#ifdef ESP32
#include "FlashUpdater.h"
#include <StreamString.h>
#include "tinyHTTP.h"
#include <esp_partition.h>
#include <esp_ota_ops.h> // get running partition
#include <otadrive_esp.h>
#include <Update.h>
#include <WiFi.h>
#if ESP_IDF_VERSION >= 0x050000
    #include <spi_flash_mmap.h>
#endif


using namespace OTAdrive_ns;

// To do extern "C" uint32_t _SPIFFS_start;
// To do extern "C" uint32_t _SPIFFS_end;

FlashUpdater::FlashUpdater(void)
    : _httpClientTimeout(8000), _ledPin(-1)
{
}

FlashUpdater::~FlashUpdater(void)
{
}

FotaResult FlashUpdater::update(Client &client, const String &url)
{
    return handleUpdate(client, url);
}

/**
 * return error code as int
 * @return int error code
 */
int FlashUpdater::getLastError(void)
{
    return _lastError;
}

/**
 * return error code as String
 * @return String error
 */
String FlashUpdater::getLastErrorString(void)
{

    if (_lastError == 0)
    {
        return String(); // no error
    }

    // error from Update class
    if (_lastError > 0)
    {
        StreamString error;
        Update.printError(error);
        error.trim(); // remove line ending
        return String("Update error: ") + error;
    }

    // error from http client
    if (_lastError > -100)
    {
        return String("HTTP error: ") + String(_lastError);
    }

    switch (_lastError)
    {
    case HTTP_UE_TOO_LESS_SPACE:
        return "Not Enough space";
    case HTTP_UE_SERVER_NOT_REPORT_SIZE:
        return "Server Did Not Report Size";
    case HTTP_UE_SERVER_FILE_NOT_FOUND:
        return "File Not Found (404)";
    case HTTP_UE_SERVER_FORBIDDEN:
        return "Forbidden (403)";
    case HTTP_UE_SERVER_WRONG_HTTP_CODE:
        return "Wrong HTTP Code";
    case HTTP_UE_SERVER_FAULTY_MD5:
        return "Wrong MD5";
    case HTTP_UE_BIN_VERIFY_HEADER_FAILED:
        return "Verify Bin Header Failed";
    case HTTP_UE_BIN_FOR_WRONG_FLASH:
        return "New Binary Does Not Fit Flash Size";
    case HTTP_UE_NO_PARTITION:
        return "Partition Could Not be Found";
    }

    return String();
}

String FlashUpdater::createHeaders(void)
{
    String hdr = "";
    hdr = "\r\nUser-Agent: OTAdrive-SDK-v" OTADRIVE_SDK_VER
          "\r\nCache-Control: no-cache";
    hdr += "\r\nx-ESP32-STA-MAC: " + WiFi.macAddress();
    hdr += "\r\nx-ESP32-AP-MAC: " + WiFi.softAPmacAddress();
    hdr += "\r\nx-ESP32-free-space: " + String(ESP.getFreeSketchSpace());
    hdr += "\r\nx-ESP32-sketch-size: " + String(ESP.getSketchSize());

    String sketchMD5 = ESP.getSketchMD5();
    if (sketchMD5.length() != 0)
    {
        hdr += "\r\nx-ESP32-sketch-md5: " + sketchMD5;
    }

    hdr += "\r\nx-ESP32-chip-size: " + String(ESP.getFlashChipSize());
    hdr += "\r\nx-ESP32-sdk-version: " + String(ESP.getSdkVersion());
    hdr += "\r\nx-ESP32-mode: sketch";

    return hdr;
}

/**
 *
 * @param http GsmHttpClient *
 * @param currentVersion const char *
 * @return HTTPUpdateResult
 */
FotaResult FlashUpdater::handleUpdate(Client &client, const String &url)
{
    FotaResult ret = FotaResult::FOTA_UPDATE_FAILED;
    TinyHTTP http(client);
    http.user_headers = createHeaders();
    if (MD5_Match)
        http.user_headers += "\r\nx-check-sketch-md5: 1";

    if (!http.get(url, 0, 16))
    {
        if (http.resp_code == 304)
            return FOTA_UPDATE_NO_UPDATES;
        return FOTA_UPDATE_FAILED;
    }

    if (http.total_len > 0)
    {
        bool startUpdate = true;

        int sketchFreeSpace = ESP.getFreeSketchSpace();
        if (!sketchFreeSpace)
        {
            _lastError = HTTP_UE_NO_PARTITION;
            return FOTA_UPDATE_FAILED;
        }

        if (http.total_len > sketchFreeSpace)
        {
            otd_log_e("FreeSketchSpace to low (%d) needed: %d\n", sketchFreeSpace, http.total_len);
            startUpdate = false;
        }

        if (!startUpdate)
        {
            _lastError = HTTP_UE_TOO_LESS_SPACE;
            ret = FOTA_UPDATE_FAILED;
        }
        else
        {
            // Warn main app we're starting up...
            if (_cbStart)
            {
                _cbStart();
            }

            delay(100);
            otd_log_d("runUpdate flash...\n");

            // check for valid first magic byte
            uint8_t buf[16];
            client.readBytes(buf, 16);
            if (buf[0] != 0xE9)
            {
                otd_log_e("Magic header does not start with 0xE9\n");
                _lastError = HTTP_UE_BIN_VERIFY_HEADER_FAILED;
                // client.stop();
                return FOTA_UPDATE_FAILED;
            }

            // TODO:
            // uint32_t bin_flash_size = http.total_len;
            // check if new bin fits to SPI flash
            // if(bin_flash_size > ESP.getFlashChipSize())
            // {
            //     log_e("New binary does not fit SPI Flash size\n");
            //     _lastError = HTTP_UE_BIN_FOR_WRONG_FLASH;
            //     client.stop();
            //     return HTTP_UPDATE_FAILED;
            // }

            if (runUpdate(http, U_FLASH))
            {
                ret = FOTA_UPDATE_OK;
                otd_log_d("Update ok\n");
                // client.stop();
                // Warn main app we're all done
                if (_cbEnd)
                {
                    _cbEnd();
                }

                if (_rebootOnUpdate)
                {
                    ESP.restart();
                }
            }
            else
            {
                ret = FOTA_UPDATE_FAILED;
                otd_log_e("Update failed\n");
            }
        }
    }
    else
    {
        _lastError = HTTP_UE_SERVER_NOT_REPORT_SIZE;
        ret = FOTA_UPDATE_FAILED;
        otd_log_e("Content-Length was 0 or wasn't set by Server?!\n");
    }

    // client.stop();
    return ret;
}

#define BUF_SIZE SPI_FLASH_SEC_SIZE * 1
#define GET_SIZE SPI_FLASH_SEC_SIZE * 8
/**
 * write Update to flash
 * @param in Stream&
 * @param size uint32_t
 * @param md5 String
 * @return true if Update ok
 */
bool FlashUpdater::runUpdate(TinyHTTP http, int command)
{
    StreamString error;

    if (_cbProgress)
    {
        Update.onProgress(_cbProgress);
    }

    if (!Update.begin(http.total_len, command, _ledPin, _ledOn))
    {
        _lastError = Update.getError();
        Update.printError(error);
        error.trim(); // remove line ending
        otd_log_e("Update.begin failed! (%s)\n", error.c_str());
        Update.end();
        return false;
    }

    if (_cbProgress)
    {
        _cbProgress(0, http.total_len);
    }

    if (http.xMD5.length())
    {
        if (!Update.setMD5(http.xMD5.c_str()))
        {
            _lastError = HTTP_UE_SERVER_FAULTY_MD5;
            otd_log_e("Update.setMD5 failed! (%s)\n", http.xMD5.c_str());
            return false;
        }
    }

    // To do: the SHA256 could be checked if the server sends it
    MD5Builder md5c;
    md5c.begin();
    uint32_t t0 = millis();
    uint8_t tmp_buf[BUF_SIZE];
    size_t remain = http.total_len;
    size_t remain_get = 0;
    http.user_headers = "";

    for (uint32_t i = 0; i < http.total_len; tmp_buf)
    {
        otd_log_v("part i:%d,buf:%d,rem:%d", i, remain_get, remain);
        size_t rd;
        if (remain_get)
        {
            if (remain_get < BUF_SIZE)
                rd = http.client.readBytes(tmp_buf, remain_get);
            else
                rd = http.client.readBytes(tmp_buf, BUF_SIZE);
            remain_get -= rd;
        }
        else
        {
            size_t req_size = GET_SIZE;
            if (remain < GET_SIZE)
                req_size = remain;

            for (uint8_t t = 0;; t++)
            {
                if (t == 3)
                {
                    otd_log_e("Update.HTTP GET failed!");
                    return false;
                }
                if (!http.get("", i, req_size))
                    continue;

                rd = 0;
                remain_get = GET_SIZE;
                break;
            }
            continue;
        }

        if (rd == 0)
        {
            // Update.printError(error);
            // error.trim(); // remove line ending
            otd_log_e("read from stream failed!\n");
            remain_get = 0;
            return false;
            // continue;
        }
        remain -= rd;

        md5c.add(tmp_buf, rd);
        if (Update.write(tmp_buf, rd) != rd)
        {
            _lastError = Update.getError();
            Update.printError(error);
            error.trim(); // remove line ending
            otd_log_e("Update.writeStream failed! (%s)\n", error.c_str());
            return false;
        }

        i += rd;

        if (_cbProgress)
        {
            _cbProgress(i, http.total_len);
        }
    }

    md5c.calculate();
    otd_log_i("Download end MD5 %s\n", md5c.toString().c_str());
    if (!Update.end())
    {
        _lastError = Update.getError();
        Update.printError(error);
        error.trim(); // remove line ending
        otd_log_e("Update.end failed! (%s)\n", error.c_str());
        return false;
    }

    return true;
}
#endif
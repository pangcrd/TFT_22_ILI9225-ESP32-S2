#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <DHT.h>
#include <PZEM004Tv30.h>
#include <Adafruit_Sensor.h>
#include "time.h"
#include <WiFiManager.h>
#include <HardwareSerial.h>
//#include <otadrive_esp.h>
#include <WebSocketsServer.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "webpage.h"

#define FANPIN 35
#define ALARM 37
#define DHTPIN 33
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int i,j = 0;

#if defined(ESP32)
PZEM004Tv30 pzem(Serial1, 17, 18);
#else
PZEM004Tv30 pzem(Serial2);
#endif

// #define APIKEY "ac19751e-8f0d-4504-8546-d1cea02d909f" // OTAdrive APIkey for this product
// #define FW_VER "v@1.1"                              // this app version

const int ResetBTN = 34; 
const unsigned long holdTime = 3000; 
unsigned long buttonPressTime = 0;
bool buttonPressed = false;
bool fanstate = false;
int speed = 0;

WiFiManager wm;
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);



bool manualFanControl = false;  
int fanSpeed = 0;

// const char* ssid = "SHome"; // Name of the Wi-Fi box
// const char* password = "015975321"; // MDP of the Wi-Fi box

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600 * 7;
const int   daylightOffset_sec = 3600 * 0;


/*Change to your screen resolution*/
static const uint16_t screenWidth  = 220;
static const uint16_t screenHeight = 176;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif



/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}
/**************************WEBSOCKET************************/

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    String msg = "";
    for (size_t i = 0; i < len; i++) {
    msg += (char)data[i];
     }
     if (msg == "toggleFan") {
        fanstate = !fanstate;
        digitalWrite(FANPIN, fanstate ? HIGH : LOW);
        webSocket.broadcastTXT(fanstate ? "FAN ON" : "FAN OFF");
        // Gửi trạng thái slider (vô hiệu hóa nếu LED tắt)
        webSocket.broadcastTXT(fanstate ? "slider:enable" : "slider:disable");
    } else if (msg.startsWith("fanSpeed:") && fanstate) {
        speed = msg.substring(11).toInt();
        analogWrite(FANPIN, speed );
     }

    if (msg.indexOf("resetEnergy") >= 0) {
        pzem.resetEnergy(); 
    }
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
    // if (type == WStype_TEXT) {
    //     //handleWebSocketMessage(payload);
    //     String message = String((char*)payload);
    //      if (message.indexOf("toggleFan") >= 0) {
    //         manualFanControl = !manualFanControl;
    //         if (!manualFanControl) {
    //             analogWrite(FANPIN, 0);  // Tắt quạt nếu chuyển sang điều khiển tự động
    //         }
    //     } 
    //     
    //     else if (message.indexOf("setSpeed") >= 0) {
    //         // Xử lý tốc độ quạt từ thanh trượt
    //         int startIndex = message.indexOf("Speed:") + 6;
    //         fanSpeed = message.substring(startIndex).toInt();
    //         if (manualFanControl) {
    //             analogWrite(FANPIN, fanSpeed);
    //         }
    //     }
    // }
}

void setupWebSocket() {
    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);
}

void sendSensorData() {
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    String jsonData = "{\"voltage\":" + String(voltage) + 
                      ",\"current\":" + String(current) + 
                      ",\"power\":" + String(power) + 
                      ",\"energy\":" + String(energy) + 
                      ",\"frequency\":" + String(frequency) + 
                      ",\"temperature\":" + String(temperature) + 
                      ",\"humidity\":" + String(humidity) + "}";
    
    webSocket.broadcastTXT(jsonData);  // Gửi dữ liệu đến tất cả các client kết nối

}
/**************************WEBSOCKET END************************/

/**************************Đẩy giá trị nhiệt độ/độ ẩm từ cảm biến DTH22 lên màn hình************************/
void tempHumi(){
  /*Nhiệt độ*/
  float temperature = dht.readTemperature();
   // Chuyển đổi giá trị float thành chuỗi ký tự
  String tempString = String(temperature, 1)+ "*C";  // Lấy 1 chữ số thập phân
  const char* tempValue = tempString.c_str();   // Chuyển đổi từ String sang const char*
  lv_label_set_text(ui_temp1, tempValue);   // Cập nhật nhãn LVGL
  /*Độ ẩm*/
  float humidity = dht.readHumidity();
  String humidString = String(humidity, 1)+ "%";
  const char* humiValue = humidString.c_str();  
  lv_label_set_text(ui_humi1, humiValue);

  if (manualFanControl ) {
        analogWrite(FANPIN, fanSpeed);
        lv_obj_clear_flag(ui_fanon, LV_OBJ_FLAG_HIDDEN);  // Hiện icon khi đạt ngưỡng
    } else {
          // Điều khiển quạt dựa trên giá trị cảm biến
        float temperature = dht.readTemperature();
        if (temperature > 46) {
            analogWrite(FANPIN, 150);
            lv_obj_clear_flag(ui_fanon, LV_OBJ_FLAG_HIDDEN);  // Hiện icon khi đạt ngưỡng
        } else if (temperature < 37) {
            analogWrite(FANPIN, 0);
            lv_obj_add_flag(ui_fanon, LV_OBJ_FLAG_HIDDEN);  // Ẩn icon nếu không đạt ngưỡng
        }
        
    }
}
/**************************Cảnh báo************************/
void alarm(){
for(j=0;j<3;j++)
{
  
  for(i=700;i<800;i++)
      {
      tone(ALARM,i);
      delay(15);
      }
  for(i=800;i>700;i--)
      {
      tone(ALARM,i);
      delay(15);
      }
      noTone(ALARM);
}
} 
void alarm1(){
  tone(ALARM, 2000, 100);
  delay(200); 
  tone(ALARM, 2000, 100);
  delay(200);
  tone(ALARM, 2000, 100);
  delay(1000);
}

/**************************Alarm END************************/

/**************************Get Date Time************************/
void getDateTime(){

 struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    lv_label_set_text(ui_date, "Date: N/A");
    lv_label_set_text(ui_time, "Time: N/A");
    return;
  }

  // Hiển thị ngày tháng năm
  char dateBuffer[11];
  strftime(dateBuffer, sizeof(dateBuffer), "%d/%m/%Y", &timeinfo);
  lv_label_set_text(ui_date, dateBuffer);

  // Hiển thị giờ phút
  char timeBuffer[6];
  strftime(timeBuffer, sizeof(timeBuffer), "%H:%M", &timeinfo);
  lv_label_set_text(ui_time, timeBuffer);

  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

}

/**************************************************/
/**************************PZEM004T************************/
void energy(){
    lv_obj_add_flag(ui_overvoltage, LV_OBJ_FLAG_HIDDEN);
    float voltage = pzem.voltage();
    String volS = String(voltage, 1)+ "V";  
    const char* volValue = volS.c_str();
    lv_label_set_text(ui_voltage, volValue);  
        //Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
    float current = pzem.current();
    String ampS = String(current, 1)+ "A";  
    const char* ampValue = ampS.c_str();
    lv_label_set_text(ui_ampe, ampValue); 
        //Serial.print("Current: "); Serial.print(current); Serial.println("A");
    float power = pzem.power();
    String powerS = String(power, 1)+ "W";  
    const char* powerValue = powerS.c_str();
    lv_label_set_text(ui_power,powerValue); 
        //Serial.print("Power: "); Serial.print(power); Serial.println("W");
    float energy = pzem.energy();
    String energyS = String(energy, 1)+ "W";  
    const char* energyValue = energyS.c_str();
    lv_label_set_text(ui_thongke,energyValue); 
        //Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
    float frequency = pzem.frequency();
    String freqS = String(frequency, 1)+ "Hz";  
    const char* freqValue = freqS.c_str();
    lv_label_set_text(ui_sine,freqValue); 
        //Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
    
}


void resetEnergy() {

     int buttonState = digitalRead(ResetBTN);

    if (buttonState == HIGH) {
        if (!buttonPressed) {
            buttonPressed = true;
            buttonPressTime = millis();
        } else if (millis() - buttonPressTime >= holdTime) {
            pzem.resetEnergy();
            //Serial.println("Energy reset");
            lv_obj_clear_flag(ui_energyRST, LV_OBJ_FLAG_HIDDEN);
            buttonPressed = false; // Đặt lại trạng thái nút để không bị reset nhiều lần
        }
    } else {
        buttonPressed = false;
        lv_obj_add_flag(ui_energyRST, LV_OBJ_FLAG_HIDDEN);

    }
}

void warning(){

 float current = pzem.current();
  if (current > 27) {
     lv_obj_clear_flag(ui_overvoltage, LV_OBJ_FLAG_HIDDEN);
     alarm();
  } else {
    lv_obj_add_flag(ui_overvoltage, LV_OBJ_FLAG_HIDDEN);
  }  

 float voltage = pzem.voltage();
    if (voltage < 190 ) {
          lv_obj_clear_flag(ui_overvoltage, LV_OBJ_FLAG_HIDDEN);
          alarm1();
        } else {
          lv_obj_add_flag(ui_overvoltage, LV_OBJ_FLAG_HIDDEN);

        }
}

/**************************************************/
void my_timer(lv_timer_t * timer) { //Đẩy giá trị lên màn hình theo chu kỳ 2s một lần
    if (WiFi.status() == WL_CONNECTED) {
        // Update IP address and time if connected to Wi-Fi
        String ipAddress = WiFi.localIP().toString();
        lv_label_set_text(ui_ipaddress, ipAddress.c_str());
        lv_obj_add_flag(ui_wifierr, LV_OBJ_FLAG_HIDDEN); // Ẩn icon wifierr
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        getDateTime();       
    } else {
        // Show "Connecting to Wi-Fi" message if not connected
        lv_label_set_text(ui_ipaddress, "Connecting...");
        lv_obj_clear_flag(ui_wifierr, LV_OBJ_FLAG_HIDDEN);

    }
    tempHumi();
    energy();
    resetEnergy();
    webSocket.loop();  // Xử lý các sự kiện WebSocket
    sendSensorData();

}

void setup(){
    Serial.begin( 115200 );
    //PZEM_SERIAL.begin(9600);
    dht.begin();
    pinMode(FANPIN, OUTPUT);
    pinMode(ALARM, OUTPUT);
    digitalWrite(ALARM, HIGH);
    delay(1000);
    digitalWrite(ALARM, LOW);
    delay(1000);
    pinMode(ResetBTN, INPUT);
      // Tạo tên và mật khẩu cho AP mode
    String apName = "CTD_AP";
    String apPassword = "12345678";
    wm.setTimeout(120);
    wm.setConfigPortalTimeout(60); // 60 giây
    wm.setAPCallback([](WiFiManager* myWiFiManager) {
    //Serial.println("Entered AP mode");
    });
    // Sử dụng tên và mật khẩu AP mode khi không kết nối được Wi-Fi sau 60s
    if (!wm.autoConnect(apName.c_str(), apPassword.c_str())) {
        //Serial.println("Failed to connect, restarting...");             
        WiFi.disconnect(true);// Ngắt kết nối Wi-Fi và reset ESP để vào lại AP mode
        WiFi.persistent(true);
        WiFi.setAutoConnect(true);
        WiFi.setAutoReconnect(true);
        delay(1000);
        ESP.restart();
    } 

    WiFi.mode(WIFI_STA); // Optional
    //WiFi.begin(ssid, password);
    //Serial.println("\nConnecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println(WiFi.localIP());
    //Vào DHCP của router thiết lập địa chỉ IP cố định cho ESP32 bằng cách đặt trước địa chỉ IP dựa trên địa chỉ MAC.
    if (!MDNS.begin("congtodien")) { // congtodien.local Tên miền tĩnh
      //Serial.println("Lỗi khi bắt đầu mDNS");
      return;
    }


    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", MAIN_page);
    });
    server.begin();
    setupWebSocket();

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    //Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 1 ); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    //indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );
    ui_init();
    lv_timer_t* timer = lv_timer_create(my_timer,2000,NULL); //Đọc và gửi dữ liệu mỗi 2s
    lv_scr_load(ui_startScr);
    lv_obj_add_event_cb(ui_startScr, ui_event_startScr, LV_EVENT_SCREEN_LOADED, NULL);
    //Serial.println( "Setup done" );
}

void loop()
{

    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
}




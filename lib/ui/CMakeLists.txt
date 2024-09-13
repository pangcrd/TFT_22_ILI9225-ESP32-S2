SET(SOURCES ui_Screen1.c
    ui_startScr.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_img_contodien_png.c
    ui_img_powermeter_1_png.c
    ui_img_line_4_png.c
    ui_img_vol_1_png.c
    ui_img_pw_1_png.c
    ui_img_ampe_1_png.c
    ui_img_graphico_1_png.c
    ui_img_line_5_png.c
    ui_img_line_6_png.c
    ui_img_voltnone_1_png.c
    ui_img_overvoltage_1_png.c
    ui_img_clockpng_1_png.c
    ui_img_calendar_1_png.c
    ui_img_line_2_png.c
    ui_img_humidity_1_png.c
    ui_img_temperature_1_png.c
    ui_img_coolingfan_1_png.c
    ui_img_wifiok_2_png.c
    ui_img_wifierr_1_png.c
    ui_img_sine_png.c
    ui_img_line1_1_png.c
    ui_img_line1_2_png.c
    ui_img_ipaddress_png.c
    ui_img_fame_png.c
    ui_img_scr1_png.c)

add_library(ui ${SOURCES})

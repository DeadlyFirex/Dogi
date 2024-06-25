#include "display.h"

U8G2_SSD1306_64X32_1F_F_HW_I2C dsp::u8g2 = U8G2_SSD1306_64X32_1F_F_HW_I2C(U8G2_R2, U8X8_PIN_NONE);

bool dsp::setup() {
    return dsp::u8g2.begin();
}

void dsp::draw_display(_arguments args) {
    dsp::u8g2.clearBuffer();

    dsp::u8g2.setFont(u8g2_font_u8glib_4_tf);
    dsp::u8g2.drawStr(5, 5, "MNT+");
    
    dsp::u8g2.setCursor(45, 5);
    dsp::u8g2.print(args.time_message);
    
    dsp::u8g2.drawLine(0, 10, 64, 10);
    dsp::u8g2.setFont(u8g2_font_5x7_tf);

    dsp::u8g2.setCursor(5, 20);
    dsp::u8g2.print(args.since_message);

    dsp::u8g2.setCursor(5, 30);
    dsp::u8g2.print(args.detected ? "SEEN" : "...");

    dsp::u8g2.setCursor(48, 30);
    dsp::u8g2.print(args.ble_active ? "B" : "-");

    dsp::u8g2.setCursor(56, 30);
    dsp::u8g2.print(args.serial_active ? "S" : "-");

    dsp::u8g2.sendBuffer();
}
#pragma once

#include <Wire.h>
#include <U8g2lib.h>

namespace dsp {

    struct _arguments {
        bool & detected;
        char * since_message;
        
        bool & ble_active;
        bool serial_active;
        char * time_message;
    };
    extern U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2;

    bool setup();
    void draw_display(_arguments args);
}
#include "lcd.h"
#include "configuration.h"

namespace screen{

    LiquidCrystal_I2C lcd(0x27, 16 , 2);
   
    char buffer_line_1[17]{};
    char buffer_line_2[17]{};

    void initialize(){
        lcd.init();
        lcd.backlight();
        Serial.println("LCD display initialized");
        bootMessage();
        
    }

    void update(){
        lcd.setCursor(0, 0);
        lcd.print(buffer_line_1);
        lcd.setCursor(0, 1);
        lcd.print(buffer_line_2);
    }

    void bootMessage(){
        sprintf(buffer_line_1, "    Biosynth    ");
        sprintf(buffer_line_2, "      %4d      ", configuration::version_year);
        update();
    }

    void clear(){
        sprintf(buffer_line_1, "                ");
        sprintf(buffer_line_2, "                ");
        update();
}

}//namespace screen

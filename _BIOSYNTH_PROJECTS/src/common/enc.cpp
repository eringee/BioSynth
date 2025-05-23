#include "enc.h"
#include "pins.h"
#include "configuration.h"


namespace encoder{

    Encoder encoder(pins::hardware::encoder_B, pins::hardware::encoder_A);

    void initialize(){
        set_value(0);
        Serial.println("Encoder initialized");
    }

    void set_value(const int& value){
        encoder.write(value * 4); //multiply by 4 because it is a quadrature encoder
    }

    int limit(const int& pos, const int& min_pos, const int& max_pos){
       
        if(pos < min_pos)
        {   
            set_value(min_pos); 
            return min_pos;
        }
        else if( pos > max_pos)
        {   
            set_value(max_pos);
            return max_pos;
        }

        return pos;
    }

    int update(int number_sections){
        static int current_encoder_value{0};
        static long last_read_time{0};

        int newPosition{limit(encoder.read()/4, 0,number_sections-1)}; //divided by 4 because its a quadrature encore
        long unsigned int current_read_time{millis()};

        //test for time for debouncing purpose. Could be removed if using encoder with the interrups
        if(current_encoder_value != newPosition && (current_read_time-last_read_time) >= 500){
            current_encoder_value = newPosition;
            last_read_time = millis();
        }
        
        return current_encoder_value;
    }

}//namespace encoder

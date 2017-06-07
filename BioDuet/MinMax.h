class MinMax {
    float input= 0;
    float min = 0;
    float max = 0;
    float value = 0;
    bool reset = true;

  public:
    MinMax() {

    }


    void adapt(float lop) {
      lop = constrain(lop, 0, 1);
      lop = lop * lop;

      min = (input - min) * lop + min;
      max = (input - max) * lop + max;
    }

    float filter(float f) {

      input = f;
      
      if ( reset == true ) {
        reset = false;
        min = f;
        max = f;
      } else {
        if ( f > max ) max = f;
        if ( f < min ) min = f;
      }


      if ( max == min ) {
        value = 0.5;
      } else {
        value = (f - min) / ( max - min);

      }

      return value;
    }

    float getMax() {

      return max;
    }

    
    float getMin() {

      return min;
    }


};


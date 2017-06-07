class Hip {
  float value;
  float previousInput;
  float hip;

 public:
  Hip(float hip ) {
    this->hip = hip;
    };

  float filter( float input) {
    value =  hip * ( value + input - previousInput);
    previousInput = input;
    return value;
  }
  
  
};


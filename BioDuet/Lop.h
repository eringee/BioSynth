class Lop {
  
  float lop;
  float value;
 public:
 
  Lop(float lop) {
    this->lop = lop;
    };

  float filter( float input ) {
    value = (input-value)*lop + value;
    return value;
  }
  
  
};


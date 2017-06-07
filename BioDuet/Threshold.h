class Threshold {
  float lower;
  float upper;
  bool triggered = false;

public:

 Threshold(float lower, float upper) {
  this->lower = lower;
  this->upper = upper;
 }

 bool detect(float value) {

    if ( value >= upper && triggered == false ) {
      triggered = true;
      return true;
    } else if ( value <= lower) {
      triggered = false;
    }
    return false;
  
 }


  
};


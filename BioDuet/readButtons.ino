void readButtons() {
  
  debouncerBlack.update();
  debouncerRed.update();
  debouncerGreen.update();
  debouncerBlue.update();
  
  if (debouncerBlack.fell() ) configMode = !configMode;

  if (configMode) {
    
    if (debouncerRed.fell() )   redToggle   = !redToggle;
    if (debouncerGreen.fell() ) greenToggle = !greenToggle;
    if (debouncerBlue.fell() )  blueToggle  = !blueToggle;
  }
}

void updateLeds() {
  if (configMode) {
    // USE THESE TOGGLES TO ACTIVATE DIFFERENT SOUND SETTINGS IN MAIN LOOP WITH BOOLEAN LOGIC // 
    if (redToggle) analogWrite(heartLed, 255);
    else analogWrite(heartLed, 0);
    
    if (greenToggle) analogWrite(gsrLed, 255);
    else analogWrite(gsrLed, 0);
    
    if (blueToggle) analogWrite(respLed, 150);  // this LED's brightness needs to get toned down
    else analogWrite(respLed, 0);
  }
  else {
     analogWrite(respLed, 0);
    // analogWrite(gsrLed, gsrSensorChange * -30);


  int gsrLight = GSRmastered * 255;
  //gsrLighter.push(gsrLight);                   //LED still flickers...
  
  if(gsrSensorReading<GSRav) gsrLightFinal = 0;       //less than average implies an absence of sweat
 // else gsrLightFinal = gsrLighter.mean();      
  else gsrLightFinal = gsrLight;
  
  analogWrite(gsrLed, gsrLightFinal);
  
  analogWrite(heartLed, heartSensorFiltered * 255);
  }
}


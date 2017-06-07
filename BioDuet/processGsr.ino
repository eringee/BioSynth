void processGsr() {
  
/*
  // GSR
  int gsrSensorReading = analogRead(A6);
  gsrSensorLop = gsrLop.filter(gsrSensorReading);
  gsrSensorFiltered = gsrMinMax.filter(gsrSensorLop); // Min max the data
  gsrSensorChange = gsrHip.filter(gsrSensorLop); // Get the change over time
 // gsrSensorChange = gsrHip.filter(gsrSensorFiltered);
  
*/

  gsrSensorReading = analogRead(A6);    //read the signal
  gsrSensorReading = (gsrSensorReading-1023)*-1;    //inverse the value
  
  gsrSensorLop = gsrLop.filter(gsrSensorReading);
  gsrSensorFiltered = gsrMinMax.filter(gsrSensorLop); // Min max the data
  gsrMinMax.adapt(0.01); // APPLY A LOW PASS ADAPTION FILTER TO THE MIN AND MAX
  
  if(gsrSensorLop<0) GSRaverager.push(gsrSensorLop-10); //only the greater than average values matter, shove the lesser than values down quick
  else GSRaverager.push(gsrSensorLop);               //array for determining an average GSR over time
  
  GSRav = GSRaverager.mean();        
  GSRmastered = (gsrSensorLop-GSRav) / 10;                    
  if (GSRmastered<0) GSRmastered = 0;
  if(gsrSensorLop>GSRmax) GSRmax = gsrSensorLop;      //keep track of the latest max value 
  else GSRmax = (GSRaverager.maximum(&maxat));

  if (GSRmastered>1.) GSRmastered = 1.;        //keep the mapping below 1 no matter what
  
  msg.beginPacket("gsr");
 /* 
  msg.addFloat( gsrSensorChange );  */
  //msg.addFloat( gsrSensorReading );
  msg.addFloat( gsrSensorLop );
  msg.addFloat( gsrSensorFiltered);
  msg.addFloat( GSRmastered);
  msg.endPacket();
}


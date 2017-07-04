void processGsr() {
  

  // GSR
  int gsrSensorReading = analogRead(A6);
  gsrSensorLop = gsrLop.filter(gsrSensorReading);
  //gsrSensorFiltered = gsrMinMax.filter(gsrSensorLop); // Min max the data
  gsrSensorChange = gsrHip.filter(gsrSensorLop); // Get the change over time
  gsrMinMax.adapt(0.01); // APPLY A LOW PASS ADAPTION FILTER TO THE MIN AND MAX

  msg.beginPacket("gsr");
  //msg.addFloat( gsrSensorReading );
  //msg.addFloat( gsrSensorLop );
  msg.addFloat( gsrSensorChange );
  msg.endPacket();
}


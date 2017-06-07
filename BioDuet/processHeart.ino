void processHeart() {
   // HEART
  int heartSensorReading = analogRead(A8);

  heartSensorFiltered = heartMinMax.filter(heartSensorReading);
  heartSensorAmplitude = heartMinMax.getMax() - heartMinMax.getMin();
  heartMinMax.adapt(0.01); // APPLY A LOW PASS ADAPTION FILTER TO THE MIN AND MAX

  heartSensorAmplitudeLopValue = heartSensorAmplitudeLop.filter(heartSensorAmplitude); 
  heartSensorBpmLopValue =  heartSensorBpmLop.filter(bpm);

   heartSensorAmplitudeLopValueMinMaxValue = heartSensorAmplitudeLopValueMinMax.filter(heartSensorAmplitudeLopValue);
   heartSensorAmplitudeLopValueMinMax.adapt(0.001);
   heartSensorBpmLopValueMinMaxValue = heartSensorBpmLopValueMinMax.filter(heartSensorBpmLopValue);
  heartSensorBpmLopValueMinMax.adapt(0.001);
  
  msg.beginPacket("heart");
  msg.addFloat( heartSensorReading );
  msg.addFloat( heartSensorFiltered );
  msg.addFloat( heartSensorAmplitudeLopValueMinMaxValue);
  msg.addFloat( heartSensorBpmLopValueMinMaxValue );
  msg.endPacket();

  bool beatDetected = heartThresh.detect(heartSensorFiltered);

  if ( beatDetected ) {
    unsigned long temporaryBpm = 60000. / (bpmChrono.elapsed());
    bpmChrono.restart();

    if ( temporaryBpm > 30 && temporaryBpm < 200 ) {

      

      bpm = temporaryBpm;

 





      msg.beginPacket("beat");
      msg.addFloat(bpm);
      msg.addFloat(heartSensorAmplitude);
      msg.endPacket();

      // A BEAT IS DETECTED
    }

  }
}


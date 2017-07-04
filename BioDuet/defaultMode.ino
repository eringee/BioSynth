void setupModeDefault() {
  
 // outputFilter.frequency(10000);
 // outputFilter.resonance(0.7); //Set the filter's resonance. Q ranges from 0.7 to 5.0.

  // set bits to 16 and sampleRate to 44100 to pass audio through without any Bitcrush effect.
 /* bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);*/
  
  sine_fm1.amplitude(0.15); 
  sine_fm2.amplitude(0.1);
  sine_fm3.amplitude(0.08);
  sine_fm4.amplitude(0.06);

 // bassnoteVibrato.begin(0.004, 1, WAVEFORM_SINE);

 // filter1.resonance(1.2);

  arp.setLoop(0);

/////////////////////////////////BOX DEPENDANT VARIABLES///////////////
  
if (box == 1) {
  sine_fm1.frequency(1046);  //C
  sine_fm2.frequency(1174);  //D
  sine_fm3.frequency(1566);  //G
  sine_fm4.frequency(2098);  //C

  bassnote.frequency(500);  //C
  
  filter1.frequency(1000);   //low ocean
  
  arp.setLoop(1);
  arp.setBpm(bpm);
  arp.trigger();

  instrument = 1;

  arp.setOffset(0);
  arp.setIncrement(6);
  arp.setSteps(5);
  arp.setOctave(1);
  arp.setDivision(1);
}

else if (box == 2) {
  //Box2//////////////////////////////  
  sine_fm1.frequency(1174); //D
  sine_fm2.frequency(1318); //E
  sine_fm3.frequency(1760); //A  
  sine_fm4.frequency(2349); //D      
    
  bassnote.frequency(146);  //D
  
  filter1.frequency(2500);   //middle ocean

 
  //arp.trigger();
  arp.setLoop(0);
}
  
else if (box == 3) {
  //Box3////////////////////////////
  sine_fm1.frequency(1567);  //G
  sine_fm2.frequency(1760);  //A
  sine_fm3.frequency(2349);  //D  
  sine_fm4.frequency(3135);  //G      
  
  bassnote.frequency(195);  //G
  
  filter1.frequency(3500);   //high ocean

  arp.setLoop(0);
}
/////////////////////////////////END BOX DEPENDANT VARIABLES///////////////

}

void runModeDefault() {

  noise.amplitude(1 - heartSensorAmplitudeLopValueMinMaxValue*1.85);   // "ocean" controlled by BVPA

  //bassnote.amplitude(heartSensorBpmLopValueMinMaxValue/ 8.0);  //bassnote amp controlled by HRV
  bassnote.amplitude(0.1);
  arp.setIncrement(heartSensorBpmLopValueMinMaxValue * 10);  //

///////////////analyze GSR levels////////////////////////

  if (GSRmastered >= 0.02  && !gsrStage1) {
    sine_envelope1.noteOn();
    gsrStage1 = true;
  }
 
  else if (GSRmastered < 0.02 && gsrStage1) {
    sine_envelope1.noteOff();
    gsrStage1 = false;

  }

  if (GSRmastered >= 0.05  && !gsrStage2) {
    sine_envelope2.noteOn();
    gsrStage2 = true;
  }
 
  else if (GSRmastered < 0.1 && gsrStage2) {
    sine_envelope2.noteOff();
    gsrStage2 = false;
  }

  
  if (GSRmastered >= 0.15  && !gsrStage3) {
    sine_envelope3.noteOn();
    gsrStage3 = true;
  }
 
  else if (GSRmastered < 0.15 && gsrStage3) {
    sine_envelope3.noteOff();
    gsrStage3 = false;
  }

  if (GSRmastered >= 0.2  && !gsrStage4) {
    sine_envelope4.noteOn();
    gsrStage4 = true;
  }
 
  else if (GSRmastered < 0.2 && gsrStage4) {
    sine_envelope4.noteOff();
    gsrStage4 = false;
  }
  
}


 



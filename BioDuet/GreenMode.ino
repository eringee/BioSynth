//Soft natural Guitar song

void setupGreenMode() {
arp.setBpm(bpm/3);

sine_fm1.amplitude(0.25); 

/*bitcrusher1.bits(16);
bitcrusher1.sampleRate(44100);*/
  
bassnote.amplitude(0);
noise.amplitude(0);
sine_envelope1.noteOff();
sine_envelope2.noteOff();
sine_envelope3.noteOff();
sine_envelope4.noteOff();

outputFilter.resonance(0.7);

instrument = 2;

arp.setLoop(1);
arp.trigger();

arp.setOffset(2);  
arp.setIncrement(0);
arp.setSteps(4);
arp.setDivision(1);

if (box == 1){
  outputFilter.frequency(4500);
  arp.setOctave(5);
  sine_fm1.frequency(9000); 
}
if (box == 2){
  arp.setOctave(7);
  arp.setBpm(bpm*0.75);
  arp.setDivision(1);
  arp.setSteps(0);

  sine_fm1.frequency(14000);  
}
if (box == 3){
  outputFilter.frequency(2500);
  arp.setOctave(4);
  arp.setBpm(bpm/4);

  sine_fm1.frequency(10000);  
}

}

void runGreenMode() {

 // noise.amplitude(1 - heartSensorAmplitudeLopValueMinMaxValue*1.85);   // "ocean" controlled by BVPA
  if (box == 2){

    if (GSRmastered >= 0.1  && !gsrStage1) {
     sine_envelope1.noteOn();
     gsrStage1 = true;
    }
 
    else if (GSRmastered < 0.1 && gsrStage1) {
      sine_envelope1.noteOff();
      gsrStage1 = false;
    }
  }
  
  if (box == 1 || box == 3){
    
  arp.setIncrement(heartSensorAmplitudeLopValueMinMaxValue*10-5);
  arp.setBpm(bpm);
  if (bpm < 80) arp.setDivision(2);
  else arp.setDivision(1);
  
////////////////////////////////
  
  if (GSRmastered >= 0.05  && !gsrStage1) {
    //arp.setBpm(bpm);
  //  bitcrusher1.sampleRate(20000);
    sine_envelope1.noteOn();
    gsrStage1 = true;
  }
 
  else if (GSRmastered < 0.05 && gsrStage1) {
    //arp.setBpm(bpm/3);
    sine_envelope1.noteOff();
    gsrStage1 = false;
   // bitcrusher1.sampleRate(44100);
  }
////////////////////////////////
  if (GSRmastered >= 0.1  && !gsrStage2) {
    //gsrStage2 = true;
  //  bitcrusher1.sampleRate(10000);
  }
 
  else if (GSRmastered < 0.1 && gsrStage2) {
   // arp.setBpm(bpm/2);
  // bitcrusher1.sampleRate(20000);
    gsrStage2 = false;
  }
////////////////////////////
  
  if (GSRmastered >= 0.15  && !gsrStage3) {
   // arp.setDivision(2);
 //  bitcrusher1.sampleRate(5000);
    gsrStage3 = true;
  }
 
  else if (GSRmastered < 0.15 && gsrStage3) {
    //arp.setDivision(1);
 //   bitcrusher1.sampleRate(10000);
    gsrStage3 = false;
  }
///////////////////////////////////////
  if (GSRmastered >= 0.2  && !gsrStage4) {
   // arp.setDivision(3);
  // bitcrusher1.sampleRate(2000);
    gsrStage4 = true;
  }
 
  else if (GSRmastered < 0.2 && gsrStage4) {
   // arp.setDivision(2);
 //  bitcrusher1.sampleRate(5000);
    gsrStage4 = false;
  }
  }
}

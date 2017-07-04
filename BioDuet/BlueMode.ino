void setupBlueMode() {
  arp.setBpm(bpm);

/*  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);*/

  bassnote.amplitude(0);
  noise.amplitude(0);
  sine_envelope1.noteOff();
  sine_envelope2.noteOff();
  sine_envelope3.noteOff();
  sine_envelope4.noteOff();

  outputFilter.resonance(0.7);
  outputFilter.frequency(1000);

  arp.setLoop(1);
  arp.trigger();

  if (box == 1) {   //slow tweeter
    arp.setBpm(bpm/2);
    instrument = 1;
    arp.setOffset(0);  
    arp.setIncrement(1);
    arp.setSteps(4);
    arp.setDivision(1);
    arp.setOctave(3);
  }

  if (box == 2){  //fast tweeter
    instrument = 1;
    arp.setOffset(0);  
    arp.setIncrement(1);
    arp.setSteps(4);
    arp.setDivision(3);
    arp.setOctave(4);
  }

  if (box == 3){   //low frequency bassline
    instrument = 0;
    arp.setOffset(0);  
    arp.setIncrement(2);
    arp.setSteps(2);
    arp.setDivision(5);
    arp.setOctave(3);
  }
}
void runBlueMode() {
  if (box == 1){
    
  }
    if (box == 2){
    
  }
    if (box == 3){
   // outputFilter.frequency(1200-10000);
    outputFilter.resonance(5.0);

   // bitcrusher1.sampleRate(100-10000);
  }
}


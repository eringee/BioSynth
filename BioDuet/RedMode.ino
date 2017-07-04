void setupRedMode() {

/*bitcrusher1.bits(16);
bitcrusher1.sampleRate(44100);*/

bassnote.amplitude(0);
noise.amplitude(0);
sine_envelope1.noteOff();
sine_envelope2.noteOff();
sine_envelope3.noteOff();
sine_envelope4.noteOff();

if (box == 1) {  // Guitar
  instrument = 2;
  
  arp.setLoop(1);

  arp.setOffset(1);
  arp.setIncrement(1);
  arp.setSteps(4);
  arp.setOctave(4);
  arp.setDivision(4);
  arp.trigger();
  outputFilter.resonance(4.0);
  }  //end box 1 settings

  if (box == 2) {  // GSRTWEETER
    instrument = 1;
    arp.setOctave(8);
    arp.setLoop(0);
  }

  if (box == 3){
    instrument = 1;
    arp.setLoop(1);
    arp.trigger();
    arp.setIncrement(4);
    arp.setSteps(1);
    arp.setOctave(2);
    arp.setDivision(6);
  }

}

void runRedMode() {

  if (GSRmastered > 0.0  && !gsrStage1) {
      if (box == 3) {
      sine_envelope1.noteOff();
      sine_envelope3.noteOff();
      sine_envelope4.noteOff();
      }
      gsrStage1 = true;
    }
 
    else if (GSRmastered < 0.005 && gsrStage1) {
     // sine_envelope1.noteOff();
      gsrStage1 = false;
    }

    if (GSRmastered > 0.05  && !gsrStage2) {
      if (box == 2) {
         arp.setDivision(2);
         arp.trigger();
       }
      if (box == 3) {
      sine_envelope1.noteOff();
      sine_envelope3.noteOff();
      sine_envelope4.noteOff();
      }
      gsrStage2 = true;
    }
 
    else if (GSRmastered < 0.1 && gsrStage2) {
      gsrStage2 = false;
    }

    if (GSRmastered > 0.15  && !gsrStage3) {
      if (box == 2){
        arp.setDivision(5);
        arp.trigger();
      }
      if (box == 3) {
      sine_envelope1.noteOff();
      sine_envelope3.noteOff();
      sine_envelope4.noteOff();
      }
      gsrStage3 = true;
    }
 
    else if (GSRmastered < 0.2 && gsrStage3) {
     // sine_envelope3.noteOff();
      gsrStage3 = false;
    }

    if (GSRmastered > 0.3  && !gsrStage4) {
      if (box == 2){
        arp.setDivision(8);
        arp.trigger();
      }
      gsrStage4 = true;
    }
 
    else if (GSRmastered < 0.3 && gsrStage4) {
    //  sine_envelope4.noteOff();
      gsrStage4 = false;
    }

  if (box == 1) {  // (Guitar) 

    arp.setIncrement((heartSensorAmplitudeLopValueMinMaxValue * 10) - 5);

    int filterMe = map(heartSensorAmplitudeLopValueMinMaxValue*100, 0, 100, 500, 6000);
    
    outputFilter.frequency(filterMe);
    ///////////////analyze GSR levels////////////////////////

    
    if (gsrStage4) arp.setDivision(7);
    else if (gsrStage3) arp.setDivision(6);
    else if (gsrStage2) arp.setDivision(5);
    else if (gsrStage1) arp.setDivision(4);
    else arp.setDivision(3);

 /*   if ((heartSensorAmplitudeLopValueMinMaxValue * 1.5) > 5.5) bitcrusher1.sampleRate(44100);
    else if ((heartSensorAmplitudeLopValueMinMaxValue * 1.5) < 5.5) bitcrusher1.sampleRate(9000);
    else if ((heartSensorAmplitudeLopValueMinMaxValue * 1.5) < 5) bitcrusher1.sampleRate(6000);
    else if ((heartSensorAmplitudeLopValueMinMaxValue * 1.5) < 4) bitcrusher1.sampleRate(4000);
    else if ((heartSensorAmplitudeLopValueMinMaxValue * 1.5) < 3) bitcrusher1.sampleRate(2000);
    else if ((heartSensorAmplitudeLopValueMinMaxValue * 1.5) < 2) bitcrusher1.sampleRate(1000);
    else if ((heartSensorAmplitudeLopValueMinMaxValue * 1.5) < 1) bitcrusher1.sampleRate(200);*/
  } //end box 1

  if(box == 2) {
    arp.setLoop(0);
    
    arp.setOctave((heartSensorBpmLopValueMinMaxValue*10)+2);
  } // end box 2
  
  if (box == 3) {
    
    arp.setDivision(heartSensorAmplitudeLopValueMinMaxValue * 30);
  }
} //end process redMode





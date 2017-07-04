void arpegiatorLoop() {
   if ( voice1IsPlaying && voice1Chrono.hasPassed(100) ) {
      voice1Chrono.restart();
      h_beat_envelope1.noteOff();
      voice1IsPlaying = false;
    }

    if ( voice2IsPlaying && voice2Chrono.hasPassed(100) ) {
      voice2Chrono.restart();
      h_beat_envelope2.noteOff();
      voice2IsPlaying = false;
    }


    // ARPEGIATOR LOOP
    if (  arp.check() ) {

      if ( instrument == 0 ) {

        h_beat_voice = (h_beat_voice + 1) % 2;

        if ( h_beat_voice == 0 ) {
          h_beat_waveform1.frequency(arp.getFreq());
          h_beat_envelope1.noteOn();
          voice1IsPlaying = true;
          voice1Chrono.restart();
        } else {
          h_beat_waveform2.frequency(arp.getFreq());
          h_beat_envelope2.noteOn();
          voice2IsPlaying = true;
          voice2Chrono.restart();
        }
      } else if ( instrument == 1 ) {

        drum1.frequency(arp.getFreq());
        drum1.length(500);
        drum1.secondMix(0);
        drum1.pitchMod(0.9);
        drum1.noteOn();

      } else if ( instrument == 2 ) {

        string1.noteOn(arp.getFreq(), 1);
      }


  }
}


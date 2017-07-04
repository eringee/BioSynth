void receiveMessages() {

// MESSAGE RECEPTION

  while ( msg.parsePacket() ) { // Run as long as  there is a new Massage.
    manualMode = true;
    if ( msg.fullMatch("arp.trigger")) {
      arp.trigger();
    } else if ( msg.fullMatch("arp.setOffset") ) {
      arp.setOffset(msg.nextInt());
    } else if ( msg.fullMatch("arp.setSteps") ) {
        arp.setSteps(msg.nextInt());
    } else if ( msg.fullMatch("arp.setDivision") ) {
      arp.setDivision(msg.nextInt());
    } else if ( msg.fullMatch("arp.setOctave") ) {
      arp.setOctave(msg.nextInt());
    } else if ( msg.fullMatch("arp.setLegato") ) {
      arp.setLegato(msg.nextInt());
    } else if ( msg.fullMatch("arp.setLoop") ) {
      arp.setLoop(msg.nextInt());
    } else if ( msg.fullMatch("arp.setIncrement") ) {
      arp.setIncrement(msg.nextInt());


      
    } else  if ( msg.fullMatch("filter") ) {
      int freq = msg.nextInt();
      float q = msg.nextFloat();
      outputFilter.frequency(freq);
      outputFilter.resonance(q); //Set the filter's resonance. Q ranges from 0.7 to 5.0.


    } else if ( msg.fullMatch("crusher") ) {
      bitcrusher1.bits(msg.nextInt());
      bitcrusher1.sampleRate(msg.nextInt());

    } else if ( msg.fullMatch("string") ) {
      string1.noteOn(msg.nextFloat(), msg.nextFloat());

    } else if ( msg.fullMatch("drum") ) {
      drum1.frequency(msg.nextFloat());
      drum1.length(msg.nextFloat());
      drum1.secondMix(msg.nextFloat());
      drum1.pitchMod(msg.nextFloat());
      drum1.noteOn();

    } else if ( msg.fullMatch("instrument") ) {

      instrument = msg.nextInt();
    }
  }
}

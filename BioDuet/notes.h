/*
   "Frequency data shall be defined in [units] which are fractions of a semitone.
   The frequency range starts at MIDI note 0, C = 8.1758 Hz,
   and extends above MIDI note 127, G = 12543.875 Hz.
   The first byte of the frequency data word specifies the highest
   equal-tempered semitone not exceeding the frequency.
*/

uint16_t n2fTable[128] PROGMEM = {8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 19, 21, 22, 23, 24, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 5920, 6645, 7040, 7459, 7902, 8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544};

int noteWrap(int value) {
  while ( value < 0 ) {
    value += 128;
  }
  return value % 128;
  
}

// MIDI note to freq
float noteToFequency(int note) {
  note = noteWrap(note);
  return n2fTable[note];
}

// MIDI note (0-11) with octave
float noteToFequency(int note, int octave) {
  note = note + (octave*12);
  note = noteWrap(note); 
  return n2fTable[note ];
}




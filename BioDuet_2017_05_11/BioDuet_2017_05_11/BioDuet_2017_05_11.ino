#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise1;         //xy=144.88333129882812,216
AudioSynthWaveform       h_beat_waveform1; //xy=176.88333129882812,112
AudioSynthWaveform       h_beat_waveform2; //xy=180.88333129882812,163
AudioSynthWaveform       waveform2;      //xy=305.8833312988281,509
AudioSynthWaveform       waveform3;      //xy=345.8833312988281,624
AudioSynthWaveformSineModulated sine_fm2;       //xy=393.8833312988281,216
AudioSynthWaveformSineModulated h_beat_sine_fm2; //xy=417.8833312988281,165
AudioSynthWaveformSineModulated h_beat_sine_fm1; //xy=419.8833312988281,111
AudioSynthWaveformSineModulated sine_fm3;       //xy=462.8833312988281,513
AudioSynthWaveformSine   sine1;          //xy=466.8833312988281,553
AudioSynthWaveformSineModulated sine_fm4;       //xy=484.8833312988281,620
AudioSynthKarplusStrong  string1;        //xy=592.88330078125,221.88333129882812
AudioSynthSimpleDrum     drum1;          //xy=592.88330078125,272.8833312988281
AudioEffectEnvelope      h_beat_envelope2; //xy=633.88330078125,164
AudioEffectEnvelope      h_beat_envelope1; //xy=669.8833312988281,112
AudioMixer4              mixer2;         //xy=766.8833312988281,543
AudioMixer4              mixer1;         //xy=886.88330078125,204
AudioEffectBitcrusher    bitcrusher1;    //xy=900.88330078125,473.8833312988281
AudioFilterStateVariable outputFilter;   //xy=1000.88330078125,562
AudioOutputAnalog        dac1;           //xy=1146.88330078125,535
AudioConnection          patchCord1(noise1, sine_fm2);
AudioConnection          patchCord2(h_beat_waveform1, h_beat_sine_fm1);
AudioConnection          patchCord3(h_beat_waveform2, h_beat_sine_fm2);
AudioConnection          patchCord4(waveform2, sine_fm3);
AudioConnection          patchCord5(waveform3, sine_fm4);
AudioConnection          patchCord6(h_beat_sine_fm2, h_beat_envelope2);
AudioConnection          patchCord7(h_beat_sine_fm1, h_beat_envelope1);
AudioConnection          patchCord8(sine_fm3, 0, mixer2, 1);
AudioConnection          patchCord9(sine1, 0, mixer2, 2);
AudioConnection          patchCord10(sine_fm4, 0, mixer2, 3);
AudioConnection          patchCord11(string1, 0, mixer1, 2);
AudioConnection          patchCord12(drum1, 0, mixer1, 3);
AudioConnection          patchCord13(h_beat_envelope2, 0, mixer1, 1);
AudioConnection          patchCord14(h_beat_envelope1, 0, mixer1, 0);
AudioConnection          patchCord15(mixer2, bitcrusher1);
AudioConnection          patchCord16(mixer1, 0, mixer2, 0);
AudioConnection          patchCord17(bitcrusher1, 0, outputFilter, 0);
AudioConnection          patchCord18(outputFilter, 0, dac1, 0);
// GUItool: end automatically generated code

#include <Chrono.h>
#include <Bounce2.h>    // debouncing library

#include "notes.h"
#include "Arpegiator.h"



// Colored buttons/LEDs used to configure (in configuration mode).

#define redButton 8
#define greenButton 9
#define blueButton 10

// This button toggles configuration vs performance mode.
#define blackButton 3

Bounce debouncerRed   = Bounce();
Bounce debouncerGreen = Bounce();
Bounce debouncerBlue  = Bounce();
Bounce debouncerBlack = Bounce();


int respLight;
int heartLight;
int gsrLight;


int heartLed =  4;    //red
int gsrLed   =  5;    //green
int respLed  =  6;    //blue

boolean configMode  = false;

boolean redToggle   = false;   // you can separate different sounds by using these boolean logics
boolean greenToggle = false;
boolean blueToggle  = false;





char h_beat_notes[] = {0, 2, 4, 5 , 7 , 9, 11}; //char h_beat_notes[] = {0, 2, 4, 5 , 7 , 9, 11};

Arpegiator arp(h_beat_notes, 7); // MIDI note array and its size

int h_beat_voice = 0;
Chrono voice1Chrono;
bool voice1IsPlaying = false;
Chrono voice2Chrono;
bool voice2IsPlaying = false;


#include <AsciiMassenger.h>
AsciiMassenger msg; // By default, AsciiMassenger uses Serial.

bool manualMode = false;

int instrument = 0;

Chrono bpmChrono;

float bpm = 120;

#include "MinMax.h"
MinMax heartMinMax = MinMax();
MinMax gsrMinMax = MinMax();

#include "Threshold.h"
Threshold heartThresh = Threshold(0.25, 0.75);

#include "Lop.h"
Lop gsrLop = Lop(0.001);
#include "Hip.h"
Hip gsrHip = Hip(0.9999);//Hip(0.9999);
Lop heartSensorAmplitudeLop = Lop(0.001  );
Lop heartSensorBpmLop = Lop(0.001);
float heartSensorAmplitudeLopValue;
float heartSensorBpmLopValue;
MinMax heartSensorAmplitudeLopValueMinMax = MinMax();
float heartSensorAmplitudeLopValueMinMaxValue;
MinMax heartSensorBpmLopValueMinMax = MinMax();
float heartSensorBpmLopValueMinMaxValue;

float heartSensorFiltered = 0;
float heartSensorAmplitude = 0;

float gsrSensorFiltered = 0;
float gsrSensorAmplitude = 0;
float gsrSensorLop = 0;
float gsrSensorChange = 0;

void setup(void)
{

  noise1.amplitude(0.1);
  sine_fm2.frequency(622);      //harmonics of Eb -  1-622 2-933
  // 3-1244 4- 1555 5-1866
  // 6- 2177 7- 2488
  sine_fm2.amplitude(0.0);

  Serial.begin(115200);
  AudioMemory(30);   //This might need to be adjusted, depending.

  h_beat_waveform1.begin(0.4, 1020, WAVEFORM_SINE);  //something below 32Hz displays a clear beating pattern rathern than modulation
  h_beat_sine_fm1.frequency(500);   //this is the same amplitude as one of the atmospheric sine waves
  h_beat_sine_fm1.amplitude(0.2);
  h_beat_envelope1.attack(10);            //attack envelope for heartbeat
  h_beat_envelope1.decay(10);
  h_beat_envelope1.sustain(0.9);
  h_beat_envelope1.release(25);

  h_beat_waveform2.begin(0.4, 1020, WAVEFORM_SINE);  //something below 32Hz displays a clear beating pattern rathern than modulation
  h_beat_sine_fm2.frequency(500);   //this is the same amplitude as one of the atmospheric sine waves
  h_beat_sine_fm2.amplitude(0.2);
  h_beat_envelope2.attack(10);            //attack envelope for heartbeat
  h_beat_envelope2.decay(10);
  h_beat_envelope2.sustain(0.9);
  h_beat_envelope2.release(25);



  waveform2.begin(0.004, 1, WAVEFORM_SINE);
  sine_fm3.frequency(311);           //atmospheric sines
  sine1.frequency(424);
  sine_fm3.amplitude(0); //sine_fm3.amplitude(0.1);
  sine1.amplitude(0);//sine1.amplitude(0.03);


  waveform3.begin(0.05, 1, WAVEFORM_SINE);
  sine_fm4.frequency(622);
  sine_fm4.amplitude(0);//sine_fm4.amplitude(0.025);

  outputFilter.frequency(500);
  outputFilter.resonance(0.7); //Set the filter's resonance. Q ranges from 0.7 to 5.0.

  // set bits to 16 and sampleRate to 44100 to pass audio through without any Bitcrush effect.
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);



  pinMode(heartLed, OUTPUT);      //led for heart signal
  pinMode(respLed, OUTPUT);       //ostensibly this led would be resp signal but screw that for now
  pinMode(gsrLed, OUTPUT);        // led for gsr above average reporting
  pinMode(17, OUTPUT);

  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(blackButton, INPUT_PULLUP);

  //setting up the Bounce instance :
  debouncerRed.attach(redButton);
  debouncerRed.interval(20);        // inverval in ms
  debouncerGreen.attach(greenButton);
  debouncerGreen.interval(20);      // inverval in ms
  debouncerBlue.attach(blueButton);
  debouncerBlue.interval(20);       // inverval in ms
  debouncerBlack.attach(blackButton);
  debouncerBlack.interval(20);      // inverval in ms

  arp.setBpm(bpm);

}



void loop() {

 receiveMessages();

 processHeart();

 processGsr();

 arpegiatorLoop();


  analogWrite(respLed, 0);

  analogWrite(gsrLed, gsrSensorFiltered * 255);

  analogWrite(heartLed, heartSensorFiltered * 255);

  int harmonies = bpm * 1.25;
  if (harmonies > 140) harmonies = 140;
  waveform3.frequency(heartSensorAmplitude / 100);
  sine_fm4.frequency(harmonies);

}





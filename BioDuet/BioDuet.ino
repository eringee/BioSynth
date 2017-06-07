/*********************************/
/*********************************/

#define box 1   // 1 or 2 or 3

/**********************************/
/*********************************/
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Chrono.h>
#include <Bounce2.h>    // debouncing library

#include "notes.h"
#include "Arpegiator.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       h_beat_waveform2;      //xy=233,107
AudioSynthWaveform       h_beat_waveform1;      //xy=240,54
AudioSynthWaveform       waveform1;      //xy=382,515
AudioSynthWaveform       bassnoteVibrato;      //xy=424,341
AudioSynthWaveformSineModulated h_beat_sine_fm2; //xy=436,109
AudioSynthWaveformSineModulated h_beat_sine_fm1; //xy=444,57
AudioSynthNoiseWhite     noise;         //xy=460,274
AudioSynthWaveformSineModulated sine_fm2;       //xy=568,480
AudioSynthWaveformSineModulated sine_fm1;       //xy=571,432
AudioSynthWaveformSineModulated sine_fm3;       //xy=578,523
AudioFilterStateVariable filter1;        //xy=582,281
AudioSynthKarplusStrong  string1;        //xy=583,166
AudioSynthSimpleDrum     drum1;          //xy=583,217
AudioSynthWaveformSineModulated sine_fm4;       //xy=600,588
AudioEffectEnvelope      h_beat_envelope2; //xy=624,109
AudioSynthWaveformSineModulated bassnote;       //xy=625,339
AudioEffectEnvelope      h_beat_envelope1; //xy=660,57
AudioEffectEnvelope      sine_envelope3;      //xy=747,523
AudioEffectEnvelope      sine_envelope1;      //xy=748,430
AudioEffectEnvelope      sine_envelope2;      //xy=749,487
AudioEffectEnvelope      sine_envelope4;      //xy=801,588
AudioMixer4              Arp_mixer;         //xy=808,137
AudioMixer4              SinesMixer;         //xy=931,471
AudioMixer4              ExtraMixer;         //xy=949,248
AudioMixer4              mixer4;         //xy=953,589
AudioEffectBitcrusher    bitcrusher1;    //xy=1090,589
AudioFilterStateVariable outputFilter;   //xy=1237,594
AudioOutputAnalog        dac1;           //xy=1373,581
AudioConnection          patchCord1(h_beat_waveform2, h_beat_sine_fm2);
AudioConnection          patchCord2(h_beat_waveform1, h_beat_sine_fm1);
AudioConnection          patchCord3(waveform1, sine_fm2);
AudioConnection          patchCord4(waveform1, sine_fm3);
AudioConnection          patchCord5(waveform1, sine_fm4);
AudioConnection          patchCord6(waveform1, sine_fm1);
AudioConnection          patchCord7(bassnoteVibrato, sine_fm1);
AudioConnection          patchCord8(h_beat_sine_fm2, h_beat_envelope2);
AudioConnection          patchCord9(h_beat_sine_fm1, h_beat_envelope1);
AudioConnection          patchCord10(noise, 0, filter1, 0);
AudioConnection          patchCord11(sine_fm2, sine_envelope2);
AudioConnection          patchCord12(sine_fm1, sine_envelope1);
AudioConnection          patchCord13(sine_fm3, sine_envelope3);
AudioConnection          patchCord14(filter1, 0, ExtraMixer, 1);
AudioConnection          patchCord15(string1, 0, Arp_mixer, 2);
AudioConnection          patchCord16(drum1, 0, Arp_mixer, 3);
AudioConnection          patchCord17(sine_fm4, sine_envelope4);
AudioConnection          patchCord18(h_beat_envelope2, 0, Arp_mixer, 1);
AudioConnection          patchCord19(bassnote, 0, ExtraMixer, 2);
AudioConnection          patchCord20(h_beat_envelope1, 0, Arp_mixer, 0);
AudioConnection          patchCord21(sine_envelope3, 0, SinesMixer, 3);
AudioConnection          patchCord22(sine_envelope1, 0, SinesMixer, 1);
AudioConnection          patchCord23(sine_envelope2, 0, SinesMixer, 2);
AudioConnection          patchCord24(sine_envelope4, 0, mixer4, 1);
AudioConnection          patchCord25(Arp_mixer, 0, ExtraMixer, 0);
AudioConnection          patchCord26(SinesMixer, 0, mixer4, 0);
AudioConnection          patchCord27(ExtraMixer, 0, SinesMixer, 0);
AudioConnection          patchCord28(mixer4, bitcrusher1);
AudioConnection          patchCord29(bitcrusher1, 0, outputFilter, 0);
AudioConnection          patchCord30(outputFilter, 0, dac1, 0);
//////NEW GSR ITEMS BEGIN//////////////////////////////

#include <Average.h>    // library for averaging data

Average<float> GSRaverager(1250);  //1250
Average<float> GSRlightav(1000);
Average<float> gsrLighter(500);

int gsrSensorReading;
float GSRmastered;   //The final GSR 
float GSRmax;
float GSRav;
int gsrLightFinal;
int maxat = 0;

boolean gsrStage1 = false;
boolean gsrStage2 = false;
boolean gsrStage3 = false;
boolean gsrStage4 = false;

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

#define MODE_DEFAULT 0x0
#define MODE_RED     0x1
#define MODE_BLUE    0x2
#define MODE_GREEN   0x3
#define MODE_NONE    0x4
int mode = MODE_DEFAULT;

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
Lop gsrLop = Lop(0.001); //0.001
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
  Serial.begin(115200);

    AudioMemory(30);   //This might need to be adjusted, depending.

  outputFilter.frequency(500);
  outputFilter.resonance(0.7); //Set the filter's resonance. Q ranges from 0.7 to 5.0.

  // set bits to 16 and sampleRate to 44100 to pass audio through without any Bitcrush effect.
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);

  arp.setBpm(bpm);
  
  //Arpeggiator envelopes I guess?
  
  h_beat_waveform1.begin(0.4, 1020, WAVEFORM_SINE);  //something below 32Hz displays a clear beating pattern rathern than modulation
  h_beat_sine_fm1.frequency(500);   
  h_beat_sine_fm1.amplitude(0.2);
  h_beat_envelope1.attack(10);            
  h_beat_envelope1.decay(10);
  h_beat_envelope1.sustain(0.9);
  h_beat_envelope1.release(25);

  h_beat_waveform2.begin(0.4, 1020, WAVEFORM_SINE);  //something below 32Hz displays a clear beating pattern rathern than modulation
  h_beat_sine_fm2.frequency(500);   
  h_beat_sine_fm2.amplitude(0.2);
  h_beat_envelope2.attack(10);       
  h_beat_envelope2.decay(10);
  h_beat_envelope2.sustain(0.9);
  h_beat_envelope2.release(25);

  pinMode(heartLed, OUTPUT);      //led for heart signal
  pinMode(respLed, OUTPUT);       //ostensibly this led would be resp signal but screw that for now
  pinMode(gsrLed, OUTPUT);        // led for gsr above average reporting

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

///blink lights to let you know which box it is//

  digitalWrite(heartLed, HIGH); 
  digitalWrite(respLed, HIGH);
  digitalWrite(gsrLed, HIGH);  
  delay(300);
  if (box >= 2) {               
    digitalWrite(heartLed, LOW);  
    digitalWrite(respLed, LOW);
    digitalWrite(gsrLed, LOW);  
    delay(300);
       if (box == 3) {
        digitalWrite(heartLed, HIGH); 
        digitalWrite(respLed, HIGH);
        digitalWrite(gsrLed, HIGH);  
        delay(300);
       }
    }
 }

elapsedMillis every4;

void loop() {
  
 processHeart();  //only needs to be 250Hz (4 millis)
 processGsr();    //only needs to be 100Hz (6 millis) take avg over 4 seconds and subtract from signal to eliminate noise

 readButtons();
 receiveMessages();
 updateLeds();

 arpegiatorLoop(); 

 processMode();
 
}

void processMode() {
  if (!redToggle && !greenToggle && !blueToggle) {
    if (mode != MODE_DEFAULT)
      setupModeDefault(); // enter state
     runModeDefault();
     mode = MODE_DEFAULT;
  }
  
  else if (redToggle && !greenToggle && !blueToggle) {
   if (mode != MODE_RED)
     setupRedMode(); // enter state
    runRedMode();
    mode = MODE_RED;
 }

if (!redToggle && greenToggle && !blueToggle) {
  if (mode != MODE_GREEN)
   setupGreenMode(); // enter state
   runGreenMode();
   mode = MODE_GREEN;
 }
 
 if (!redToggle && !greenToggle && blueToggle) {
   if (mode != MODE_BLUE)
     setupBlueMode(); // enter state
     runBlueMode();
     mode = MODE_BLUE;
  }

}

void setMode(int newMode) {
  mode = newMode;
}



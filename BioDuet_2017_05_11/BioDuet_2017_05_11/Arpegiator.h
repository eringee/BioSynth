
#include <Chrono.h>

int progressionssion[] = {0, 2, 4, 5 , 7 , 9, 11};


class Arpegiator {
    int step = 0;
    int stepCount = 0;
 
    
    Chrono stepChrono;
    char* notes;
    int notesLength;
    bool forceNoteOnNextCheck = false;

    bool legato = false;
    int offset = 0;
    int division = 1;

    int octave = 3;
    int steps = 3;
    float bpm = 120;

    bool loop = false;

    int note = 60;

    int increment  = 1;

    bool playing = false;

  public:
    Arpegiator( char notes[] , int size  ) {  //

      this->notes = notes;
      notesLength = size;

      //progressionssion0[] = {0, 2, 4, 5 , 7 , 9, 11};

    }

   void setBpm( float bpm ) {
    this->bpm = bpm;
   }

   void setSteps( int steps ) {
      steps = max(1,steps);
      this->steps = steps;
   }

     void setDivision( int division ) {
      division = max(1,division);
      this->division = division;
   }

     void setOffset( int offset ) {
      offset = max(0,offset);
      this->offset = offset;
   }
   
   void setOctave ( int octave ) {
      octave = max(0,octave);
      this->octave = octave;
   }

    void setLegato ( bool legato ) {
      this->legato = legato;
   }

   void setLoop ( bool loop ) {
      this->loop = loop;
   }


 void setIncrement( int increment ) {
  this->increment = increment;
 }

    
    void trigger() {
      
      if ( legato == false ) step = 0;
      stepCount = 0;
      
      if ( legato == false || playing == false ) {
        forceNoteOnNextCheck = true;
        stepChrono.restart();
      }
      playing = true;
    }



    boolean check() {

     if ( playing == false ) return false;
     
      if ( forceNoteOnNextCheck || stepChrono.hasPassed( 60000. / (bpm*division)) ) {
        stepChrono.restart();
        forceNoteOnNextCheck = false;

        int index = (step*increment+offset);
        while ( index < 0 ) index = index + notesLength;
        index = index % notesLength;
        note = notes[ index ] + octave * 12;
        
        step = (step + 1);
        step = step % steps;
        
        stepCount++;
        if ( stepCount >= steps ) {
          if ( loop ) stepCount = 0;
          else playing = false;
        }
        
        return true;
      }
      return false;
    }

    int getStep() {

      return step;

    }

    int getNote() {
      
      return note;
      
    }

    int getFreq() {

      return noteToFequency( getNote() );
    }


};

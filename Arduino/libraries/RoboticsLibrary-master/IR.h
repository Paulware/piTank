#ifndef IR_Class_h
#define IR_Class_h

#include <Arduino.h>
#include <TimerOne.h>
#include <avr/interrupt.h>

#define MAXIRCOUNTS 16


class IR {

public:
  
   IR (int irrcvpin )
   {
     rcvpin = irrcvpin;
     if (rcvpin != 0) { 
       pinMode (rcvpin, INPUT);
       resetIR();
     }  
   }
   
   // IR constructor for transmission
   IR () 
   {    
   }

   void transmit (bool on) {
      if (on) {  
         TCCR2A |= _BV(COM2B1); // Enable pin 3 PWM output       
      } 
      else // off
      {
         TCCR2A &= ~(_BV(COM2B1)); // Disable pin 3 PWM output
      } 
   } 
   
   void enableIROut() 
   {
     #define SYSCLOCK 16000000  // main Arduino clock
     int khz = 38;

     // Enables IR output.  The khz value controls the modulation frequency in kilohertz.
     // The IR output will be on pin 3 (OC2B).
     // This routine is designed for 36-40KHz; if you use it for other values, it's up to you
     // to make sure it gives reasonable results.  (Watch out for overflow / underflow / rounding.)
     // TIMER2 is used in phase-correct PWM mode, with OCR2A controlling the frequency and OCR2B
     // controlling the duty cycle.
     // There is no prescaling, so the output frequency is 16MHz / (2 * OCR2A)
     // To turn the output on and off, we leave the PWM running, but connect and disconnect the output pin.
     // A few hours staring at the ATmega documentation and this will all make sense.
     // See my Secrets of Arduino PWM at http://arcfn.com/2009/07/secrets-of-arduino-pwm.html for details.

     
     // Disable the Timer2 Interrupt (which is used for receiving IR)
     // TIMSK2 &= ~_BV(TOIE2); //Timer2 Overflow Interrupt
     // atmega168
     // Not sure about next line
     //TIMSK1 &= ~_BV(OCIE1A); // Disable the interrupt that is used to read RF

     pinMode(3, OUTPUT);
     digitalWrite(3, LOW); // When not sending PWM, we want it low
     
     // COM2A = 00: disconnect OC2A
     // COM2B = 00: disconnect OC2B; to send signal set to 10: OC2B non-inverted
     // WGM2 = 101: phase-correct PWM with OCRA as top
     // CS2 = 000: no prescaling
     TCCR2A = _BV(WGM20);
     TCCR2B = _BV(WGM22) | _BV(CS20);

     // The top value for the timer.  The modulation frequency will be SYSCLOCK / 2 / OCR2A.
     OCR2A = SYSCLOCK / 2 / khz / 1000;
     OCR2B = OCR2A / 2;  // 50% duty cycle... / 3; =  33% duty cycle
   }

   
   // Reset all on/off information 
   void resetIR()
   {
     for (int i=0; i<MAXIRCOUNTS; i++)
     {
       onCounts [i] = 0;
       offCounts[i] = 0;
     }
     lastIR = 1; // off inverse logic
     irCount = 0;
     first = true;
     offHead = 0;
     offTail = 0;
     irReady = false;
   }

   // This procedure will run at 50 microseconds
   void callback() 
   {
     if (!irReady) // Not ready to be consumed yet
     {
       byte ir = digitalRead (rcvpin); 
       if (ir != lastIR)
       {
         if (ir) // transition to off
         {
           onCounts[offHead] = irCount;
           if (offHead == offTail) // Queue is full, lose one tail value
             offTail = ++offTail % MAXIRCOUNTS;
           // Increment Head/Tail
           offHead = ++offHead % MAXIRCOUNTS;
         }
         else // transition to on 
         {
           /* 
             The first transition to on should be preceded by a 
             long off period.  This period is variable and has 
             nothing to do with the actual pulses being generated.
           */
           if (first) // ignore 
             offCounts[offHead] = 0;
           else
             offCounts[offHead] = irCount;
           first = false;  
         }
         irCount = 0;
       }
       
       if (ir) // pulse is off 
       {
         if (!first) // ir is off (reverse logic)
         {
           if (irCount < 1500)
             irCount = irCount + 1;
           else 
             irReady = true; // It has been off long enough
         }
       }
       else if (irCount < 32767) 
         irCount = irCount + 1;
       
       lastIR = ir;
     }  
   }

   // Decode where information is defined in the off-time rather than the 
   // standard on-time.
   unsigned int decodeBits (int maxLow, bool onOff, bool debug)
   {
     int counts;
     int head = offHead;
     int tail = offTail;
     unsigned int val; 
     bool first = true;
     val = 0;
     
     if (irReady)
     {  
       if (debug)
       {
         Serial.print ( "head: " );
         Serial.print ( head );
         Serial.print ( " tail:" );
         Serial.println ( tail );
       }  

       while ((head != tail) || first) 
       {  
         first = false;
         if (onOff) 
           counts = onCounts[tail];
         else
           counts = offCounts[tail];
         val = val * 2;
         if (counts > maxLow) 
           val++;
         tail = ++tail % MAXIRCOUNTS;
       } 

       if (debug)
       {  
         head = offHead;
         tail = offTail;
         val = 0;
         first = true;
         while ((head != tail) || first)
         { 
           first = false;	  
           if (onOff)
             counts = onCounts[tail];
           else  
             counts = offCounts[tail];
           val = val * 2;
           if (counts > maxLow) 
             val++;
           if (debug)
           { 
             Serial.print ( "[" );
             if (tail <10)
                Serial.print ( "0" );
             Serial.print ( tail );
             Serial.print ( "]: " );
             Serial.println (counts);
           }
           tail = ++tail % MAXIRCOUNTS;
         } 
         if (onOff)
           Serial.print ("Decoded ON bits maxLow(");
         else
           Serial.print ("Decoded OFF bits maxLow(" );
         Serial.print ( maxLow );
         Serial.print ( "):");
         Serial.println ( val,HEX );
         lastDecodedValue = val;
       }    
     }
     return val;
   }

  unsigned int irValue( void )
  {
    unsigned int val; // IR value
    int check;
    bool shot = false;
    if (irReady) {
       val = decodeBits (15, true, false);    
       resetIR(); 
       if (val != 0) { 
          lastDecodedValue = val; 
       }
    }    
    return val;
  }  
    
  void showLastVal () {
     if (lastDecodedValue != 0) {
         Serial.print ( "IR value detected:" );
         Serial.println ( lastDecodedValue );
         lastDecodedValue = 0; // Consume it.
     } 
  } 
  
  void update() {
     lastDecodedValue = irValue();
  }
  
  // fields
  bool irReady;  
  int lastDecodedValue=0;
 

 
private:
  int rcvpin;  
  byte lastIR;
  int onCounts [MAXIRCOUNTS];
  int offCounts[MAXIRCOUNTS];
  int offHead; // head offset always points to next available
  int offTail; // tail offset
  int irCount;
  bool first;
};

class IRCallback {
 public:
   // Timer1 is set to 25 microsecond to balance PWM output
   static void callback() 
   {
      static bool skip = false;
      skip = !skip;
      if (!skip)
         irReceive.callback();
   }
   static void initialize() {
      Timer1.initialize(25);
      Timer1.attachInterrupt (callback,25);      
   }  
 
   static int irValue() {
      return irReceive.irValue();
   }
   static void showLastVal() {
      irReceive.showLastVal();
   }
   static void update() {
      irReceive.update();
   }    
   static IR irReceive;
}; 

#endif
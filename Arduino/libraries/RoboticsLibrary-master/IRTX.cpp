#include "IRTX.h"
#include "IRPulses.h" 
/* Leave pin off for time (given in microseconds) */
void IRTX::space(int time) {
  // Sends an IR space for the specified number of microseconds.
  // A space is no output, so the PWM output is disabled.
  TCCR2A &= ~(_BV(COM2B1)); // Disable pin 3 PWM output
  delayMicroseconds(time * 50);
}
void IRTX::sendRaw(unsigned int uDelay, int index)
{

  if (index & 1)
    TCCR2A &= ~(_BV(COM2B1)); // Disable pin 3 PWM output
  else 
    TCCR2A |= _BV(COM2B1); // Enable pin 3 PWM output
    
  delayMicroseconds(uDelay);
}

void IRTX::enableIROut() 
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


/* 
   Limitation: 
      You cannot place any Serial.println instructions here.
	  The program will not run 
*/
void IRTX::fire (void)
{
  unsigned int myDelay;  

  enableIROut();
  for (int i=0; i<4; i++){
    for (int j = 0; j < HUANPULSES; j++) {
      myDelay = huanQiPulses[j];
      sendRaw (myDelay, j);
    }
  }
   
}

void IRTX::fireData(void)
{
  unsigned int myDelay;
  Serial.print ("Sh");
  //Timer1->stop();
  enableIROut();
  for (int j = 0; j < 32; j++) {
    myDelay = firePulses[j];
    sendRaw (myDelay, j);
  }
  //Timer1->resume();   
}

void IRTX::sendFirePulse(void)
{
  unsigned int myDelay;
  
  enableIROut();
  fireType--;
  switch (fireType)
  {
    default:
	     break;
    
    case 6:
      for (int i=0; i<3; i++)
      {
        for (int j = 0; j < MICROHUANQI; j++) 
        {
          myDelay = microHuanQi[j];
          sendRaw (myDelay, j);
        }
      }
    break;
    
	   
    case 5:
      for (int i=0; i<4; i++)
      {
        for (int j = 0; j < MINITANK; j++) 
        {
          myDelay = miniTankPulses[j];
          sendRaw (myDelay, j);
        }
      }
        
    break;
     
    case 4:  
      for (int i=0; i<4; i++)
      {
        for (int j = 0; j < HUANPULSES; j++) 
        {
          myDelay = huanQiPulses[j];
          sendRaw (myDelay, j);
        }
      }
    break;
      
    case 3:
      for (int j=0; j<FOVPULSES; j++) 
      {
        myDelay = FOVPulses[j];
        sendRaw (myDelay, j);
      }  
      space(0); // Just to be sure
    break;
        
    case 2:
      for (int j=0; j<DANBARPULSES; j++) 
      {
        myDelay = DanbarPulses[j];
        sendRaw (myDelay, j);
      }
      space(0); // Just to be sure    
    break;
        
    case 1: 
      for (int i=0; i<2; i++)
      {
        for (int j=0; j<AIRBENDERPULSES; j++)
        {
          myDelay = airBenderPulses[j];
          sendRaw (myDelay,j);
        }
        space(0); // Just to be sure
      }    
    break;
        
    case 0:
      for (int i=0; i<2; i++) {
   	    if (repairRobot) {
          for (int j=0; j<REPAIRPULSES; j++)
          {
            myDelay = repairPulses[j];
            sendRaw (myDelay,j);
          }
      		} else {
          for (int j=0; j<BATTLEMACHINEPULSES; j++)
          {
            myDelay = battleMachinePulses[j];
            sendRaw (myDelay,j);
          }
      		}  
        space(0); // Just to be sure
      }
    break;              
  }  
}

/* 
   Limitation: 
      You cannot place any Serial.println instructions here.
	  The program will not run 
*/
void IRTX::fireAll (void)
{
  //Timer1->stop();
  sendFirePulse(); // Update fireTimeout and send pulse
  //Timer1->resume();   
}

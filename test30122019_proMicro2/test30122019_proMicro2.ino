#include <Keyboard.h>
#include "HID.h"

const int pinLed = LED_BUILTIN;

const int ledPin_spindle = 13;  
const int ledPin_feedrate = 13;     

const int buttonPin_spindle = 14;       //spindle reset
const int encoder0PinA_spindle = 15;    //spindle increase
const int encoder0PinB_spindle = 16;    //spindle decrease

const int buttonPin_feedrate = 2;       //feedrate reset
const int encoder0PinA_feedrate = 3;    //feedrate increase
const int encoder0PinB_feedrate = 4;    //feedrate decrease

const int button_R100=5;                //R100
const int button_R50=6;                 //R50
const int button_R25 = 7;               //R25

const int button_probe = 8;             //Probing   

// case for spindle 
int bstate_spindle = 0; //0 is paused, 1 is playing
int ledState_spindle = HIGH;         // the current state of the output pin
int buttonState_spindle;             // the current reading from the input pin
int lastButtonState_spindle = LOW;   // the previous reading from the input pin
long lastDebounceTime_spindle = 0;  // the last time the output pin was toggled
long debounceDelay_spindle = 50;    // the debounce time; increase if the output flickers
long longpressDelay_spindle = 500;    // If we hold it longer than 500ms then it is a long press.
int val_spindle;
int encoder0Pos_spindle = 0;
int encoder0PinALast_spindle = LOW;
long encoderLastValue_spindle=0;
//int lastCommand; //0=volup 1=voldown 2=next, 3=prev
int lastDirection_spindle; //0=--, 1=++
int n_spindle = LOW;
int reading_spindle;
float fo_spindle=100;

// case for feedrate
int bstate_feedrate = 0; //0 is paused, 1 is playing
int ledState_feedrate = HIGH;         // the current state of the output pin
int buttonState_feedrate;             // the current reading from the input pin
int lastButtonState_feedrate = LOW;   // the previous reading from the input pin
long lastDebounceTime_feedrate = 0;  // the last time the output pin was toggled
long debounceDelay_feedrate = 50;    // the debounce time; increase if the output flickers
long longpressDelay_feedrate = 500;    // If we hold it longer than 500ms then it is a long press.
int val_feedrate;
int encoder0Pos_feedrate = 0;
int encoder0PinALast_feedrate = LOW;
long encoderLastValue_feedrate=0;
//int lastCommand; //0=volup 1=voldown 2=next, 3=prev
int lastDirection_feedrate; //0=--, 1=++
int n_feedrate = LOW;
int reading_feedrate;
float fo_feedrate=100;



void setup() {
  
  pinMode(ledPin_spindle, OUTPUT);
  pinMode(buttonPin_spindle, INPUT_PULLUP);
  pinMode(encoder0PinA_spindle, INPUT_PULLUP);
  pinMode(encoder0PinB_spindle, INPUT_PULLUP);
  digitalWrite(ledPin_spindle, ledState_spindle);
  

  pinMode(ledPin_feedrate, OUTPUT);
  pinMode(buttonPin_feedrate, INPUT_PULLUP);
  pinMode (encoder0PinA_feedrate, INPUT_PULLUP);
  pinMode (encoder0PinB_feedrate, INPUT_PULLUP);
  digitalWrite(ledPin_feedrate, ledState_feedrate);
  
  pinMode(button_R100, INPUT_PULLUP);
  pinMode(button_R50, INPUT_PULLUP);
  pinMode(button_R25, INPUT_PULLUP);

  pinMode(button_probe, INPUT_PULLUP);
  
  Serial.begin (9600);
  
}

void loop() {
  //spindle code
  n_spindle = digitalRead(encoder0PinA_spindle);
  if ((encoder0PinALast_spindle == LOW) && (n_spindle == HIGH)) {
    if (digitalRead(encoder0PinB_spindle) == LOW) { 
      //to make a double check we are going the right direction.
      if (lastDirection_spindle == 0) {
        encoder0Pos_spindle--;
      }
      lastDirection_spindle = 0;
    } else {
      if (lastDirection_spindle == 1) {
        encoder0Pos_spindle++;
      }
      lastDirection_spindle = 1;
    }
  }
  encoder0PinALast_spindle = n_spindle;
  
  //We make the vol up/down descision with the lastButttonState.
  if (lastButtonState_spindle == HIGH) { //((millis() - lastDebounceTime) < longpressDelay) 
    //nothing happens with the button so if the rotary encoder moves now, it is volume. 
    //Well actually this code runs also if the button isnt released, so we need to make sure it isnt a longpress aswell... which we do two rows up.
    if (encoderLastValue_spindle > encoder0Pos_spindle) {
      //volume down
//      Remote.decrease();
//      Remote.clear();
      Serial.println ("spindle negative");
       
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('z');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('z');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    delay(200);
    
    digitalWrite(pinLed, LOW);
    }
    else if (encoderLastValue_spindle < encoder0Pos_spindle) {
      //volume up
//      Remote.increase();
 //     Remote.clear();
      Serial.println ("spindle positive");
   
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('e');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('e');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    delay(200);
    
    digitalWrite(pinLed, LOW);
      
   
    }
  }
  
  //We must make the next/prev descisions before the button press if.
  if (((millis() - lastDebounceTime_spindle) > longpressDelay_spindle) && (lastButtonState_spindle == LOW)) {
    //So if the button has been held longer than 500ms, then if the rotary encoder is turned it is next/prev
    if (encoderLastValue_spindle > encoder0Pos_spindle) {
//      previous
//      Remote.previous();
 //     Remote.clear();
      delay(500);
    //  Serial.println ("Previous");
    }
    else if (encoderLastValue_spindle < encoder0Pos_spindle) {
//      next
//      Remote.next();
//      Remote.clear();
      delay(500);
  //    Serial.println ("Next");
    }
  } 
  
  //button_code_spindle
  reading_spindle = digitalRead(buttonPin_spindle);
  if (reading_spindle != lastButtonState_spindle) {
    //The button is (probalby) pressed or released
    if (reading_spindle==LOW) {
      //if it indeed is pressed then:
      //Set the start time
      lastDebounceTime_spindle = millis();
    } else {
       //if it is high the button was released, check how long time it was pressed...
       if ((millis() - lastDebounceTime_spindle) > longpressDelay_spindle) {
         //the button was pressed 500ms or longer
         //we cant handle next/prev here because here the button is already released again, se code above for next/prev...
         Serial.println ("spindle reset");

         digitalWrite(pinLed, HIGH);
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('x');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('x');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        delay(200);
        
        digitalWrite(pinLed, LOW);
       }
       else if ((millis() - lastDebounceTime_spindle) > debounceDelay_spindle) {
          //it was only pressed a short while, but more than 50ms so it is a play/pause press
          Serial.println ("quick spindle reset");
          digitalWrite(pinLed, HIGH);
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('x');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('x');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        delay(200);
        
        digitalWrite(pinLed, LOW);
          if (bstate_spindle == 0) {
//             Remote.play();
        //     Remote.clear();
             bstate_spindle = 1;
           } else {
             //Remote.pause();
          //   Remote.clear();
             bstate_spindle = 0;
           }
       } else {
         Serial.println (millis()-lastDebounceTime_spindle);
       }
    }
  }
  
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState_spindle = reading_spindle;
  encoderLastValue_spindle=encoder0Pos_spindle;
















   //feedrate code
   
  n_feedrate = digitalRead(encoder0PinA_feedrate);
  if ((encoder0PinALast_feedrate == LOW) && (n_feedrate == HIGH)) {
    if (digitalRead(encoder0PinB_feedrate) == LOW) { 
      //to make a double check we are going the right direction.
      if (lastDirection_feedrate == 0) {
        encoder0Pos_feedrate--;
      }
      lastDirection_feedrate = 0;
    } else {
      if (lastDirection_feedrate == 1) {
        encoder0Pos_feedrate++;
      }
      lastDirection_feedrate = 1;
    }
  }
  encoder0PinALast_feedrate = n_feedrate;
  
  //We make the vol up/down descision with the lastButttonState.
  if (lastButtonState_feedrate == HIGH) { //((millis() - lastDebounceTime) < longpressDelay) 
    //nothing happens with the button so if the rotary encoder moves now, it is volume. 
    //Well actually this code runs also if the button isnt released, so we need to make sure it isnt a longpress aswell... which we do two rows up.
    if (encoderLastValue_feedrate > encoder0Pos_feedrate) {
      //volume down
//      Remote.decrease();
//      Remote.clear();
      Serial.println ("feedrate negative");

      digitalWrite(pinLed, HIGH);
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('a');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('a');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        delay(200);
        
        digitalWrite(pinLed, LOW);
      
  
    }
    else if (encoderLastValue_feedrate < encoder0Pos_feedrate) {
      //volume up
//      Remote.increase();
 //     Remote.clear();
      Serial.println ("feedrate positive");


      digitalWrite(pinLed, HIGH);
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('q');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('q');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        delay(200);
        
        digitalWrite(pinLed, LOW);
   
    }
  }
  
  //We must make the next/prev descisions before the button press if.
  if (((millis() - lastDebounceTime_feedrate) > longpressDelay_feedrate) && (lastButtonState_feedrate == LOW)) {
    //So if the button has been held longer than 500ms, then if the rotary encoder is turned it is next/prev
    if (encoderLastValue_feedrate > encoder0Pos_feedrate) {
//      previous
//      Remote.previous();
 //     Remote.clear();
      delay(500);
      Serial.println ("Previous");
    }
    else if (encoderLastValue_feedrate < encoder0Pos_feedrate) {
//      next
//      Remote.next();
//      Remote.clear();
      delay(500);
      Serial.println ("Next");
    }
  } 
  
  //button_code
  reading_feedrate = digitalRead(buttonPin_feedrate);
  if (reading_feedrate != lastButtonState_feedrate) {
    //The button is (probalby) pressed or released
    if (reading_feedrate==LOW) {
      //if it indeed is pressed then:
      //Set the start time
      lastDebounceTime_feedrate = millis();
    } else {
       //if it is high the button was released, check how long time it was pressed...
       if ((millis() - lastDebounceTime_feedrate) > longpressDelay_feedrate) {
         //the button was pressed 500ms or longer
         //we cant handle next/prev here because here the button is already released again, se code above for next/prev...
         Serial.println ("Feedrate reset");

       
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('p');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('p');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        delay(200);
          digitalWrite(pinLed, HIGH);
    
        digitalWrite(pinLed, LOW);
         
       }
       else if ((millis() - lastDebounceTime_feedrate) > debounceDelay_feedrate) {
          //it was only pressed a short while, but more than 50ms so it is a play/pause press
          Serial.println ("quick feedrate reset");
            Serial.println ("Feedrate reset");

       
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('p');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('p');
        Keyboard.releaseAll();
    
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
    
        delay(200);
          digitalWrite(pinLed, HIGH);
    
        digitalWrite(pinLed, LOW);
    
          if (bstate_feedrate == 0) {
//             Remote.play();
        //     Remote.clear();
             bstate_feedrate = 1;
           } else {
             //Remote.pause();
          //   Remote.clear();
             bstate_feedrate = 0;
           }
       } else {
         Serial.println (millis()-lastDebounceTime_feedrate);
       }
    }
  }
  
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState_feedrate = reading_feedrate;
  encoderLastValue_feedrate=encoder0Pos_feedrate;


  //Probing
  if(!digitalRead(button_probe)){
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('v');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('v');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    delay(200);
    
    digitalWrite(pinLed, LOW);
  }
  
  //R100
  if (!digitalRead(button_R100)) {
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('j');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('j');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    delay(200);
    
    digitalWrite(pinLed, LOW);
  }
  
  //R50
   if (!digitalRead(button_R50)) {
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('k');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('k');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    delay(200);
    
    digitalWrite(pinLed, LOW);
  }
  //R25
   if (!digitalRead(button_R25)) {
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    Keyboard.releaseAll();
   
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    delay(200);
    
    
    digitalWrite(pinLed, LOW);
  }
 
  


}

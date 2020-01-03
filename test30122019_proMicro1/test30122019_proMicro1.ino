#include "HID-Project.h"
const int pinLed = LED_BUILTIN;

const int button_JogDecrease = 2; //Tested Ok
const int button_JogIncrease = 5; //Tested Ok
const int button_Unlock = 3;  //Tested Ok... but special form of u is printed..: ctrl+alt+gui+'u' cmd generates 'ū'.
const int button_Homing = 4;  //Tested Ok
const int button_ChangeScreen = 9; //Tested Ok
const int button_Spindle = 6; //Tested Ok
const int button_Coolant = 7; //Tested Ok
const int button_x_plus=A1;   //Tested Ok
const int button_x_minus=A2;   //Tested Ok
const int button_y_plus=A3;   //Tested Ok
const int button_y_minus=14;   //Tested Ok
const int button_z_plus=15;   //Tested Ok
const int button_z_minus=16;   //Tested Ok

void setup() {
  // put your setup code here, to run once:
   pinMode(pinLed, OUTPUT);

  pinMode(button_JogDecrease, INPUT_PULLUP);
  pinMode(button_JogIncrease, INPUT_PULLUP);
  pinMode(button_ChangeScreen, INPUT_PULLUP);
  pinMode(button_Unlock, INPUT_PULLUP);
  pinMode(button_Homing, INPUT_PULLUP);
  pinMode(button_Spindle, INPUT_PULLUP);
  pinMode(button_Coolant, INPUT_PULLUP);

  pinMode(button_x_plus, INPUT_PULLUP);
  pinMode(button_x_minus, INPUT_PULLUP);
  pinMode(button_y_plus, INPUT_PULLUP);
  pinMode(button_y_minus, INPUT_PULLUP);
  pinMode(button_z_plus, INPUT_PULLUP);
  pinMode(button_z_minus, INPUT_PULLUP);
  
 Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
   if (!digitalRead(button_JogDecrease)) {
    digitalWrite(pinLed, HIGH);
   
    Keyboard.press(KEY_LEFT_ALT);
    delay(10);
    Keyboard.press('-');
    Keyboard.releaseAll();
    
   delay(200);
   
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('-');
    Keyboard.releaseAll();
    
    delay(200);
    digitalWrite(pinLed, LOW);
  }

  if (!digitalRead(button_JogIncrease)) {
    digitalWrite(pinLed, HIGH);

    Keyboard.press('b');
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('=');
    Keyboard.releaseAll();
    
   delay(200);
   
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('=');
    Keyboard.releaseAll();
    
    delay(200);
    digitalWrite(pinLed, LOW);
  }

   //Unlock
  if (!digitalRead(button_Unlock)) {
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.write('u');
    Keyboard.releaseAll();

    delay(200);

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('u');
    Keyboard.releaseAll();
    
    delay(200);
    digitalWrite(pinLed, LOW);
  }

  //Homing
  if (!digitalRead(button_Homing)) {
    digitalWrite(pinLed, HIGH);
   
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('h');
    Keyboard.releaseAll();
    
   delay(200);
   
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('h');
    Keyboard.releaseAll();
    
    delay(200);
    digitalWrite(pinLed, LOW);
  }

  //ChangeScreen
  if (!digitalRead(button_ChangeScreen)) {
    digitalWrite(pinLed, HIGH);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();
    delay(200);
  
    digitalWrite(pinLed, LOW);
  }
  
  //Spindle
  if (!digitalRead(button_Spindle)) {
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('s');
    Keyboard.releaseAll();
    
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('s');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    delay(200);

    digitalWrite(pinLed, LOW);  
  }

  //Coolant
  if (!digitalRead(button_Coolant)) {
    digitalWrite(pinLed, HIGH);
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('c');
    Keyboard.releaseAll();
    delay(200);
    
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('c');
    Keyboard.releaseAll();

    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();

    delay(200);

    digitalWrite(pinLed, LOW);  
  }
  
  //x plus
  if(!digitalRead(button_x_plus)){
    digitalWrite(pinLed,HIGH);
    Keyboard.write(KEY_RIGHT_ARROW);
    delay(200);
    digitalWrite(pinLed, LOW);
  }
  //x minus
   if(!digitalRead(button_x_minus)){
    digitalWrite(pinLed,HIGH);
    Keyboard.write(KEY_LEFT_ARROW);
    delay(220);
    digitalWrite(pinLed, LOW);
  }
  //y plus
  if(!digitalRead(button_y_plus)){
    digitalWrite(pinLed,HIGH);
    Keyboard.write(KEY_UP_ARROW);
    delay(250);
    digitalWrite(pinLed, LOW);
  }
  //y minus
   if(!digitalRead(button_y_minus)){
    digitalWrite(pinLed,HIGH);
    Keyboard.write(KEY_DOWN_ARROW);
    delay(280);
    digitalWrite(pinLed, LOW);
  }
  //z plus
  if(!digitalRead(button_z_plus)){
    digitalWrite(pinLed,HIGH);
    Keyboard.write(KEY_PAGE_UP);
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  //z minus
   if(!digitalRead(button_z_minus)){
    digitalWrite(pinLed,HIGH);
    Keyboard.write(KEY_PAGE_DOWN);
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  
}

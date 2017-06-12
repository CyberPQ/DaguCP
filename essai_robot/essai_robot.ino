/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 This example code is in the public domain.
 */

int PIN_LED = 13;           // the pin that the LED is attached to
int vitesse = 0;    
int var_rampe = 5;  
int PIN_MOT1_DIR = 7;
int PIN_MOT2_DIR = 8;
int PIN_MOT1_VIT = 9;
int PIN_MOT2_VIT = 10;

char Mode = 's';

// the setup routine runs once when you press reset:
void setup() {
  
  // initialize serial:
  Serial.begin(9600);
  Serial.println(" r : fait des rampe de vitesses");
  Serial.println(" s : stop");
  
 digitalWrite(PIN_MOT1_DIR, LOW);
 digitalWrite(PIN_MOT2_DIR, LOW);
 digitalWrite(PIN_MOT1_VIT, LOW);
 digitalWrite(PIN_MOT2_VIT, LOW);
 
 pinMode(PIN_MOT1_DIR, OUTPUT);
 pinMode(PIN_MOT2_DIR, OUTPUT);
 pinMode(PIN_MOT1_VIT, OUTPUT);
 pinMode(PIN_MOT2_VIT, OUTPUT);
 loop_stop();
 }
 
void vitesseMoteur(int no_moteur, int vitesse_signe)
{
  int PIN_MOTEUR_DIR=0;
  int PIN_MOTEUR_VIT=0;
  
  if (no_moteur == 1)
  {
    //Serial.print("moteur 1 : ");
    PIN_MOTEUR_DIR = PIN_MOT1_DIR ;
    PIN_MOTEUR_VIT = PIN_MOT1_VIT ;
  }
  else if (no_moteur == 2)
  {
    //Serial.print("moteur 2 : ");
    PIN_MOTEUR_DIR = PIN_MOT2_DIR ;
    PIN_MOTEUR_VIT = PIN_MOT2_VIT ;
  }
  else
  {
    /* oups */
  }

  //Serial.println(vitesse);
  
  if (vitesse_signe > 0)
  {
    digitalWrite(PIN_MOTEUR_DIR, HIGH);
    analogWrite(PIN_MOTEUR_VIT, vitesse_signe);
  }
  else 
  {
    digitalWrite(PIN_MOTEUR_DIR, LOW);
    analogWrite(PIN_MOTEUR_VIT, -vitesse_signe);
  }
  
  
  
}

// the loop routine runs over and over again forever:
void loop_rampe() {
 vitesseMoteur (1, vitesse);
 vitesseMoteur (2, vitesse);  
 
 vitesse = vitesse + var_rampe;
 
 if (vitesse == -255 || vitesse == 255) {
    var_rampe = -var_rampe ;
  }
 
  delay(30);
}

void loop_stop()
{
  vitesseMoteur (1, 0);
  vitesseMoteur (2, 0);  
  delay(300);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
 
  
  if (Serial.available() > 0)
  {
    Mode = Serial.read();
    Serial.print("Activation du mode ");
    Serial.println(Mode);
  }

  switch (Mode) 
  {
      case 's':
        // stop mode
        loop_stop();
        break;
      case 'r':
        // rampe mode
        loop_rampe();
        break;
      
  }
}


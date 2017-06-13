int PIN_LED = 13;          
int vitesse = 0;
int var_rampe = 5;
int distance_gauche = 0;
int distance_droite = 0;
int distance_centre = 0;
int PIN_MOT1_DIR = 7;
int PIN_MOT2_DIR = 8;
int PIN_MOT1_VIT = 9;
int PIN_MOT2_VIT = 10;
int PIN_SERVO = 12;
int PIN_TRIG = 11;
int PIN_ECHO = 6;
int PIN_JOYSTICK_X = A1;
int PIN_JOYSTICK_Y = A2;
int PIN_JOYSTICK_BOUTON = A3;

#define POSITION_GAUCHE   (1000)
#define POSITION_MILIEU   (1500)
#define POSITION_DROITE   (2000)

char Mode = 's';
char Commande = ' ';

void setup() {

  // initialize serial:
  Serial.begin(115200);
  
  digitalWrite(PIN_MOT1_DIR, LOW);
  digitalWrite(PIN_MOT2_DIR, LOW);
  digitalWrite(PIN_MOT1_VIT, LOW);
  digitalWrite(PIN_MOT2_VIT, LOW);

  pinMode(PIN_MOT1_DIR, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_MOT2_DIR, OUTPUT);
  pinMode(PIN_MOT1_VIT, OUTPUT);
  pinMode(PIN_MOT2_VIT, OUTPUT);
  pinMode(PIN_SERVO, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_JOYSTICK_X, INPUT);
  pinMode(PIN_JOYSTICK_Y, INPUT);
  pinMode(PIN_JOYSTICK_BOUTON, INPUT_PULLUP);
  loop_stop();
  
}

void vitesseMoteurS(int VIT_moteur1, int VIT_moteur2)
{
  vitesseMoteur(1, VIT_moteur1);
  vitesseMoteur(2, VIT_moteur2);
}


void vitesseMoteur(int no_moteur, int vitesse_signe)
{
  int PIN_MOTEUR_DIR = 0;
  int PIN_MOTEUR_VIT = 0;

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
void usage(void)
{
  Serial.println(" r : fait des rampes de vitesse");
  Serial.println(" s : stop");
  Serial.println(" m : manuel (pave numerique)");
  Serial.println("   1,2,3,4,6,7,8,9 : controle");
  Serial.println("   5 : arret");
  Serial.println("   /,*,- : controle du servo moteur");
}

void loop_rampe() {
  vitesseMoteurS (vitesse, vitesse);

  vitesse = vitesse + var_rampe;

  if (vitesse == -255 || vitesse == 255) {
    var_rampe = -var_rampe ;
  }

  delay(30);
}

void loop_stop()
{
  vitesseMoteurS (0, 0);
  digitalWrite(PIN_LED, !digitalRead(PIN_LED));  //invertion état de la led
  delay(500);
  if (analogRead(PIN_JOYSTICK_X)>1000)
  {
   digitalWrite(PIN_LED, LOW);
   delay(1000);
   if (analogRead(PIN_JOYSTICK_X)>1000)
   {
      digitalWrite(PIN_LED, HIGH);
      delay(1000);
      Mode = 'a';
   }  
  }
}
 
int mesureCm(void)
{
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
    
    int microseconds = pulseIn(PIN_ECHO, HIGH);
    int mesureCm = microseconds / 29 / 2;
    return mesureCm;
}
  
void loop_manuel(char Commande) {
  
  
  digitalWrite(PIN_LED, HIGH);
  delay(150);
  digitalWrite(PIN_LED, LOW);
  delay(150);
  switch (Commande)
  {
    case '8':
      vitesseMoteurS(vitesse, vitesse);
      delay(2000);
      vitesseMoteurS (0, 0);
      break;
    case '2':
      vitesseMoteurS(1 - vitesse, -vitesse);
      delay(2000);
      vitesseMoteurS (0, 0);
      break;
    case '4':
      vitesseMoteurS(vitesse, -vitesse);
      delay(700);
      vitesseMoteurS (0, 0);
      break;
    case '6':
      vitesseMoteurS(-vitesse, vitesse);
      delay(700);
      vitesseMoteurS (0, 0);
      break;
    case '5':
      vitesseMoteurS(0, 0);
      break;
    case '9':
      vitesseMoteurS(0.25 * vitesse, vitesse);
      delay(2000);
      vitesseMoteurS (0, 0);
      break;
    case '7':
      vitesseMoteurS(vitesse, 0.25 * vitesse);
      delay(2000);
      vitesseMoteurS (0, 0);
      break;
    case '1':
      vitesseMoteurS(-0.25 * vitesse, -vitesse);
      delay(2000);
      vitesseMoteurS (0, 0);
      break;
    case '3':
      vitesseMoteurS(-vitesse, -0.25 * vitesse);
      delay(2000);
      vitesseMoteurS (0, 0);
      break;
    case '/':
      set_servo(POSITION_GAUCHE);
      distance_gauche = mesureCm();
      Serial.print(distance_gauche);
      Serial.println(" cm");
      break;
    case '*':
      set_servo(POSITION_MILIEU);
      distance_centre = mesureCm();
      Serial.print(distance_centre);
      Serial.println(" cm");
      break;
      
    case '-':
      set_servo(POSITION_DROITE);
      distance_droite = mesureCm();
      Serial.print(distance_droite);
      Serial.println(" cm");
      break;
  }
}

void analyse_distance(void)
{
  set_servo(POSITION_GAUCHE);
  distance_gauche = mesureCm();
  Serial.print(distance_gauche);
  Serial.print(" ");
  set_servo(POSITION_MILIEU);
  distance_centre = mesureCm();
  Serial.print(distance_centre);
  Serial.print(" ");
  
  set_servo(POSITION_DROITE);
  distance_droite = mesureCm();
  Serial.print(distance_droite);
  Serial.println(" ");
}
void loop_auto (void) 
{
  analyse_distance();
  if (distance_centre < 30)
  {
    if (distance_droite < distance_gauche)
    {
      vitesseMoteurS(vitesse, -vitesse);
    }
    else if (distance_droite > distance_gauche)
    {
      vitesseMoteurS(-vitesse, vitesse);
    }
  }
  else 
  {
    if (distance_droite < 40)
    {
      vitesseMoteurS(0.25 * vitesse, vitesse);
    }
    else if (distance_gauche < 40) 
    {
      vitesseMoteurS(vitesse, 0.25 * vitesse);
    }
    else
    {
      vitesseMoteurS(vitesse, vitesse);
    }
   
  }
}


void set_servo(int angle)
{
  int i = 0;

  for (i = 0; i < 70; i++)
  {
    digitalWrite(PIN_SERVO, HIGH);
    delayMicroseconds(angle);
    digitalWrite(PIN_SERVO, LOW);
    delayMicroseconds(20000);
  }
}

void loop_aleatoire()
{
  vitesseMoteurS(random(-255, 255), random(-255, 255));
  delay(1000);
}

void joystick_arret(void)
{
  if ((digitalRead(PIN_JOYSTICK_BOUTON)==0)
        || (analogRead(PIN_JOYSTICK_X)>518) 
        || (analogRead(PIN_JOYSTICK_X)<504) 
        || (analogRead(PIN_JOYSTICK_Y)>518)
        || (analogRead(PIN_JOYSTICK_Y)<504))
  {
    Serial.println("ARRET D'URGENCE !!!");
    Mode = 's'; 
  }
}

void loop() {
  char Touche = 's';
  joystick_arret();
  if (Serial.available() > 0)
  {
    Touche = Serial.read();
    switch (Touche)
    {
      case 's':
        Mode = 's';
        break;
      case 'r':
        Mode = 'r';
        break;
      case 'm':
        Mode = 'm';
        break;
      case 'x':
        Mode = 'x';
        break;
      case 'a':
        Mode = 'a';
        break; 
      case '?':
      case 'h':
        usage();     
        break;
    }   
    Serial.print("Activation du mode ");
    Serial.print(Mode);
    Serial.print(" (vitesse courante : ");
    Serial.print(vitesse);
    Serial.println(")");
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
    case 'm':
      // mode manuel
      vitesse = 100;
      loop_manuel(Touche);
      Touche = '\0';
      break;
    case 'x':
      //mode aleatoire
      loop_aleatoire();
      Touche = '\0';
      break;
    case 'a':
      //mode auto
      vitesse = 100;
      loop_auto();
      break;
  }
}


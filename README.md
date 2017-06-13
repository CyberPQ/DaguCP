# DaguCP

Robot Dagu de Clément, réalisé pendant le stage en entreprise


## Connexions électriques

La carte Arduino utilisée est assimilable à une carte Nano 328.

La led bleue est disppnible sur la pin 13.

Chenille gauche :

  - Encoder A   --> Arduino Pin 2
  - Encoder B   --> Arduino Pin 5
  - Motor       --> Arduino motor 1 (direction pin 7, PWM pin 9)

Chenille droite :

  - Encoder A   --> Arduino Pin 3
  - Encoder B   --> Arduino Pin 4
  - Motor       --> Arduino motor 2 (direction pin 8, PWM pin 10)
  
Servo branché sur la pin 12

Emetteur d'ultra-sons :
  - Trig        --> Arduino Pin 11
  - Echo        --> Arduino Pin 6  

Joystick :
  - Axe x       --> Arduino Pin A1 (0 to 1024)
  - Axe y       --> Arduino Pin A2 (0 to 1024)
  - Button      --> Arduino Pin A3 (HIGH/LOW)
  
  ## Utilisation
        Au démarage, le robot est en Mode STOP. On le voit grâce à la led qui clignote.
        Pour passer en mode AUTO, tirer le joystick vers l'arrière du rover, la led s'éteind, attendre qu'elle se rallume puis relacher le joystick.
        
        A tout moment, un mouvement du joystick fait basculer le robot en mode STOP.
        
  
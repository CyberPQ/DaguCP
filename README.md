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


## Analyse des distances
Le capteur ultrason est très bruité et beaucoup de ses valeurs sont erronées. j'ai donc effectué des mesures dans differentes positions afin de déterminer le bruit. au vu des courbes on en déduit que le capteur détecte clairement un obstacle entre 20 et 200 cm. En dehors de ces valeurs, l'obstacle peut être détécté mais le bruit empêche le robot de prendre des décisions intelligentes. De plus, si l'echo de l'ultrason ne revient pas au bout d'une seconde (*timeout*) le capteur l'inteprète comme une distance de 0cm.

## Fonctionnement des moteurs

## Servo moteur
## Algo

![boucle loop](doc\boucle_loop.png)
  
## Utilisation

Au démarage, le robot est en Mode STOP. On le voit grâce à la led qui clignote.

Pour passer en mode AUTO, tirer le joystick vers l'arrière du rover, la led s'éteind, attendre qu'elle se rallume puis relacher le joystick.
        
A tout moment, un mouvement du joystick fait basculer le robot en mode STOP.

![Transition entre les modes](doc\transitions_modes.png)        


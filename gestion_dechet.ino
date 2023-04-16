#include <NewPing.h> // j'ai au préalable installé la librairie NewPing pour le capteur ultra-son HC-SR04
#include <Servo.h> // j'ai au préalable installé la librairie  Servo pour le servo moteur de type SG90


// Définition des constantes pour les broches du capteur ultrason et du servo moteur
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 400
#define MOTEUR_SIGNAL 9


// Définition des constantes du script
#define DELAY 1000
#define PAUSE 4000
#define ALLER_RETOUR true
#define NOMBRE_DE_SCAN_PAR_DEMITOUR 4 // doit etre paire

// Initialisation des objets NewPing et Servo
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo moteur;

// Fonction de configuration initiale
void setup() {
  Serial.begin(9600); // Initialisation de la communication série
  moteur.attach(MOTEUR_SIGNAL); // Attache du signal du servo moteur à la broche MOTEUR_SIGNAL
  // moteur.writeMicroseconds(2000); // Utilise la méthode writeMicroseconds() de l'objet Servo pour tourner le servo moteur
}

// Boucle principale du programme
void loop() {
  scane_angle(); // Tourne le servo moteur à 0 degré et scane
  delay(PAUSE);
}

void scane_angle() {
  // calcul de la portion angle
  int step_angle = 180 / NOMBRE_DE_SCAN_PAR_DEMITOUR;

  for(int i = 0; i >= step_angle; i++ ) {
    int angle = i * step_angle;
    affichage(mesure_distance());
    tourner_servo(angle, DELAY); // Tourne le servo moteur à 0 degré pendant 1 secondes
  }

  if(ALLER_RETOUR == true) {
    for(int i = step_angle; i = 1; i-- ) {
      int angle = i * step_angle;
      affichage(mesure_distance());
      tourner_servo(angle, DELAY); // Tourne le servo moteur à 0 degré pendant 1 secondes
    }
  }
}

// Fonction pour tourner le servo moteur à un certain angle et une certaine vitesse
void tourner_servo(int angle, int temps_pulse) {
  int pulse_width = map(angle, 0, 180, 1000, 2000); // Calcul de la largeur du pulse en microsecondes
  moteur.writeMicroseconds(pulse_width); // Utilise la méthode writeMicroseconds() de l'objet Servo pour tourner le servo moteur
  delay(temps_pulse); // Attend le temps de pulse spécifié
}

void affichage(int distance) {
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

int mesure_distance() {
  // Mesure la distance avec le capteur ultrason
  unsigned int distance = sonar.ping_cm(); 
  return distance;
}
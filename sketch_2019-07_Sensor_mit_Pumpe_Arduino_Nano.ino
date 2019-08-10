const int LED = 6; // LED an Pin D6
const int Pumpe = 4; // Pumpe an Pin D4
const int USensor = 7; // Spannungsversorgung an Pin D7 für Sensor
const int Sensor = A1; // Sensor auslesen an Pin A1
const int tP = 15; // Pumpzeit in s

void setup() { 
     // Digitaler Ausgang steuert die LED
     pinMode(LED, OUTPUT);
     pinMode(Pumpe, OUTPUT);
     pinMode(USensor, OUTPUT);
     // Der Sensor soll nicht ständig unter Spannung stehen, um
     // möglichst lange zu halten, ggf. Elektrolyse zu minimieren.
     pinMode(Sensor, INPUT);
     Serial.begin(115200); // Seriellen Port mit 115200 Baud initialisieren
}

void loop() {
     // digitalWrite(LED, HIGH); 
     analogWrite(LED, 10); // Licht an
     // Licht anschalten mit PWM ca. 20 %
     int Messwert=SensorLesen();
     Serial.print("Sensorwert = "); // Ausgabe an seriellen Monitor
     Serial.println(Messwert); 
     delay(100); // Wartezeit von 100 Millisekunden
     // digitalWrite(LED, LOW); 
     analogWrite(LED, 0); // Licht aus
     if (Messwert <200 ) // Abfrage: Wenn Sensorwert kleiner als "200", dann ...
     { 
     Pumpen();
     }
     else //..ansonsten...
     {
     Serial.println("feucht genug"); // Ausgabe an seriellen Monitor
     }
     delay(1*60000); // Wartezeit von 10 Minuten
}


float SensorLesen(){
  digitalWrite(USensor, HIGH); // Spannungsversorgung des Sensors anschalten
  delay(100); // Wartezeit von 100 Millisekunden
  int S1=analogRead(Sensor); // Sensorwert auslesen
  digitalWrite(USensor, LOW); // Spannungsversorgung des Sensors ausschalten
  return S1;
}

void Pumpen(){
  Serial.println("zu trocken, Pumpe startet"); // Ausgabe an seriellen Monitor
  digitalWrite(Pumpe, HIGH); // Pumpe starten
  delay(tP*1000); // Pumpzeit abwarten
  digitalWrite(Pumpe, LOW); // Pumpe stoppen
  Serial.print("Pumpe lief "); // Ausgabe an seriellen Monitor
  Serial.print(tP); 
  Serial.println(" s lang");
}

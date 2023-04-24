#include <WiFi.h>
#include <PubSubClient.h>
#define  BUILTIN_LED 2

#include <DHTesp.h>
#include <ESP32_Servo.h>

//Pines para Led y sensor de gas
int LED = 32;  
int Sensor_input = 4;  
//Pines para sensor de proximidad
const int trigPin = 5;  
const int echoPin = 18;  
const int ledPin = 23;  
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
//Pin del sensor de lluvia
#define rainDigital 34  
//Pin del sensor de choque
#define SENSOR_PIN 21  

long duration;
float distanceCm;
float distanceInch;
int lastState = HIGH;
int currentState;

Servo myservo; // create servo object to control a servo

DHTesp dht;

// Update these with values suitable for your network.

const char* ssid = "RedEstudiantes_2.4";
const char* password = "1q2w3e4r5t";
const char* mqtt_server = "192.168.1.129";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg2[MSG_BUFFER_SIZE];
char msg3[MSG_BUFFER_SIZE];


const int lightSensorPin = 21;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("fer", "hello world");
      // ... and resubscribe
      client.subscribe("fer");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(lightSensorPin, INPUT);

  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(rainDigital, INPUT);
  pinMode(SENSOR_PIN, INPUT);
  myservo.attach(2, 500, 2400); // attaches the servo on GPIO2 to the servo object with pulse width range of 500 to 2400 microseconds
  dht.setup(15, DHTesp::DHT11); // Connect DHT sensor to GPIO 15 (D8)
  pinMode(12, OUTPUT);
}

void loop() {
  //Sensor de gas
  int sensor_Aout = analogRead(Sensor_input);
  Serial.print("Gas sensor: ");
  Serial.print(sensor_Aout);
  Serial.print("\t");
  Serial.print("\t");
  if (sensor_Aout > 1800) {
    Serial.println("Gas");
    digitalWrite(LED, HIGH);
  } else {
    Serial.println("No gas");
    digitalWrite(LED, LOW);
  }
  delay(500);

  //Distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  distanceInch = distanceCm * CM_TO_INCH;
  
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  if (distanceCm > 30) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(12, HIGH);
    Serial.println("Cuidado!");
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(12, LOW);
  }
  delay(1000);

  int rainDigitalVal = digitalRead(rainDigital);
  if (rainDigitalVal == LOW) {
    Serial.println("Está lloviendo.");
  } else {
    Serial.println("No está lloviendo.");
  }
  delay(200);

  currentState = digitalRead(SENSOR_PIN);
  if (lastState == HIGH && currentState == LOW) {
    Serial.println("The obstacle is detected");
  } else if (lastState == LOW && currentState == HIGH) {
    Serial.println("The obstacle is cleared");
  }
  delay(100);
  lastState = currentState;

  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  Serial.print("Humidity:");
  Serial.print(humidity, 1);
  Serial.print("\n");
  if(humidity>40) {
    int pos;
    for(pos = 0; pos <= 360; pos += 1) {
      //goes from 0 degress to 360 degress in steps of 1 degree
      myservo.write(pos);
      delay(15); // wait for 15ms after each 1 degree rotation
    }
    for(pos = 360; pos >= 0; pos -= 1) {
      //goes
{
//goes from 360 degress to 0 degress in steps of 1 degree
myservo.write(pos);
delay(15); // wait for 15ms after each 1 degree rotation
}
} // end of if condition
} // end of loop.

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    
    int humiditysens = humidity;
    snprintf(msg2, MSG_BUFFER_SIZE, "{\"sensor_id\": 2, \"value\": %d}", humiditysens); // Convert the value to a string
    
    int distance = distanceCm;
    snprintf(msg3, MSG_BUFFER_SIZE, "{\"sensor_id\": 3, \"value\": %d}", distance); // Convert the value to a string
    
    
    // Publicar mensajes en el topic MQTT_TOPIC
    client.publish("fer",msg2);
    client.publish("fer",msg3);    

    Serial.print("Mensaje enviado: ");
    Serial.println(msg2);
    Serial.println(msg3);
  }


}
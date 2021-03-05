/* Standard includes! */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

/* Defines */
#define MSG_BUFFER_SIZE (50)
#define SLAVE_ADDR 0x09

/* Declares */
WiFiClient espClient;
PubSubClient client(espClient);

/* Network settings */
const char* ssid = "telenet-ED83B";
const char* password = "passwordsenne";
const char* mqtt_server = "broker.hivemq.com";

/* Variables */
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;
int code = 0;

void setup_wifi() {

  delay(10);
  /* We start by connecting to a WiFi network */
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

  /* Switch on the LED if (payload) */
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
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
      client.publish("Senne123", "hello world");
      // ... and resubscribe
      client.subscribe("Senne123");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void receiveEvent() {

    /* Read while data received */
    while (0 < Wire.available()) {
        byte x = Wire.read();
    }
    
    code = x;

    /* DEBUG TESTING IF I RECEIVE SOMETHING */
    Serial.println("Receive event: " + x);
}

void requestEvent() {

    /* Setup correct byte size */
    byte response[ANSWERSIZE];

    /* DEBUG */
    Serial.print("Request event: ");

    /* Format answer as array */
    for (byte i=0;i<ANSWERSIZE;i++) {
        response[i] = (byte)answer.charAt(i);
        Serial.print(response[i]);
    }
    Serial.println();
}

void setup()
{
    /* General Setup */
    pinMode(BUILTIN_LED, OUTPUT);
    Serial.begin(115200);

    /* Calling wifi setup function */
    setup_wifi();

    /* Setting up the mqtt-client */
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    /* Init slave */
    Wire.begin(SLAVE_ADDR);

    /* data request function from master */
    Wire.onRequest(requestEvent); 

    /* Data receive function from master */
    Wire.onReceive(receiveEvent);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    value++;

    //snprintf (msg, MSG_BUFFER_SIZE, "HIGH #%ld", value); // currently slashed out

    /* TESTING */
    msg = "Code = " + code + " id: " + value;

    /* DEBUG */
    Serial.println(msg);

    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Senne", msg);
    delay(100);
}



// --------- EXTRA INFO ---------

/* Err: PIXY scans 10 times while only 1 passed by! */


// int oldcode = 0;
// int code = 0;

// if(oldcode != code){
//     /*CODE TO SEND TO THINGSWORX*/
//     {

//     }

//     /* AT THE END -> OLDCODE */
//     oldcode = code;
// }
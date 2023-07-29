#define BLYNK_TEMPLATE_ID "TMPL3jrbheuQH"
#define BLYNK_TEMPLATE_NAME "LED with Preferences"
#define BLYNK_AUTH_TOKEN "E2gBxPBMJ2Hy9-Qi9wHxcR8tZgIAKabC"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Preferences.h> 

char auth[] = BLYNK_AUTH_TOKEN;

// Pin numbers for LEDs
const int led1 = 2;
const int led2 = 23;
const int led3 = 5;

Preferences pref;

void setup() {
  Serial.begin(115200);

  // Read network credentials from Preferences
  pref.begin("network");
  String savedSSID = pref.getString("ssid", "");
  String savedPassword = pref.getString("password", "");
  pref.end();

  // Connect to Wi-Fi using saved credentials
  if (savedSSID != "" && savedPassword != "") {
   Blynk.begin(auth, savedSSID.c_str(),savedPassword.c_str() );
  } else {
    Serial.println("No saved credentials found !");
  }

  // Set the LED pins as OUTPUT
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Initialize the Preferences library for LED states
   pref.begin("led_states");                           // "led_states" is the namespace for our LED states
  digitalWrite(led1, pref.getBool("led1", false));
  digitalWrite(led2, pref.getBool("led2", false));
  digitalWrite(led3, pref.getBool("led3", false));
  pref.end();
}

void loop() {
  Blynk.run();
}

// Function to control LEDs based on virtual pin values
BLYNK_WRITE(V0) {
  int Value = param.asInt();
  digitalWrite(led1, Value);
  pref.begin("led_states");
  pref.putBool("led1", Value); // Save the LED state to Preferences
  pref.end();
}

BLYNK_WRITE(V1) {
  int Value = param.asInt();
  digitalWrite(led2, Value);
  pref.begin("led_states");
  pref.putBool("led2", Value); // Save the LED state to Preferences
  pref.end();
}

BLYNK_WRITE(V2) {
  int Value = param.asInt();
  digitalWrite(led3, Value);
  pref.begin("led_states");
  pref.putBool("led3", Value); // Save the LED state to Preferences
  pref.end();
}

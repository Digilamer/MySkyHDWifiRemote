/*
 * IRremoteESP8266: IRServer - demonstrates sending IR codes controlled from a webserver
 * Version 0.2 June, 2017
 * Copyright 2015 Mark Szabo
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

 /// NOTA: Per programmare l'unità assicurarsi di scollegare il pin Vin dal +5V
 ///       poi ricollegarlo al termine. Non collegare mai l'USB e l'alimentatore esterno insieme
 
#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>
#include "Code_SKY.h"

#include "index.h" //Our HTML webpage contents
#include "manifest.h" //Json manifest contents useful if you install the web page as a web app (stays portrait w/o rotation and fullscreen)

const char* kSsid = "your_wifi_ssid";
const char* kPassword = "your_wifi_password";
MDNSResponder mdns;

ESP8266WebServer server(80);

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

void handleRoot() {
  server.send_P(200, "text/html", MAIN_page, strlen(MAIN_page));
}

void handleManifest() {
  Serial.print("\nManifest request, Sending json file");
  Serial.print("\n");
  server.send_P(200, "text/html", manifest, strlen(manifest));
}


void sendKey(int k) {
  Serial.print(" Received code ");
  Serial.print(k);

  int codeLen = sizeof(Signal1[k])/sizeof(int);

  Serial.print("\ncode len part 1: ");
  Serial.print(codeLen);
  Serial.print("\n");

  irsend.sendRaw(Signal1[k], VALS, KHZ);
  if ( KEYPAUSE > 0 ) {
    delayMicroseconds(KEYPAUSE);
    codeLen = sizeof(Signal2[k])/sizeof(int);
    irsend.sendRaw(Signal2[k], VALS, KHZ);
    Serial.print(" \ncode len part 2: ");
    Serial.print(codeLen);
    Serial.print("\n");
    if (Signal3[k][0] != 0) {
      delayMicroseconds(KEYPAUSE);
      codeLen = sizeof(Signal3[k])/sizeof(int);
      irsend.sendRaw(Signal3[k], VALS, KHZ);
      Serial.print(" \ncode len part 3: ");
      Serial.print(codeLen);
      Serial.print("\n");
    }
  }
  delay(20);
}


void handleIr() {
  digitalWrite(LED_BUILTIN, HIGH); // Led off
  delayMicroseconds(100);
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      String kCodes;
      kCodes = server.arg(i).c_str();

      Serial.print(" Received code ");
      Serial.print(kCodes);
      Serial.print("\n");

      int code = -1;
      
      for (uint8_t x = 0; x < KEYS; x++) 
      {
        if (kCodes == keyLbl[x]) {
          code = x;
          break;
        }
      }
      Serial.print("Converted code ");
      Serial.print(code);
      Serial.print("\n");

      if (code >= 0) 
      {
        sendKey(code);  
        Serial.println("code sent to IR");
      }
      else 
      {
        String extraLbl[] = {"EUSP",   "SKY1",   "SMGP",   "SARE"};

        code = -1;
        
        for (uint8_t x = 0; x < 4; x++) 
        {
          if (kCodes == extraLbl[x]) {
            code = x;
            break;
          }
        }
        switch (code) {
            case 0:
              sendKey(2);
              delay(300);
              sendKey(1);  
              delay(300);
              sendKey(0);  
              break;
            case 1:
              sendKey(1);  
              delay(300);
              sendKey(0);  
              delay(300);
              sendKey(8);
              break;
            case 2:
              sendKey(2);  
              delay(300);
              sendKey(0);  
              delay(300);
              sendKey(8);  
              break;
            case 3:
              sendKey(2);  
              delay(300);
              sendKey(0);  
              delay(300);
              sendKey(4);  
              break;
          }
      }      
    }
  }
  handleRoot();
  digitalWrite(LED_BUILTIN, LOW);  // Led on
}




void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  // Builtin led
  pinMode(LED_BUILTIN, OUTPUT);
  // Per output in Monitor seriale
  Serial.begin(115200);

  // Avvia wifi
  WiFi.mode(WIFI_STA); // set to station only mode (default was WIFI_AP_STA (modes are WIFI_OFF = 0, WIFI_STA = 1, WIFI_AP = 2, WIFI_AP_STA = 3 )
  WiFi.begin(kSsid, kPassword);
  
  WiFi.setSleepMode(WIFI_NONE_SLEEP); // per non perdere la connessione
  
  Serial.println("");

  irsend.begin();

  Serial.print("Connecting to ");
  Serial.println(kSsid);
  
  // Wait for connection with blinking led
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);  // Led on
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);  // Led off
    delay(250);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(kSsid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP().toString());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  // Se non richiede una pagina specifica, mostra la pagina principale
  server.on("/", handleRoot);   

  // se richiede ir, gestisco richiesta comando
  server.on("/ir", handleIr); 

  server.on("/manifest.json", handleManifest);   
  
  // se richiede inline, mostro stato segnale wifi
  server.on("/inline", [](){
    String rssi = String(WiFi.RSSI(), DEC);
    String out = String("Wifi Signal: " + rssi);
    server.send(200, "text/plain", out);
  });
  
  // Se richiesta una pagina diversa, do errore 404
  server.onNotFound(handleNotFound); 

  // Start http server
  server.begin();
  Serial.println("HTTP server started");
  
  Serial.print("Wi-fi signal: ");
  Serial.println(WiFi.RSSI());
 
  digitalWrite(LED_BUILTIN, LOW);  // Led on

}

void loop(void) {
  
  server.handleClient();

  // Wait for connection with blinking led
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);  // Led on
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);  // Led off
    delay(100);
    Serial.print(".");
  }


}

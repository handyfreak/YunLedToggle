#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

#define LED_PIN 13

YunServer server;

void setup() {
  
  // init LED PIN
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // start the Bridge library
  Bridge.begin();
  
  // init serial connection and wait until it's available
  Serial.begin(9600);
  while (!Serial);
  
  // listen for incoming connections from localhost only
  server.listenOnLocalhost();
  server.begin();
  
  Serial.println("Accepting commands...");
}

void loop() {
  
  // try to accept a new connection
  YunClient client = server.accept();
  
  // a client was accepted?
  if(client) {
  
    // read the command and trim spaces
    String command = client.readString();
    command.trim();
    
    // print the received command on the console
    Serial.print("New command -> ");
    Serial.println(command);
    
    // perform the requested action
    if(command == "toggle") {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      client.println("LED status changed");
    } else client.println("Unknown command");
    
    // close the connection
    client.stop();
  }
}

//EthernetElectricity.ino.ino
#include <Ethernet.h>
#include <SPI.h>

int led = 13;

byte mac[] = { 0x36, 0x31, 0x35, 0x41, 0x4E, 0x4C };
byte server[] = {192, 168, 1, 121};
byte ip[] = {192, 168, 1, 125};

EthernetClient client;
void setup() {
  Ethernet.begin(mac, ip);

  Serial.begin(9600);

  Serial.println(Ethernet.localIP());

  delay(1000);

  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("LED");
  } else {
    Serial.println("connection failed");
  }
  pinMode(5, OUTPUT);
}

void loop() {
  if (client.available()) {
    char c = client.read();
    digitalWrite(5, c);
    Serial.print(c);
  }
}

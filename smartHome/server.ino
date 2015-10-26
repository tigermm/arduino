#include <SPI.h>
#include <Ethernet.h>

// network configuration.  gateway and subnet are optional.

 // the media access control (ethernet hardware) address for the shield:
byte mac[] = {0x36, 0x31, 0x35, 0x41, 0x4E, 0x4C};  
//the IP address for the shield:
byte ip[] = { 192, 168, 1, 121 };    
// the router's gateway address
byte gateway[] = { 192, 168, 1, 1 };
// the subnet:
byte subnet[] = { 255, 255, 255, 0 };

// telnet defaults to port 23
EthernetServer server = EthernetServer(80);

void setup()
{
  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);

  Serial.begin(9600);
    Serial.println(Ethernet.localIP());
  // start listening for clients
  server.begin();
  Serial.println(Ethernet.localIP());
}

char id[10];
EthernetClient client;

void loop()
{
  
  // if an incoming client connects, there will be bytes available to read:
   EthernetClient c = server.available();
   int i = 0;
   if (c) {
     client = c;
     // read bytes from the incoming client and write them back
     // to any clients connected to the server:
     // server.write(client.read());
   int i = 0;
   while(client.available()){
     id[i] = client.read();
     i++;  
     //strcat(id, client.read());
   }
   
  }
  if ((client) && (Serial.available()) )
  {
    client.println(Serial.read() );
  }
  
}

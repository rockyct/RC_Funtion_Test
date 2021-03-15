#include <SBUS.h>
#include <PololuMaestro.h>


#define maestroSerial Serial1
//#define maestroSerial SERIAL_PORT_HARDWARE_OPEN



// a SBUS object, which is on hardware
// serial port 1
SBUS x8r(Serial1);

// channel, fail safe, and lost frames data
uint16_t channels[16];
bool failSafe;
bool lostFrame;


MicroMaestro maestro(maestroSerial);
//MicroMaestro maestro(Serial1);
void setup() {
  // begin the SBUS communication
  x8r.begin();
  maestroSerial.begin(100000);
  
  Serial.begin(115200);
  Serial.println("starting up");
}

void loop() {
//  delay(1000);
//  Serial.println("starting the loop");
  
  // look for a good SBUS packet from the receiver
  if(x8r.read(&channels[0], &failSafe, &lostFrame)){



    // write the SBUS packet to an SBUS compatible servo
    Serial.print("Ch1  ");
    Serial.println(channels[0]);
    Serial.println(4*channels[0]);
    maestro.setTarget(0, 4*channels[0]);
    Serial.print("Ch2  ");
    Serial.println(channels[1]);
    Serial.println(4*channels[1]);
    maestro.setTarget(1, 4*channels[1]);
    Serial.print("Ch3  ");
    Serial.println(channels[2]);
    Serial.println(4*channels[2]);
    maestro.setTarget(2, 4*channels[2]);
    Serial.print("Ch4  ");
    Serial.println(channels[3]);
    Serial.println(4*channels[3]);
    maestro.setTarget(3, 4*channels[3]);
//    delay(1000);              
  }
}

#include <sbus.h>
#include <PololuMaestro.h>


#define maestroSerial Serial2
//#define maestroSerial SERIAL_PORT_HARDWARE_OPEN

// Updated library
bfs::SbusRx sbus_rx(&Serial2);
bfs::SbusData data;

// old method
// a SBUS object, which is on hardware
// serial port 1
//SBUS x8r(Serial1);

// old
// channel, fail safe, and lost frames data
// uint16_t channels[16];
// bool failSafe;
// bool lostFrame;

int sendChannel[15];


MicroMaestro maestro(maestroSerial);
//MicroMaestro maestro(Serial1);


void setup() {
  // old begin the SBUS communication
  // x8r.begin();
  
  Serial.begin(115200);
  Serial.println("starting up");

  while (!Serial) {}
  /* Begin the SBUS communication */
  sbus_rx.Begin();

  maestroSerial.begin(100000);

}

void loop() {
//  delay(1000);
//  Serial.println("starting the loop");

  if (sbus_rx.Read()) {
    /* Grab the received data */
    data = sbus_rx.data();
    /* Display the received data */
    for (int8_t i = 0; i < data.NUM_CH; i++) {
      Serial.print(data.ch[i]);
      Serial.print("\t");
      sendChannel[i] = map(data.ch[i], 172, 1811, 4000, 8000);
      Serial.print(sendChannel[i]);
      Serial.print("\t");
    }
    maestro.setTarget(0, sendChannel[0]);
    maestro.setTarget(1, sendChannel[1]);
    maestro.setTarget(2, sendChannel[2]);
    maestro.setTarget(3, sendChannel[3]);
    /* Display lost frames and failsafe data */
    Serial.print(data.lost_frame);
    Serial.print("\t");
    Serial.println(data.failsafe);
    
    /* Set the SBUS TX data to the received data */
    // sbus_tx.data(data);
    // /* Write the data to the servos */
    // sbus_tx.Write();
  }
  // old - look for a good SBUS packet from the receiver
  // if(x8r.read(&channels[0], &failSafe, &lostFrame)){



    // write the SBUS packet to an SBUS compatible servo
    // This works outputs: "Ch1 XXX"

    // Values coming from receiver are 172-1811. Meastro takes 4000-8000
    // 688-7244
    // Serial.print("Ch1  ");
    // Serial.println(data.ch[0]);
    // Serial.println(4*data.ch[0]);
    // maestro.setTarget(0, 5000);
    // maestro.setTarget(1, 5000);
    // maestro.setTarget(2, 5000);
    // maestro.setTarget(3, 5000);
    // maestro.setTarget(0, 4*data.ch[0]);
    // maestro.setTarget(1, 4*data.ch[1]);
    // maestro.setTarget(2, 4*data.ch[2]);
    // maestro.setTarget(3, 4*data.ch[3]);
    // delay(2000);
    // Serial.print("Ch2  ");
    // Serial.println(channels[1]);
    // Serial.println(4*channels[1]);
    // maestro.setTarget(1, 4*channels[1]);
    // Serial.print("Ch3  ");
    // Serial.println(channels[2]);
    // Serial.println(4*channels[2]);
    // maestro.setTarget(2, 4*channels[2]);
    // Serial.print("Ch4  ");
    // Serial.println(channels[3]);
    // Serial.println(4*channels[3]);
    // maestro.setTarget(3, 4*channels[3]);
    // delay(1000);              
  
}

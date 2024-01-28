#include <sbus.h>
#include <PololuMaestro.h>


#define maestroSerial Serial2

bfs::SbusRx sbus_rx(&Serial2);
bfs::SbusData data;

int sendChannel[15];

MicroMaestro maestro(maestroSerial);

void setup() {
  
  Serial.begin(115200);
  Serial.println("starting up");

  while (!Serial) {}
  /* Begin the SBUS communication */
  sbus_rx.Begin();

  maestroSerial.begin(100000);

}

void loop() {

  if (sbus_rx.Read()) {
    /* Grab the received data */
    data = sbus_rx.data();
    /* Display the received data */
    for (int8_t i = 0; i < data.NUM_CH; i++) {
      Serial.print(data.ch[i]);
      Serial.print("\t");
    }

    /* For loop that maps the SBus values (172 to 1811) to the Maestro quarter microsecond input needed (4000 to 8000), 
    prints the mapped values for the desired servos, and sends the value to the desired Maestro inputs. The lost frame and
    fail safe bools don't seem to work properly if the values aren't mapped in the same loop they are sent in */
    for (int8_t i = 0; i < 4; i++) {
      sendChannel[i] = map(data.ch[i], 172, 1811, 4000, 8000);
      Serial.print(sendChannel[i]);
      Serial.print("\t");      
      maestro.setTarget(i, sendChannel[i]);
    }

    /* Display lost frames and failsafe data */
    Serial.print(data.lost_frame);
    Serial.print("\t");
    Serial.println(data.failsafe);

  }
}

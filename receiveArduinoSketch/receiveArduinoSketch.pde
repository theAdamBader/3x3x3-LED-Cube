/*
 HOW IT WORKS:
 It gets the serial number for the Arduino (9600) and OSC and destination of 
 
 REFERENCE:
 Andrea's if(f == 1): https://github.com/AndreasRef/additional_wekinator_outputs/blob/master/Processing_1_Classifier_robotKeyPress/Processing_1_Classifier_robotKeyPress.pde
 */
import processing.serial.*;
import oscP5.*;
import netP5.*;

Serial myPort;
OscP5 oscP5;
NetAddress dest;

//boolean button = false;
float lastInput = 1;

void setup() {
  size (50, 50);

  myPort = new Serial(this, /*insert what COM port you are using*/"COM5", 9600);

  oscP5 = new OscP5(this, 12000);
  dest = new NetAddress("127.0.0.1", 6448);
}

void draw() {
}


//This is called automatically when OSC message is receiveds
void oscEvent(OscMessage theOscMessage) {
  //println("received message");
  if (theOscMessage.checkAddrPattern("/wek/outputs") == true) {
    if (theOscMessage.checkTypetag("f")) {
      float f = theOscMessage.get(0).floatValue();
      println("received1");


      if (lastInput != f) {
        if (f == 1) {
          myPort.write('1');
          delay(20);
        }

        if (f == 2) {
          myPort.write('2');
          delay(20);
        }

        if (f == 3) {
          myPort.write('3');
          delay(20);
        }

        if (f == 4) {
          myPort.write('4');
          delay(20);
        }
      }
      lastInput = f;
    }
  }
}
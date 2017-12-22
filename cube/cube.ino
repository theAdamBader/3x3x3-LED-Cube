/*
HOW IT WORKS:
    This sends the code into the Arduino, however, you need to open Wekinator, receiveArduinoSketch.pde, input300_webcam.pde
    Using Wekinator classification, it recieves the receiveArduinoSketch and once its played, you choose a class of what position you want to be in, using the input300_webcam
    
REFERENCE:
    Gamaiel Zavala LED Cube example: https://github.com/gzip/arduino-ledcube/blob/master/examples/ledcube/ledcube.pde
 */

#include <LedCube.h>

#define SIZE 3 //defines the size
#define COLS (SIZE*SIZE) //multiples the column of the cube 3*3

byte levelPins[SIZE] = {A0,A1,A2};
byte colPins[COLS] = {2,3,4,5,6,7,8,9,10};

byte currentEffect = 0; //currentEffect changes depending of the postion the user is on

LedCube cube(SIZE, levelPins, colPins);


void setup ()
{ 
  //starting the serial at 9600
  Serial.begin(9600);
}


void loop ()
{
  delay(20);

  if(Serial.available() > 0){//if the available serial is more than 0 the reads the currentEffetc
    currentEffect = Serial.read();


    if(currentEffect == '1'){
      // if effect is 1 then the helicopter sketch works
      //using top and bottom array to allow the sequence to work
      byte topSeq[8] = {
        0,3,6,7,8,5,2,1                  
      };
        
      byte botSeq[8] = {
        8,5,2,1,0,3,6,7                  
      };
      
      //loops the light however has a delay of 0.05 seconds  
      for(byte loops = 0, delay = 50; loops<=8; loops++)
      {
        for(byte s=0; s<8; s++)
        {
          byte seq[] = {
            2,topSeq[s], 1,4, 0,botSeq[s]                              };
          cube.lightSequence(seq, sizeof(seq), delay);
        } 
        
        //if loop is less than 5 then subtract 0.01 second of the delay else, add 0.01 seconds of delay
        if(loops < 5){ delay-=10; } 
        else {delay += 10;}
      }
    }

/* -------------------------------------------------------------------------------- */


    if(currentEffect == '2'){
      // if effect is 2 then diamond and box works
      //diamond has an array while a box is using a 3 * 3 matrix
      byte diamond[] = {
        0,4,  1,1, 1,3, 1,4, 1,5, 1,7,   2,4            
      };
        
      byte box[] = {
        2,0, 2,1, 2,2, 
        1,0, 1,2, 1,6, 
        0,0, 0,1, 0,2,
      };
      
      cube.lightSequence(box, sizeof(box), 200);
      cube.lightSequence(diamond, sizeof(diamond), 400);
    }

/* -------------------------------------------------------------------------------- */

    if(currentEffect == '3'){
      // if effect is 3 then circle will activate at a random level
      for(byte x=0; x<=5; x++)
      {
        cube.lightPerimeter(random(0,cube.getLevels()), random(1,5), random(25,100));
      }
    }
    
/* -------------------------------------------------------------------------------- */

    if(currentEffect == '4'){
     // if effect is 4 then it will play at random columns
    cube.randomColumn(25);
    }
  }
}












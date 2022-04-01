/*
Final_Project_Arduino_Code.ino
Hanwen Shen, Created 8/25/19
This program runs a color sorting device
The functions are
  delMotor()
  agiMotor()

Delivery Motor pins: 5, 6, 7  
Agitator Motor pins: 2, 3, 4  
*/

//stepper motor 1 is the delivery motor
#define DI 6            //Pin 6 controls the direction of the delivery motor
#define PU 7            //Pin 7 controls the spinning of the delivery motor
#define EN 5            //Pin 5 controls the enabling of the delivery motor
//stepper motor 2 is the agitator motor
#define DI2 3           //Pin 3 controls the direction of the agitator motor
#define PU2 4           //Pin 4 controls the spinning of the agitator motor
#define EN2 2           //Pin 5 controls the enabling of the agitator motor

#include <Pixy2.h> //Include the Pixy2 Library
Pixy2 pixy;        // This is the main Pixy object 

int curPos = 0; //current position of the curved pipe on the delivery motor

//This function spins the delivery motor
void delMotor(int tarpos, int curpos){  
  int diff = tarpos - curpos; //calculate and print the difference between the current position and target position
  Serial.print(diff);         //print the difference
    
  if(diff == 1 || diff == 2 || diff == 3){
    digitalWrite(DI, HIGH);   //the motor will turn clockwise

    for(int i = 0; i < diff; i++){
     for (int x = 0; x < 458; x++){   //send 458 pulses to turn 60 degrees
      digitalWrite(PU, HIGH);
      delay(1);                       //the frequency of the pulses is 1Hz
      digitalWrite(PU, LOW);      
      delay(1);
      }
    }
  } 

  else if(diff == 4 || diff == 5 || diff == 6){
    diff = 6 - diff;
    
    digitalWrite(DI, LOW);   //the motor will turn anti-clockwise

    for(int i = 0; i < diff; i++){
     for (int x = 0; x < 458; x++){   //send 458 pulses to turn 60 degrees
      digitalWrite(PU, HIGH);
      delay(1);                       //the frequency of the pulses is 1Hz
      digitalWrite(PU, LOW);      
      delay(1);
      }
    }
  } 

  else if(diff == -1 || diff == -2 || diff == -3){
    diff = - diff;
    
    digitalWrite(DI, LOW);   //the motor will turn anti-clockwise

    for(int i = 0; i < diff; i++){
     for (int x = 0; x < 458; x++){   //send 458 pulses to turn 60 degrees
      digitalWrite(PU, HIGH);
      delay(1);                       //the frequency of the pulses is 1Hz
      digitalWrite(PU, LOW);      
      delay(1);
      }
    }
  } 

  else if(diff == -4 || diff == -5 || diff == -6){
    diff = - diff;
    diff = 6 - diff;
    
    digitalWrite(DI, HIGH);   //the motor will turn clockwise

    for(int i = 0; i < diff; i++){    
     for (int x = 0; x < 458; x++){   //send 458 pulses to turn 60 degrees
      digitalWrite(PU, HIGH);
      delay(1);                       //the frequency of the pulses is 1Hz
      digitalWrite(PU, LOW);      
      delay(1);
      }
    }
  } 
  curPos = tarpos;    //let the new current position equal to the target position            
}

//This function spins the agitator motor at 120 degree
void agiMotor(){
  for(int i = 0; i < 1; i++){         //spin for one time
     for (int x = 0; x < 915; x++){   //send 915 pulses to turn 120 degrees
      digitalWrite(PU2, HIGH);
      delay(1);
      digitalWrite(PU2, LOW);         //the frequency of the pulses is 1Hz
      delay(1);
      }
    }
  }

void setup() {
  //set all the motor pins to output
  pinMode(DI, OUTPUT);    
  pinMode(PU, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(DI2, OUTPUT);
  pinMode(PU2, OUTPUT);
  pinMode(EN2, OUTPUT);

  pixy.init();                    //initiate the pixy2 camera

  Serial.begin(115200);           //start the serial connection to the computer
  Serial.print("Starting...\n");  
}
 

void loop() {
  digitalWrite(EN, LOW);          //enable the delivery motor
  digitalWrite(EN2, LOW);         //enable the agitator motor
  digitalWrite(DI, HIGH);         //set the direction of delivery motor to anticlockwise
  digitalWrite(DI2, HIGH);        //set the direction of agitator motor to anticlockwise

  int i;
  int tarPos;     //create a variable to store the target position

  agiMotor();     //spin the agitator motor for 120 degrees
  
  delay(1000);     //a short delay
  
  pixy.ccc.getBlocks();   //determine if any block is detected
  
  if (pixy.ccc.numBlocks) //if a block is detetced
  {
    Serial.print("Detected ");  
    tarPos = pixy.ccc.blocks[i].m_signature;  //let the target position equals to the signature of the block detected
    Serial.println(tarPos);

    delMotor(tarPos,curPos);    //spin the delivery motor accoring to the target position and current position
    delay(1000);  //a short delay
    }
}

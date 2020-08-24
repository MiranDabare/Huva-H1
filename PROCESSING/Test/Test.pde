import controlP5.*; //import ControlP5 library
import processing.serial.*;

String myText="";
String Test4Text="";

int TestNumber = 1;

Serial port;

ControlP5 cp5; //create ControlP5 object
PFont font;

void setup(){ //same as arduino program

  size(600, 600);    //window size, (width, height)
  
  printArray(Serial.list());   //prints all available serial ports
  
  port = new Serial(this, "COM3", 9600);  //i have connected arduino to com3, it would be different in linux and mac os
  port.bufferUntil('\n');
  
  //lets add buton to empty window
  
  cp5 = new ControlP5(this);
  font = createFont("calibri light bold", 20);    // custom fonts for buttons and title
  
  cp5.addButton("RGB_Test")     //"red" is the name of button
    .setPosition(100, 50)  //x and y coordinates of upper left corner of button
    .setSize(180, 70)      //(width, height)
    .setFont(font)
  ;   

  cp5.addButton("Button_Test")     //"yellow" is the name of button
    .setPosition(100, 150)  //x and y coordinates of upper left corner of button
    .setSize(180, 70)      //(width, height)
    .setFont(font)
  ;

  cp5.addButton("Remote_Reciever")     //"blue" is the name of button
    .setPosition(100, 250)  //x and y coordinates of upper left corner of button
    .setSize(180, 70)      //(width, height)
    .setFont(font)
  ;
  
  cp5.addButton("Buzzer_Test")     //"alloff" is the name of button
    .setPosition(100, 350)  //x and y coordinates of upper left corner of button
    .setSize(180, 70)      //(width, height)
    .setFont(font)
  ;
    cp5.addButton("Buzzer_On")     //"alloff" is the name of button
    .setPosition(100, 450)  //x and y coordinates of upper left corner of button
    .setSize(100, 50)      //(width, height)
    .setFont(font)
  ;
  
    cp5.addButton("SMS_Sending")     //"red" is the name of button
    .setPosition(350, 50)  //x and y coordinates of upper left corner of button
    .setSize(180, 70)      //(width, height)
    .setFont(font)
  ;   

  cp5.addButton("SMS_Recieving")     //"yellow" is the name of button
    .setPosition(350, 150)  //x and y coordinates of upper left corner of button
    .setSize(180, 70)      //(width, height)
    .setFont(font)
  ;

  cp5.addButton("Siren_Transmitter")     //"blue" is the name of button
    .setPosition(350, 250)  //x and y coordinates of upper left corner of button
    .setSize(180, 70)      //(width, height)
    .setFont(font)
  ;
  

}

void draw(){  //same as loop in arduino

  background(150, 0 , 150); // background color of window (r, g, b) or (0 to 255)
  
  //lets give title to our window
  fill(0, 255, 0);               //text color (r, g, b)
  textFont(font);
  text("HUVA H1 TEST PANEL", 180, 30);  // ("text", x coordinate, y coordinat)
  
  if (TestNumber == 2)
  {
  text(myText, 130, 240);
  myText="";
  }
  
   if (TestNumber == 3)
  {
  text(myText, 130, 340);
  myText="";
  }
  
     if (TestNumber == 4)
  {
  text(myText, 130, 440);
  myText="";
  }
  
       if (TestNumber == 5)
  {
  text(myText, 230, 240);
  myText="";
  }




}

void serialEvent (Serial port){
myText = port.readStringUntil('\n');
}

//lets add some functions to our buttons
//so whe you press any button, it sends perticular char over serial port

void RGB_Test(){
  port.write('1');
}

void Button_Test(){
  port.write('2');
  TestNumber = 2;
}

void Remote_Reciever(){
  port.write('3');
  TestNumber = 3;
}

void Buzzer_Test(){
  port.write('4');
  TestNumber = 4;
}

void Buzzer_On(){
  for (int i = 0; i < 10; i++)
  {
    port.write('9');
  }
}

void SMS_Sending(){
  port.write('5');
  TestNumber = 5;
}

void SMS_Recieving(){
  port.write('6');
}

void Siren_Transmitter(){
  port.write('7');
}

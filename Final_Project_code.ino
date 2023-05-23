#include <Servo.h> //include Servo Library

int servoPin = 3;  //Declare variable for servo motor 1
int servoPin1 = 5; //Declare variable for servo motor 2
Servo servo;       //Creating servo object 1
Servo servo1;      //Creating servo object 2
int angle = 0;     // servo position in degrees

int flexPin =2;    //declaring variable for metal sensor pin

int ir=8;          //declaring variable for 1st IR sensor pin
int ir1=4;         //declaring variable for 2nd IR sensor pin

int moisture=9;    //declaring variable for moisture sensor pin

int echoPin =6;    //declaring variable for echo pin of ultrasonic sensor
int triggerPin =7; //declaring variable for trigger pin of ultrasonic sensor

int in1=10;        // declaring variables for motor 1 control pins
int in2=11;

int in3=12;        // declaring variables for motor 2 control pins
int in4=13;


char link1[50] = "http://maps.google.com/maps?q=loc:";  //declares a character array to store URL

void message()  //message function to obtain GPS location and send text message
{
    //gps
      int i=0;
      float lat,lon;
      char inByte;
      char latitude[20],longitude[20]; //character array to store longitude and latitude
      //==================== searching for "GG" ===================//
      do
      {
         do
        {
            while ( !Serial.available() );     // wait until any serial data available     
        } while ( 'G' != Serial.read() );      // reading a character from the GPS
      
         while(!Serial.available());           // wait until any serial data available 
      } while ( 'G' != Serial.read() );        // reading a character from the GPS
    //==================== searching for "GG" ===================//




 
    //============== seeking for north cordinate ==============//
    do
    {
        while ( !Serial.available() );        // wait until any serial data available     
    } while ( ',' != Serial.read() );         // reading a character from the GPS
 
    do
    {
        while ( !Serial.available() );        // wait until any serial data available
    } while ( ',' != Serial.read() );         // reading a character from the GPS
    //============== seeking for north cordinate ==============//
 
    //============== printing the north cordinate ===============//
 
    do
    {
        while ( !Serial.available() );  // wait until any serial data available
        inByte = Serial.read();         // read single character and store it in inByte variable 
        latitude[i]=inByte;             // store each character in latitude array
        i++;                            // increment i value by 1
    } while ( ',' != inByte );          // stop fetching for latitude after getting , character
        i--;
        latitude[i]='\0';               // assign last character of array as null character
    i=0;
    //============== printing the north cordinate ===============//
 
    //============== seeking for east cordinate ==============//
    do
    {
        while ( !Serial.available() );    // wait until any serial data available
    } while ( ',' != Serial.read() );     // reading a character from the GPS
    //============== seeking for east cordinate ==============//
 
    //============== printing the east cordinate ===============//
    do
    {
        
        while ( !Serial.available() );    // wait until any serial data available
        inByte = Serial.read();           // read single character and store it in inByte variable 
        longitude[i]=inByte;              // store each character in longitude array
        i++;                              // increment i value by 1

    } while ( ',' != inByte );            // stop fetching for longitude after getting , character
    i--;
    longitude[i]='\0';                    // assign last character of array as null character



    //============== printing the cordinates ===============//

    Serial.println(latitude);
    Serial.println(longitude);

    //Latitude
    int x=atof(latitude);   //Converts the latitude string to a float value (x) 
    x=x/100;
    Serial.println(x);      //prints the result on Serial monitor   
    

    //Longitude
    int y=atof(longitude);  //Converts the latitude string to a float value (y)
    y=y/100;
    Serial.println(y);       //prints the result on Serial monitor   

    char link2[50];               // declare character array link 2
    char link[100];               // declare character array link
    sprintf(link2,"%d,%d",x,y);  // format and concatenate the x and y values into 'link2' array
    sprintf(link,"%s%s",link1,link2);  // concatenates link1 and link2 into 'link' array to form a complete URL
    Serial.println(link);         // print the URL on Serial Monitor
 
    Serial.println("AT+CMGF=1");  //Sends the AT command AT+CMGF=1 to the GSM module to set the SMS mode to text mode
    delay(1000);                  //The delay of 1000 milliseconds
    Serial.println("AT+CMGS=\"8722009547\"\r");  //Sends the AT command to the GSM module. This command sets the destination phone number to which the SMS will be sent
    delay(1000);
    Serial.println("Garbage is filled plz visit the location"); //Sends the message content "Garbage is filled plz visit the location" to the GSM module. This message will be sent as an SMS to the specified phone number
    delay(100);
    Serial.println(link);   //Sends the URL stored in the link variable to the GSM module. This URL contains the latitude and longitude information.
    delay(1000);
    Serial.println((char)26);       // Sends the ASCII code of CTRL+Z (character 26) to the GSM module. This is used to indicate the end of the message content
    Serial.println("message sent");
    delay(5000);                    // delay of 5 seconds
}

int ultra1()
{
   long highPulseDuration;
   int calculatedDistanceCm;

   digitalWrite(triggerPin, LOW); //Set the trigPin to low, before setting it to high for the pulse
   delayMicroseconds(5);

   digitalWrite(triggerPin, HIGH); // Create the 10 seconds pulse on the trig pin
   delayMicroseconds(10);

   digitalWrite(triggerPin, LOW);  // Set the pin to low to end the pulse


   highPulseDuration = pulseIn(echoPin, HIGH); //Uses the pulseIn() function to measure the duration of the HIGH pulse on the echoPin. The duration is stored in the highPulseDuration variable.

   calculatedDistanceCm = highPulseDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

   return calculatedDistanceCm; // Displays the distance on the Serial Monitor
}

void setup()
  {
  Serial.begin(9600);       // initialize the serial communication at a baud rate of 9600. 
  servo.attach(servoPin);   //attach function is called to attach the servo motor to the specified pin servoPin
  servo1.attach(servoPin1); //attach function is called to attach the servo motor to the specified pin servoPin1
 
  // pinMode() is used to set the specified pins as either input or output

  pinMode(in1,OUTPUT);      // in1 set as OUTPUT pin
  pinMode(in2,OUTPUT);      // in2 set as OUTPUT pin
  pinMode(in3,OUTPUT);      // in3 set as OUTPUT pin
  pinMode(in4,OUTPUT);      // in4 set as OUTPUT pin
  pinMode(ir,INPUT);        // ir set as OUTPUT pin
  pinMode(ir1,INPUT);       // ir2 set as OUTPUT pin
  pinMode(moisture,INPUT);        // in1 set as OUTPUT pin
  pinMode(triggerPin, OUTPUT);       // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);    //echoPin is set as an INPUT pin
  pinMode(flexPin,INPUT);     //flexPin is set as an INPUT pin
   for(angle = 45; angle > 0; angle--)  //The first loop sets the servo motor position from 45 degrees to 0 degrees with a step of -1 degree
    {
        servo.write(angle);   //servo write function is called to set the servo motor position
        delay(15);            //delay of 15 milliseconds
    }  
    for(angle = 45; angle > 0; angle--) //The second loop sets the servo1 motor position from 45 degrees to 0 degrees with a step of -1 degree.
    {
        servo1.write(angle);    //servo write function is called to set the servo motor position
        delay(15);              //delay of 15 milliseconds
    }    
}

void loop() 
  {
  digitalWrite(in1,0); //sets the in1 pin to LOW state.
  digitalWrite(in2,1); //sets the in2 pin to HIGH state.
  int ultra =ultra1(); //calls the ultra1() function and assigns its return value to the ultra variable.



  if(ultra<=5)         //Checks if the value of ultra is less than or equal to 5
  {
     digitalWrite(in3,1);  //sets the in3 pin to HIGH state.
     digitalWrite(in4,0);  //sets the in4 pin to LOW state. to turn on motor2
     delay(5000);          // delay of 5 seconds
     digitalWrite(in3,0);  //sets the in3 pin to LOW state.
     digitalWrite(in4,0);  //sets the in4 pin to LOW state. to turn off motor2
     Serial.println("GSM message"); //"GSM message" is printed to the Serial Monitor
     message();            // meassage function is called
  }
  else
  {
    digitalWrite(in3,0); // if the condition in if statement is false motor 2 will be in off condition
    digitalWrite(in4,0);
  }
 int irsensor1=digitalRead(ir1); //Reads the state of ir1 pin and assigns its value to the irsensor1 variable.
  if(irsensor1 == 0)             //If the value of irsensor1 is equal to 0, the following actions are performed
  {
    delay(1400);                 //delay of 1.4 seconds
    digitalWrite(in1,0);         //sets the in1 pin to LOW state.
    digitalWrite(in2,0);         //sets the in1 pin to LOW state. to turn off motor 1
    delay(2000);                 //delay of 2 seconds
    while(1)                     //creates an infinite loop
    {
      int flexValue = digitalRead(flexPin); // reads the state of the flexPin and assigns it to the flexValue variable
      Serial.println(flexValue);            // prints the value of flexValue to the Serial Monitor.
      delay(100);                           // delay of 100 milliseconds
      if(flexValue == 1)                    // check if flexValue  is equal to 1.
      {
        Serial.println("Metallic  waste is present"); //print on serial monitor
        for(angle = 0; angle < 180; angle++)   //A for loop is used to control the angle of the servo motor. It starts with angle set to 0 and increments it by 1 until it reaches 180
        {
        servo.write(angle);                // For each angle value, it calls servo.write(angle) to set the servo position
        delay(15);                         // delay of 15 milliseconds
        }
   //now scan back from 180 to 0 degrees
       for(angle = 180; angle > 0; angle--) 
        {
        servo.write(angle);
        delay(15);
        }
      delay(3000);
      break;       // breaks from while loop
      }
      else 
      {
        delay(3000);
        break;     // breaks from while loop
      }


    }
  }
  digitalWrite(in1,0); //sets the in1 pin to LOW state.
  digitalWrite(in2,1); //sets the in2 pin to HIGH state.to turn on motor1 again
  
  int irsensor2=digitalRead(ir);  // reads the state of the ir pin and assigns it to the irsensor2 variable
  if(irsensor2 == 0)              //checks if irsensor2 is equal to 0 
  {
    delay(800);           //delay of 800 milliseconds
    digitalWrite(in1,0);  //sets the in1 pin to LOW state.
    digitalWrite(in2,0);  //sets the in2 pin to LOW state. to turn off motor 1
    delay(2000);          //delay of 2000 milliseconds
    while(1)              //creates an infinite loop
    {
    int var=digitalRead(moisture); //reads the state of the moisture pin and assigns it to the var variable

    if(var==1)             // checks if var is equal to 1 
    {
      Serial.println("Wet waste is present"); //prints on serial monitor
      for(angle = 0; angle < 180; angle++)    //A for loop is used to control the angle of the servo motor. It starts with angle set to 0 and increments it by 1 until it reaches 180
      {
        servo1.write(angle);                  // For each angle value, it calls servo.write(angle) to set the servo position
        delay(15);
      }
    
    // now scan back from 180 to 0 degrees
    for(angle = 180; angle > 0; angle--) 
      {
        servo1.write(angle);
        delay(15);
      }
     delay(3000);
      break;                                  // breaks from while loop
    }

    else
    {
      Serial.println("Dry waste is present"); // prints on serial monitor
       delay(3000);                           // delay of 3 seconds
      break;                                  // breaks from while loop
    }
    }
  }
  digitalWrite(in1,0); // sets the in1 pin to LOW state.
  digitalWrite(in2,1); // sets the in2 pin to HIGH state to turn on motor1 again
  delay(1000);         // delay of 1 second
}

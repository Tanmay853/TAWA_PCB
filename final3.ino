//--------------------------variables-------------------------------//

const int pwmPin = 0;
const int fanPin=1;
const int inc=2;
const int dec=3;
const int enter=4;
const int reset=11;
const int mode=28;//online or offline
const int online=11;
const int offline=28;
const int p1=2;
const int p2=3;
const int p3=4;
const int custom=28;

float room;

float T1;
float t1;
float m1;

float T2;
float t2;
float m2;

float T3;
float t3;
float m3;

int t;

boolean flag=0;
boolean comp_flag=0;

boolean cooling = 0;


#include <Adafruit_MAX31865.h>
// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(17, 19, 16, 18);
// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library for ILI9341
#include "SPI.h"
#define TFT_CS        10
#define TFT_RST       9
#define TFT_DC        8
#define TFT_MOSI 7  // Data out
#define TFT_SCLK 6  // Clock out
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST,5);



//---------------------------------ESP_ONLINE_CONNECT-----------------------------//

void take_from_esp()
{
  tft.fillScreen(ILI9341_BLACK);
  while(Serial1.available() <= 0)
  {
    Serial.println("sdf");
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }  
  }

  if(Serial1.available() > 0)
  {
    String receivedData = Serial1.readStringUntil('\n');
     Serial.println(receivedData);
    int arr[10];
    int i = 0;
    for(int j=0;j<receivedData.length();j++)
    {
      int val = 0;
      char ch = receivedData[j];
      while(ch!= ',' && j< receivedData.length())
      {
        val = 10 *val + (ch - '0');
        j++;
        ch = receivedData[j];
      }
      arr[i] = val;
      Serial.println(arr[i]);
      i++;

      
    }
    T1=(float)arr[1];
    t1=(float)arr[5];
    T2=(float)arr[2];
    t2=(float)arr[6];
    T3=(float)arr[3];
    t3=(float)arr[7];
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }  

    
  }
}

//--------------------------Time input-----------------------//

int taket(int t)
{
  tft.fillRect(0, 0, 300, 200, ILI9341_BLACK);
  while(digitalRead(enter)==HIGH)
  {
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }  
    if (digitalRead(inc) == LOW) 
    { // Check if button is pressed
      t+=5;  // Increment the variable
      tft.fillRect(0, 0, 300, 45, ILI9341_BLACK);
      tft.setCursor(0, 0);
      tft.print("t = ");
      tft.print(t);
      delay(100); // Debounce delay to avoid multiple increments on a single press
    }
    if (digitalRead(dec) == LOW) 
    { // Check if button is pressed
      t-=5;  // Increment the variable
      tft.fillRect(0, 0, 300, 45, ILI9341_BLACK);
      tft.setCursor(0, 0);
      tft.print("t = ");
      tft.print(t);    
      delay(100); // Debounce delay to avoid multiple increments on a single press
    }
  }
  return t;
}

//------------------------------Input temperature-------------------------//


int takeT(int t)
{
  tft.fillRect(0, 0, 300, 200, ILI9341_BLACK);
  while(digitalRead(enter)==HIGH)
  {
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }  
    if (digitalRead(inc) == LOW) 
    { // Check if button is pressed
      t+=5;  // Increment the variable
      tft.fillRect(0, 0, 300, 45, ILI9341_BLACK);
      tft.setCursor(0, 0);
      tft.print("T = ");
      tft.print(t);
      delay(100); // Debounce delay to avoid multiple increments on a single press
    }
    if (digitalRead(dec) == LOW) 
    { // Check if button is pressed
      t-=5;  // Increment the variable
      tft.fillRect(0, 0, 300, 45, ILI9341_BLACK);
      tft.setCursor(0, 0);
      tft.print("T = ");
      tft.print(t);    
      delay(100); // Debounce delay to avoid multiple increments on a single press
    }
  }
  return t;
}

//------------------------------Offline input----------------------------------//


void take_from_TFT()
{
  tft.fillScreen(ILI9341_BLACK); // Fill the screen with black color
  tft.setRotation(1); // Rotate the display if necessary (0, 1, 2, or 3 depending on the orientation)
  tft.setTextColor(ILI9341_WHITE); // Set text color to white
  tft.setTextSize(5); // Set text size (1, 2, 3, 4, 5, 6, 7, or 8)

  // Set the cursor position to print text
  while(digitalRead(dec) == HIGH && digitalRead(inc) == HIGH)
  {
    tft.setCursor(10, 10);
    tft.println("Enter the");
    tft.println("inputs");
    delay(100);
    //restart the code
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }  
  }



  int x=80,y=0;
  x=takeT(x);
  T1=(float)x;
  tft.println();
  tft.print("T1= ");
  tft.print(T1);
  delay(1000);

//restart the code
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }
  y=taket(y);
  t1=(float)y;
  tft.println();
  tft.print("t1= ");
  tft.print(t1);
  delay(1000);

//restart the code
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }
  x=takeT(x);
  T2=(float)x;
  tft.println();
  tft.print("T2= ");
  tft.print(T2);
  delay(1000);

//restart the code
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }
  y=taket(y);
  t2=(float)y;
  tft.println();
  tft.print("t2= ");
  tft.print(t2);
  delay(1000);

//restart the code
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }
  x=takeT(x);
  T3=(float)x;
  tft.println();
  tft.print("T3= ");
  tft.print(T3);
  delay(1000);

//restart the code
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }
  y=taket(y);
  t3=(float)y;
  tft.println();
  tft.print("t3= ");
  tft.print(t3);
  delay(1000);
}

//----------------------------Initialization by screen----------------------------------//

void In_mode()
{
  tft.fillScreen(ILI9341_BLACK); // Fill the screen with black color
  while(digitalRead(online)==HIGH && digitalRead(offline)==HIGH)
  {
    tft.setRotation(1); // Rotate the display if necessary (0, 1, 2, or 3 depending on the orientation)
    tft.setTextSize(4);
    tft.setCursor(0,0);  
    tft.println("     Mode");
    tft.println();
    tft.println(" Online ---->");
    tft.println();
    tft.println();
    tft.println();
    tft.println(" Offline --->");
  }
  if(digitalRead(online)==LOW)
  {
    //get data fromESP32
    take_from_esp();

  }
  else
  {
    delay(1000);
    tft.fillScreen(ILI9341_BLACK); // Fill the screen with black color
    while(digitalRead(p1)==HIGH && digitalRead(p2)==HIGH && digitalRead(p3)==HIGH  && digitalRead(custom)==HIGH)
    {
      tft.setRotation(1); // Rotate the display if necessary (0, 1, 2, or 3 depending on the orientation)
      tft.setTextSize(4);
      tft.setCursor(0,0);  
      tft.println("  Profiles");
      tft.println("<-- Profile 1");
      tft.println();
      tft.println("<-- Profile 2");
      tft.println();
      tft.println("<--- Desolder");
      tft.println(" Custom ---->");
      if (digitalRead(reset) == LOW)
      {
        delay(1000);
        TFT();
      } 
    }
    if(digitalRead(p1)==LOW)
    {
      flag=1;
      
      //ASSIGN  THE VALUES
      T1=100.0;
      T2=150.0;
      T3=235.0;
      t1=30.0;
      t2=120.0;
      t3=210.0;

      graph();
    }
    else if(digitalRead(p2)==LOW)
    {
      flag=1;

      //ASSIGN  THE VALUES
      T1=150.0;
      T2=180.0;
      T3=240.0;
      t1=50.0;
      t2=130.0;
      t3=170.0;

      graph();
    }
    else if(digitalRead(p3)==LOW)
    {
      flag=1;
      //assign the values
      T1=90.0;
      T2=180.0;
      T3=270.0;
      t1=60.0;
      t2=140.0;
      t3=240.0;

      graph();    
    }
    else
    {
      //get data from switches
      delay(1000);
      take_from_TFT();
      graph();
    }
  }
}

void graph()
{
  //display the inputs
  //Press the enter key to submit the inputs
  tft.fillScreen(ILI9341_BLACK); // Fill the screen with black color
  while(digitalRead(enter)==HIGH)
  {
    tft.setRotation(1);
    tft.setTextSize(4);
    tft.setCursor(0,0);
    tft.print("T1= ");
    tft.println(T1);
    tft.print("t1= ");
    tft.println(t1);
    tft.print("T2= ");
    tft.println(T2);
    tft.print("t2= ");
    tft.println(t2);
    tft.print("T3= ");
    tft.println(T3);
    tft.print("t3= ");
    tft.println(t3);

    //restart the code
    if (digitalRead(reset) == LOW)
    {
      delay(1000);
      TFT();
    }
  }

  //display graph
  tft.fillScreen(ILI9341_BLACK); // Fill the screen with black color
  tft.setRotation(1);
  tft.setTextSize(2);
  tft.setCursor(0,220);
  tft.print("------Time--------->");
  tft.setRotation(0);
  tft.drawLine((int)(0.8*room),0,(int)(0.8*T1), (int)(320.0*t1/(t3+60.0)), ILI9341_GREEN);
  tft.drawLine((int)(0.8*T1), (int)(320.0*t1/(t3+60.0)), (int)(0.8*T2), (int)(320.0*t2/(t3+60.0)), ILI9341_RED);
  tft.drawLine((int)(0.8*T2), (int)(320.0*t2/(t3+60.0)), (int)(0.8*T3), (int)(320.0*t3/(t3+60.0)), ILI9341_BLUE);
  tft.drawLine((int)(0.8*T3), (int)(320.0*t3/(t3+60.0)), (int)(0.8*T3), (int)(320.0*(t3+30.0)/(t3+60.0)), ILI9341_BLUE);
  tft.drawLine((int)(0.8*T3), (int)(320.0*(t3+30.0)/(t3+60.0)),(int)(0.8*30),(int)(320.0*(0.4*T3+8+t3)/(t3+60.0)) , ILI9341_YELLOW);
}

//-----------------------------------TFT working-------------------------------//

void TFT()
{
  flag=0;
  cooling = 0;
  comp_flag=0;
  T1=0;
  T2=0;
  T3=0;
  t1=0;
  t2=0;
  t3=0;

  digitalWrite(pwmPin,HIGH);
  digitalWrite(fanPin,HIGH);
  
  //PT100 definition 
  thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  room=thermo.temperature(RNOMINAL, RREF);
  delay(1000);  

  //display room temp.on screen
  tft.fillScreen(ILI9341_BLACK); // Fill the screen with black color
  tft.setRotation(1); // Rotate the display if necessary (0, 1, 2, or 3 depending on the orientation)
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0,0);
  tft.println("Plate temp.");
  tft.println();
  tft.print(room);
  delay(3000);

  // PWM(1.00);
  // delay(2000);

  

  loop();
}

//----------------------------setup-----------------------------------------//

void setup() 
{
  delay(1000);
  //pinmodes
  pinMode(inc, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  pinMode(dec, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  pinMode(enter, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  pinMode(reset, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  pinMode(mode, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  pinMode(online,INPUT_PULLUP);
  pinMode(offline,INPUT_PULLUP);

  pinMode(pwmPin, OUTPUT);
  pinMode(fanPin, OUTPUT);

  pinMode(p1,INPUT_PULLUP);
  pinMode(p2,INPUT_PULLUP);
  pinMode(p3,INPUT_PULLUP);
  pinMode(custom,INPUT_PULLUP);

  //UART pins
  Serial1.setTX(12);
  Serial1.setRX(13);
  Serial.begin(9600); // Start UART at baud rate 115200
  Serial1.begin(115200); // Start UART1

  //tft deinition
  tft.begin();
  TFT();


}

//------------------------------code starts--------------------------------------//

float prev_temp = room;
float new_temp = room;

void loop() 
{
  if(flag==0)
  {
    In_mode();
    flag=1;
  }
  if(comp_flag==0)
  {
    //warm up period
    PWM(1.0);
    delay(5000);
    t=0;
    // t2=t2-10;
    //t1 = t1 + 10;
    m1=(T1-room)/(t1);
    m2=(T2-T1)/(t2-t1);
    m3=(T3-T2)/(t3-t2);

    digitalWrite(fanPin,HIGH);
    comp_flag=1;
  }

  //restart the code
  if (digitalRead(reset) == LOW)
  {
    delay(100);
    TFT();
  }

  t=t+2;
  float temp_req=0;
  float kp_upar,kp_down;
  float kd = 0.004;

  uint16_t color=0;
  String phase="";

  float temp_cur=thermo.temperature(RNOMINAL, RREF);

  
  Serial.println(temp_cur);

  if(t<=t1)
  {
    temp_req=room+m1*(t+5);
    kp_upar = 0.4;
    kp_down=0.7;
    color=ILI9341_GREEN;
    phase="Preheat";
  }
  else if(t<=t2 && t>t1)
  {
    temp_req=T1+m2*(t-t1);
    kp_upar=0.8;
    kp_down = 0.4;
    color=ILI9341_RED;
    phase="Soak";

    // kd = 0.0045;
  }
  else if(t<=t3 && t>t2)
  {
    temp_req=T2+m3*(t-t2);
    kp_upar=0.03;
    kp_down = 0.8;
    color=ILI9341_BLUE;
    phase="Reflow";
  }
  else if(t > t3 && t<= t3+30){
    temp_req = T3;
    kp_upar=0.03; //0.03
    kp_down = 0.94;
    color=ILI9341_BLUE;
    phase="Reflow";

  }

  else
  {

    temp_req=40.0; 
    
    if(temp_cur <= temp_req)
    {
      stop();
    }

    else
    {
      cooling = 1;
      
      color=ILI9341_YELLOW;
      phase="Cooling";
      //switch ON the 
      digitalWrite(fanPin,LOW);

    }

    
  }

  new_temp = temp_cur;
  
  //transfer data to ESP32 for plotting
  Serial1.println(String(temp_cur, 2)+","+String(temp_req, 2)+","+t+",");

  
  float duty=0.0;

  if(cooling)
  {
    duty=0.0;
    PWM(0.00);
    // digitalWrite(fanPin,LOW);
  }
  else
  {
    if(temp_req>temp_cur)
    {
      float diff=temp_req-temp_cur;
      duty = 1.00;

      // if(t > t2 && t<t3)
      // {
      //   duty = 0.09*diff;
      // }

      duty = kp_down* diff - kd * (new_temp - prev_temp);

      if(duty>1.0)
        duty=1.0;
      
    }
    
    else
    {
      float diff=temp_cur - temp_req;

      duty = 1 - kp_upar*diff - kd * (new_temp - prev_temp);;

      if(duty < 0.0)
      {
        duty = 0.0;
      }
      
    }

    if(t>=t2-2 && t<t2){
      duty = 1.00;
    }

    if(t >= t1-8 && t < t1){
      duty = 0.1;
    }

    PWM(duty);
  }

  prev_temp = new_temp;

  //display current temp, reqd temp, duty on TFT
  tft.fillRect(170, 0, 70, 160, ILI9341_BLACK);
  tft.setRotation(1);
  tft.setTextSize(2);
  tft.setCursor(0,0);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Actual:");
  tft.println(temp_cur);
  // tft.print("Duty:");
  // tft.println(duty);
  tft.print("Reqd.:");
  tft.println(temp_req);
  tft.print("Time:");
  tft.println(t);
  tft.print("Phase:");
  tft.setTextColor(color);
  tft.print(phase);

  //plot pixel point
  tft.setRotation(0);
  tft.drawPixel((int)(0.8*temp_cur),(int)(320.0*t/(t3+60.0)),color);

}

//-----------------------------------PWM------------------------------------------//

void PWM(float duty)//10 Hz 
{
  // Serial.println("PWM Mein aa gya mein");
  for(int i=0;i<20;i++)
  {
    
    digitalWrite(pwmPin, LOW);
    delay(duty*100); // Change duty cycle every second for demonstration

    if(duty != 1.0){
      digitalWrite(pwmPin, HIGH);
      delay((1.0-duty)*100);
    }
    
  }
}


void stop()
{
  delay(3000);
  digitalWrite(fanPin,HIGH);
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(0,0);
  tft.println("Finished");
  tft.setCursor(0,200);
  tft.println("OK");
  while(digitalRead(enter)==HIGH)
  {;}
  TFT();

}





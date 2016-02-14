/*
 * Program to control RGB LED or LED strip using serial comands
 * Author : Shreyas K
 */
class LED
{
  int redLed, greenLed, blueLed; //output pins
  
  public:
  
  int red, green, blue;  //pwm value 0 - 255
  
  void writeColor() //Function to set the analog Output based on red, green and blue values
  {
    if(red>255)
      red = 255;
    else if(red <0)
      red = 0;
    if(green>255)
      green = 255;
    else if(green <0)
      green = 0;
    if(blue>255)
      blue = 255;
    else if(blue <0)
      blue = 0;
    analogWrite(redLed, red);
    analogWrite(greenLed, green);
    analogWrite(blueLed, blue);
  }
    
  LED(int r, int g, int b)  //input parameters to set the output pins
  {
    redLed = r;
    greenLed = g;
    blueLed = b;
    pinMode(r, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(b, OUTPUT);
    defaultSerialFadeTime = 200;
    defaultSerialFadeSteps = 20;
  }

  void init() //initialise 
  {
    Serial.begin(115200);
    Serial.println("Enter \"H\" for help");
  }

  int defaultSerialFadeTime, defaultSerialFadeSteps; //store default values
  
  void fade(int r, int g, int b, int fadeTime = 0, int fadeSteps = 10) //function to fade between set colour to new colour
  {
    int prevRed = red;
    int prevGreen = green;
    int prevBlue = blue;
    for(int fadeStepCounter = 1; fadeStepCounter <= fadeSteps; fadeStepCounter++)
    {
      red = map(fadeStepCounter, 0, fadeSteps, prevRed, r);
      green = map(fadeStepCounter, 0, fadeSteps, prevGreen, g);
      blue = map(fadeStepCounter, 0, fadeSteps, prevBlue, b);
      writeColor();
      delay(fadeTime/fadeSteps);
    }
  }

  void setColor(int r, int g, int b) //function to set colour
  {
    red = r;
    green = g;
    blue = b;
    writeColor();
  }

  void readSerialData()  //read serial input and perform action
  { 
    char dataParameter; 
    if(Serial.available())
    {
      dataParameter = (byte)Serial.read();
      if(dataParameter == 'R' || dataParameter == 'r')
      {
        red = Serial.parseInt();
        writeColor();
      }  
      else if(dataParameter == 'G'|| dataParameter == 'g')
      {
        green = Serial.parseInt();
        writeColor();
      } 
      else if(dataParameter == 'B'|| dataParameter == 'b')
      {
        blue = Serial.parseInt();
        writeColor();
      }
      else if(dataParameter == 'c'|| dataParameter == 'C')
      {
        red = Serial.parseInt();
        green = Serial.parseInt();
        blue = Serial.parseInt();
        writeColor();
      }
      else if(dataParameter == 'F'|| dataParameter == 'f')
      {
        int r, g, b;
        r = Serial.parseInt();
        g = Serial.parseInt();
        b = Serial.parseInt();
        fade(r, g, b, defaultSerialFadeTime, defaultSerialFadeSteps);
      }
      else if(dataParameter == 'T'|| dataParameter == 't')
      {
        defaultSerialFadeTime = Serial.parseInt();
      }
      else if(dataParameter == 'S'|| dataParameter == 's')
      {
        defaultSerialFadeSteps = Serial.parseInt();
      }
      else if(dataParameter == 'P'|| dataParameter == 'p')
      {
        Serial.print("Red = ");
        Serial.println(red);
        Serial.print("Green = ");
        Serial.println(green);
        Serial.print("Blue = ");
        Serial.println(blue);
        Serial.print("Fade length = ");
        Serial.println(defaultSerialFadeTime);
        Serial.print("Fade steps = ");
        Serial.println(defaultSerialFadeSteps);
      }
      else if(dataParameter == 'H' || dataParameter == 'h')
      {
        Serial.println("\"R <0-255>\" to set red");
        Serial.println("\"G <0-255>\" to set green");
        Serial.println("\"B <0-255>\" to set blue");
        Serial.println("\"C <red 0-255>, <green 0-255>, <blue 0-255>\" to set red, green and blue");
        Serial.println("\"F <red 0-255>, <green 0-255>, <blue 0-255>\" to fade to new red, green and blue");
        Serial.println("\"T <fade length>\" to set fade time in milliseconds");
        Serial.println("\"S <step>\" number of steps for fade");
        Serial.println("\"P\" to print current values");
      }
    }
  }
  
};

LED ledStrip(10, 11, 9); //create an object of class LED to handle a LED strip

void setup() {
  ledStrip.init();
}

void loop() {
  //manage LED from serial monitor
  ledStrip.readSerialData();
}

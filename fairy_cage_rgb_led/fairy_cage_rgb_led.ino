const unsigned int RED_PIN = 9;
const unsigned int GREEN_PIN = 10;
const unsigned int BLUE_PIN = 11;

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void hsv2rgb(const float h, const float s, const float v, unsigned int& r, unsigned int& g, unsigned int &b)
{
  float C = s * v;
  float hPrime = h / 60.0;
  float X = C * (1.0 - fabs(fmod(hPrime, 2.0) - 1.0));
  float m = v - C;
  
  if (h >= 0.0 && h < 60.0)
  {
    r = 255 * (C + m);
    g = 255 * (X + m);
    b = 255 * m;
  }
  else if (h >= 60.0 && h < 120.0)
  {
    r = 255 * (X + m);
    g = 255 * (C + m);
    b = 255 * m;
  }
  else if (h >= 120.0 && h < 180.0)
  {
    r = 255 * m;
    g = 255 * (C + m);
    b = 255 * (X + m);
  }
  else if (h >= 180.0 && h < 240.0)
  {
    r = 255 * m;
    g = 255 * (X + m);
    b = 255 * (C + m);
  }
  else if (h >= 240.0 && h < 300.0)
  {
    r = 255 * (X + m);
    g = 255 * m;
    b = 255 * (C + m);
  }
  else if (h >= 300.0 && h < 360.0)
  {
    r = 255 * (C + m);
    g = 255 * m;
    b = 255 * (X + m);
  }
  else
  {} 
}

void lightLED(unsigned int r, unsigned int g, unsigned int b)
{
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}

unsigned int red, green, blue;
unsigned int hue = 180;
boolean ascending = true;

void loop()
{
  if (hue >= 360 + 35)
    ascending = false;
    
  if (hue <= 180)
    ascending = true;
  
  hsv2rgb(hue, 1.0, 1.0, red, green, blue);
  lightLED(red, green, blue);
  delay(50);
  
  if (ascending)
    hue++;
  else
    hue--;
}

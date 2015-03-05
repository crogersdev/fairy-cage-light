const unsigned int RED_PIN = 9;
const unsigned int GREEN_PIN = 10;
const unsigned int BLUE_PIN = 11;

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void hsv2rgb(float h, float s, float v, unsigned int& r, unsigned int& g, unsigned int &b)
{
  if (v < 0)
    v = 0;
  if (v > 1.0)
    v = 1.0;
  if (s < 0)
    s = 0;
  if (s > 1.0)
    s = 1.0;
  
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

void lightLED(const unsigned int r, const unsigned int g, const unsigned int b)
{
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}

void fadeToWhite(const unsigned int hue)
{
  delay(100);
  unsigned int r, g, b;
  
  float deltaRate = 1.1;
  float initDelta = .00000000001;
  float delta = initDelta;
  
  for (float sat = 1.0; sat > 0; sat -= delta)
  {
    hsv2rgb(hue, sat, 1.0, r, g, b);
    lightLED(r, g, b);
    delay(50);
    delta *= deltaRate;
  }
  delay(100);
  delta = initDelta;
  for (float sat = 0.0; sat < 1.0; sat += delta)
  {
    hsv2rgb(hue, sat, 1.0, r, g, b);
    lightLED(r, g, b);
    delay(50);
    delta *= deltaRate;
  }
  delay(100);
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
  
  if (hue % 360 == 0)
    fadeToWhite(hue % 360);
  
  hsv2rgb(hue % 360, 1.0, 1.0, red, green, blue);
  lightLED(red, green, blue);
  delay(50);
  
  if (ascending)
    hue++;
  else
    hue--;
}

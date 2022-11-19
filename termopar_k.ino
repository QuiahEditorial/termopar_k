// Por Roberto A. Zavala
//
// Libro : https://www.amazon.com.mx/dp/B074TTGLL2
// 🙏🏼    : DNv7acPAeVBhTXbKv26itJecPG1SPy2o4F

#include <SPI.h>

#define SO  4
#define CS  5
#define SCK 6

int   B;
float C;
float K;
float F;
float mV;
int   AD;

void setup()
{
Serial.begin(9600);
pinMode(CS, OUTPUT);
pinMode(SO, INPUT);
pinMode(SCK, OUTPUT);
}

void loop()
{
B = readBit(); Serial.print("Bit = "); Serial.println(B);
C = readC();   Serial.print("°C = ");  Serial.println(C);
K = readK();   Serial.print("K = ");   Serial.println(K);
F = readF();   Serial.print("°F = ");  Serial.println(F);
mV= readmV();  Serial.print("mV = ");  Serial.println(mV);

delay(1770);
}

float readmV() { float mv = readBit(); return mv * 0.0103046875;}
float readF()  { float f = readBit();  return f * .45 + 32; }
float readK()  { float c = readBit();  return c  + 273.15;  }
float readC()  { float c = readBit();  return c * 0.25;     }

int readBit()
{
digitalWrite(CS, LOW);
delay(1);

AD = shiftIn(SO, SCK, MSBFIRST);
AD <<= 8;
AD |= shiftIn(SO, SCK, MSBFIRST);

digitalWrite(CS, HIGH);
if (AD & 0x4) { return NAN;}
AD >>= 3;

return AD;
}

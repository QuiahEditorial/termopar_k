// Por Roberto A. Zavala
// Breve : https://es.overleaf.com/read/brrnnhvyfztr
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
pinMode(SO, INPUT);
pinMode(CS, OUTPUT);
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
float readF()  { float f = readC();  return f * 1.8 + 32; }
float readK()  { float c = readC();  return c  + 273.15;  }
float readC()  { float c = readmV();  return 0.0115 + 25.4 * c + 0.447 * pow(c,2) + 0.0505 * pow(c,3); }

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

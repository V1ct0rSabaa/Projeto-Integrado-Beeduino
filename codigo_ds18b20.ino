// Código com led RGB, LCD 16 x 2 e sensor de temperatura DS18B20 waterproof
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h> 

const int CABO_TEMPERATURA = 2; // O fio de dados é conectado no pino digital 2 no Arduino
LiquidCrystal display(13, 12, 11, 10, 9, 8);

OneWire oneWire(CABO_TEMPERATURA);  // Prepara uma instância oneWire para comunicar com qualquer outro dispositivo oneWire

DallasTemperature sensors(&oneWire); // Passa uma referência oneWire para a biblioteca DallasTemperature

//int infravermelho = 6; // pino do sensor infravermelho

int azul = 3; // pinos do led rgb
int verde = 4;
int vermelho = 5;

void get_vermelho(){
  analogWrite(azul, 0);
  analogWrite(verde, 0);
  analogWrite(vermelho, 255);
}

void get_verde(){
  analogWrite(verde, 255);
  analogWrite(azul, 0);
  analogWrite(vermelho, 0);
}

void get_azul(){
  analogWrite(verde, 0);
  analogWrite(azul, 255);
  analogWrite(vermelho, 0);
}
// parte do sensor infravermelho
/*
void get_infravermelho(){
  if(digitalRead(infravermelho) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW
    display.setCursor(0, 1); 
    display.clear();
    display.print("Abelha passou pelo");
  }
}*/

void setup(void)
{
  sensors.begin();  // Inicia a biblioteca
  display.begin(16, 2);
  //pinMode(infravermelho, INPUT_PULLUP); // pino do input do sensor infravermelho
  Serial.begin(9600);
}

void loop(void)
{ 
  sensors.requestTemperatures(); // Manda comando para ler temperaturas
  float temperatura = sensors.getTempCByIndex(0);
  float temperatura_minima = 22.00;
  float temperatura_maxima = 30.00;
  //parte do LCD
  display.clear();
  display.setCursor(0, 0);
  display.print("temp: ");
  display.print(temperatura);
  display.print("C ");
  if (temperatura >= temperatura_maxima){
    display.setCursor(0, 1); 
    display.print("Muito quente!");
    get_vermelho();
  }
  else if (temperatura <= temperatura_minima){
    display.setCursor(0, 1); 
    display.print("Muito frio!");
    get_azul();
  }
  else{
    display.setCursor(0, 1); 
    display.print("Temp agradavel");
    get_verde();
  }
  delay(1000 * 0.2);
}




// Código com led RGB, LCD 16 x 2 e sensor de temperatura DHT11
#include <LiquidCrystal.h>  // biblioteca do lcd 16x2
#include <DHT.h> // Inclui a biblioteca do DHT 

LiquidCrystal display(13, 12, 11, 10, 9, 8);

const int PINO_DHT = 2;// Pino digital 2 conectado ao DHT11
#define DHTTYPE DHT11// DHT 11

DHT dht(PINO_DHT, DHTTYPE); // Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (PINO_DHT) e o tipo do sensor (DHTTYPE)

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

void setup(void)
{
  display.begin(16, 2);
  dht.begin(); // Inicializa o sensor DHT11
  Serial.begin(9600);
}

void loop(void)
{
  // definindo valores de temperatura e umidade
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  float temperatura_minima = 22.00;
  float temperatura_maxima = 30.00;
  
  if (isnan(umidade) || isnan(temperatura)) { //Verifica se a umidade ou temperatura são ou não um número
    //se umidade e/ou temperatura não tiverem recebido um valor numerico, reinicia a função loop
    return; //Caso não seja um número retorna
  }
  //parte do LCD
  display.clear(); //limpando tela
  //mostrar temperatura
  display.setCursor(0, 0);
  display.print("temp: ");
  display.print(temperatura);
  display.print("C ");
  // mostrar umidade
  display.setCursor(0, 1);
  display.print("Umid: ");
  display.print(umidade);
  display.print("%");
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
    get_verde();
    display.setCursor(0, 1); 
    display.print("Umid: ");
    display.print(umidade);
    display.print("%");
  }
  delay(1000 * 0.2);
}

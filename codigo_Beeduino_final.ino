#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 12 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void funcaoMonitorar();
void monitorarTemperatura(float valorTemp);
void monitorarUmidade(float valorUmid);
void printValores(float valorTemp, float valorUmid);

void funcaoConfigurar();
void configurarTemperatura();

void botaoDirecional();
float botaoMaisMenos(float dados);

//portas digitais
int dadosSensores[200];
int botaoMais = 8;
int botaoMenos = 9;
int botaoSelect = 10;
int botaoVoltar = 11;
int ledVermelho = 14;
int ledVerde = 15;
int ledAzul = 16;
int buzzer = 17;

//definicao objeto lcd
LiquidCrystal lcd(2,3,4,5,6,7);

//declaração de variaveis
float temperaturaMinima = 0.0;
float temperaturaMaxima = 0.0;
float umidadeMinima = 0.0;
float umidadeMaxima = 0.0;
int cursorColuna = 0;
int cursorLinha = 0;
float leituraTemperatura = 0.0;
float leituraUmidade = 0.0;

//define o elemento cursor
byte cursor[8] = {
      B00000,
      B00000,
      B00110,
      B11111,
      B00110,
      B00000,
      B00000,
};
    
void setup()
{
  //Objeto lcd
  lcd.createChar(0, cursor);
  lcd.begin(16,2);
    
  //leds e buzzer
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(buzzer, OUTPUT);

  //botoes
  pinMode(botaoMais, INPUT);
  pinMode(botaoMenos, INPUT);
  pinMode(botaoSelect, INPUT);
  pinMode(botaoVoltar, INPUT);
        
  //inicia a entrada serial
  Serial.begin(9600);

  //inicia o sensor DHT11
  dht.begin();
    
}

void loop(){
  lcd.setCursor(cursorColuna,cursorLinha);
  lcd.write(byte());
  lcd.setCursor(1,0);
  lcd.print("Configurar");
  lcd.setCursor(1,1);
  lcd.print("Monitorar");
  botaoDirecional();

  if( cursorLinha == 0 && digitalRead(botaoSelect) == HIGH ){
        funcaoConfigurar(); 
  }//fim do if
  
  if( cursorLinha == 1 && digitalRead(botaoSelect) == HIGH ){
        funcaoMonitorar();  
  }//fim do if

  int t = dht.readTemperature();
  int h = dht.readHumidity();
  
}//fim do loop

void funcaoMonitorar(){
    while ( digitalRead(botaoVoltar) == LOW ){
        lcd.clear();
        monitorarTemperatura(dht.readTemperature());
        monitorarUmidade(dht.readHumidity());
      printValores(leituraTemperatura, leituraUmidade);
        delay(2000);
    }//fim do while
    lcd.clear();
    digitalWrite( ledVermelho, LOW);
    digitalWrite( ledVerde, LOW);
    digitalWrite( ledAzul, LOW);
    digitalWrite( buzzer, LOW);
}//fim da funcao

void monitorarTemperatura(float valorSensorTemperatura ){
  
  //formula para conversao
  leituraTemperatura = valorSensorTemperatura;
  
  //baixa temperatura: azul
  if ( leituraTemperatura < temperaturaMinima ){
    digitalWrite( ledAzul, HIGH);
    digitalWrite( ledVerde, LOW);
    digitalWrite( ledVermelho, LOW);
    digitalWrite( buzzer, HIGH);
  }
  
  //temperatura adequada: verde
  if ( leituraTemperatura >= temperaturaMinima && leituraTemperatura <= temperaturaMaxima ){
    digitalWrite( ledAzul, LOW);
    digitalWrite( ledVerde, HIGH);
    digitalWrite( ledVermelho, LOW);
  }
  
  //temperatura perigosa: vermelha
  if ( leituraTemperatura > temperaturaMaxima ){
    digitalWrite( ledAzul, LOW);
    digitalWrite( ledVerde, LOW);
    digitalWrite( ledVermelho, HIGH);
    digitalWrite( buzzer, HIGH);
  }

}//fim da fucao

void monitorarUmidade(float valorSensorUmidade){
  
  //formula para conversao
  leituraUmidade = valorSensorUmidade;
  
 
}//fim da funcao

//falta acrescentar o parametro de umidade
void printValores(float valorTemp, float valorUmid ){
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(valorTemp);
  
  lcd.setCursor(0,1);
  lcd.print("U:");
  lcd.print(valorUmid);
   
}//fim da funcao

void funcaoConfigurar(){
    lcd.clear();
    while( digitalRead( botaoVoltar ) == LOW ){
        lcd.setCursor(cursorColuna,cursorLinha);
        lcd.write(byte());
        lcd.setCursor(1,0);
        lcd.print("Conf Temper");
        //lcd.setCursor(1,1);
        //lcd.print("Conf Umidade");
        botaoDirecional();
             
            if( cursorLinha == 0 && digitalRead(botaoSelect) == HIGH ){
                configurarTemperatura();  
            }//fim do if
  
            if( cursorLinha == 1 && digitalRead(botaoSelect) == HIGH ){
                //configurarUmidade();  
            }//fim do if

    }//fim do while
    lcd.clear();
}//fim da fucao

void configurarTemperatura(){
    lcd.clear();
    while( digitalRead( botaoVoltar ) == LOW ){
        lcd.setCursor(cursorColuna,cursorLinha);
        lcd.write(byte());
        lcd.setCursor(1,0);
        lcd.print("Temper Minima");
        lcd.setCursor(1,1);
        lcd.print("Temper Maxima");
        botaoDirecional();
             
            if( cursorLinha == 0 && digitalRead(botaoSelect) == HIGH ){
                lcd.clear();
                lcd.print("Temp Minima:");
                while( digitalRead(botaoSelect) == LOW && digitalRead(botaoVoltar) == LOW ){
                    lcd.setCursor(0,1);
                    lcd.print(temperaturaMinima);
                    temperaturaMinima = botaoMaisMenos(temperaturaMinima);
                }//fim do while
                lcd.clear();
            }//fim fo if

            if( cursorLinha == 1 && digitalRead(botaoSelect) == HIGH ){
                lcd.clear();
                lcd.print("Temp Maxima:");
                while( digitalRead(botaoSelect) == LOW && digitalRead(botaoVoltar) == LOW ){
                    lcd.setCursor(0,1);
                    lcd.print(temperaturaMaxima);
                    temperaturaMaxima = botaoMaisMenos(temperaturaMaxima);
                }//fim do while
                lcd.clear();
            }//fim fo if
    }//fim do while
    lcd.clear();
}//fim da funcao

void botaoDirecional(){
  
  if( digitalRead(botaoMais) == HIGH ){
        if ( cursorLinha == 1 ){
          cursorLinha = 0;
            lcd.clear();
        }//fim do 2 if
    }//fim do 1 if
  
  if( digitalRead(botaoMenos) == HIGH ){
        if ( cursorLinha == 0 ){
          cursorLinha = 1;
            lcd.clear();
        }//fim do 2 if
    }//fim do 1 if
  
}//fim da funcao

float botaoMaisMenos(float valor ){
    float resultado = valor;
    
    if( digitalRead(botaoMais) == HIGH ){
      delay(100); 
      resultado+=1;
    }

    if( digitalRead(botaoMenos) == HIGH ){
      delay(100);  
      resultado-=1;
    }
    return resultado;
}//fim da funcao

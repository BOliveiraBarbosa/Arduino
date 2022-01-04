/* Controle de nível de água
Alimentado por energia solar */

/* Bibliotecas */
#include <LiquidCrystal_I2C.h>

/* Instanciamento de Objetos */
LiquidCrystal_I2C LCD(0x27, 16, 2);

/* Definição dos Pinos */
#define pinBoiaInferior 0
#define pinBoiaSuperior 1
#define pinReservatorio 2
#define pinBombaRele 7
#define pinBuzzer 4
#define LedBoiaInf 10
#define LedBoiaSup 11
#define LedReservatorio 12

/* Variaveis Globais */
int AuxBoiaInferior, AuxBoiaSuperior;
int AuxBomba, AuxReservatorio;

/* Declaraçao de Funções */
void Som();

void setup()
{
  /*Define os modos dos Pinos */
  pinMode(pinBoiaInferior, INPUT);
  pinMode(pinBoiaSuperior,INPUT);
  pinMode(pinReservatorio,INPUT);
  pinMode(pinBombaRele,OUTPUT);
  pinMode(pinBuzzer,OUTPUT);
  pinMode(LedBoiaInf,OUTPUT);
  pinMode(LedBoiaSup,OUTPUT);
  pinMode(LedReservatorio,OUTPUT);

  /* Iniciando o Display LCD */
  LCD.init();
}

void loop()
{
  /* Lê o valor dos pinos */
  AuxBoiaInferior = digitalRead(pinBoiaInferior);
  AuxBoiaSuperior = digitalRead(pinBoiaSuperior);
  AuxReservatorio = digitalRead(pinReservatorio);
  AuxBomba = digitalRead(pinBombaRele);
  

  /* Liga e Desliga Led´s */
  digitalWrite(LedBoiaInf,AuxBoiaInferior);
  digitalWrite(LedBoiaSup,AuxBoiaSuperior);
  digitalWrite(LedReservatorio,AuxReservatorio);
  
  /* Verifica se tem água no reservatório */
  if(AuxReservatorio == 1)
  {
    /* Verificação do nível da água */

    /* Nível Alto */
    if((AuxBoiaSuperior == 1) && (AuxBoiaInferior == 1))
    {
      /* Comando Display LCD */
      LCD.clear();
      LCD.print(" reservatorio ");
      LCD.setCursor(0,1);
      LCD.print(" Nivel Alto ");

      /* Desligando da Bomba */
      if(AuxBomba == 1)
      {
        LCD.clear();
        LCD. print(" Desligando ");
        LCD.setCursor(0,1);
        LCD.print(" a Bomba! ");
        
        digitalWrite(pinBombaRele, LOW);
      }
    }

    /* Nível Médio */
    else if((AuxBoiaSuperior == 0) && (AuxBoiaInferior == 1))
    {
      LCD.clear();
      LCD.print(" reservatorio ");
      LCD.setCursor(0,1);
      LCD.print(" Nivel Medio ");
    }

    /* Nível Baixo */
    else if((AuxBoiaSuperior == 0) && (AuxBoiaInferior == 0))
    {
      LCD.clear();
      LCD.print(" reservatorio ");
      LCD.setCursor(0,1);
      LCD.print(" Nivel Baixo! ");
      
      /* Ligando a Bomba */
      if(AuxBomba == 0)
      {
        LCD.clear();
        LCD. print(" Ligando ");
        LCD.setCursor(0,1);
        LCD.print(" a Bomba! ");
        
        digitalWrite(pinBombaRele, HIGH);
      }
      
      /* Chama a função Som */
      Som();
    }
  }
  else if(AuxReservatorio == 0)
  {
    LCD.clear();
    LCD.print(" Nao tem agua ");
    LCD.setCursor(0,1);
    LCD.print(" Para o Funcionamento");
    
    digitalWrite(pinBombaRele, LOW);
  }
  delay(1000);
}

void Som()
{
  for(int j = 0; j < 3; j += 1)
  {
    /* Alarme de ponto crítico */
    digitalWrite(pinBuzzer,HIGH);
    delay(1000);
    digitalWrite(pinBuzzer,LOW);
  }
}

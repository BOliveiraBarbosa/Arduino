/* Seguidor Solar com Led */

/*Inclusão das bibliotecas */
#include <Servo.h>

/* Definição dos pinos */
#define pinServoVet 9
#define pinServoHor 10

#define pinPoste 8
#define pinControManual 2

#define pinLdrSE A0 //S = Superior
#define pinLdrIE A1 //I = Inferior
#define pinLdrSD A2 //E = Esquerda
#define pinLdrID A3 //D = Direita

/* Definição das Variaveis Globais dos Servos */
Servo servoHor;
Servo servoVer;

int anguloVer = 90; // Começa em 90°
int anguloHor = 90; // Começa em 90°

/* Cabeçalho de funções */
void seguidorSolar();
void ligaPoste();

void setup()
{
  /* Define o Estado do pino como Entrada ou Saida */
  pinMode(pinLdrSE, INPUT);
  pinMode(pinLdrIE, INPUT);
  pinMode(pinLdrSD, INPUT);
  pinMode(pinLdrID, INPUT);

  pinMode(pinControManual, INPUT_PULLUP);
  pinMode(pinPoste, OUTPUT);
  
  /* Anexa as variaveis aos pinos */
  servoHor.attach(pinServoHor);
  servoVer.attach(pinServoVet);

  /* Posição inicial dos Servos */
  servoHor.write(anguloHor);
  servoVer.write(anguloVer);
  
  Serial.begin(9600);
}

void loop()
{
  /* Chama as Funções */
  ligaPoste();
  seguidorSolar();
  
  Serial.print(anguloHor);
  Serial.print("  ");
  Serial.print(anguloVer);
  Serial.print("  ");
  Serial.print(analogRead(pinLdrSE));
  Serial.print("  ");
  Serial.print(analogRead(pinLdrIE));
  Serial.print("  ");
  Serial.print(analogRead(pinLdrSD));
  Serial.print("  ");
  Serial.println(analogRead(pinLdrID));
  
  delay(20);
}

/* Analisa e Liga o Poste */
void ligaPoste(){
  /* Analisa o sensor Modulo Ldr está recebendo luz*/
  if(analogRead(pinLdrSE) < 200) {  
    digitalWrite(pinPoste, HIGH); //Sim
  } else {
    digitalWrite(pinPoste, LOW); // Não
  }
}

void seguidorSolar()
{
  /* Definição das Variaveis e atribuição da escrita da incidência de luz */
  int luzD = analogRead(pinLdrSD) + analogRead(pinLdrID); // vindo da Direita
  int luzE = analogRead(pinLdrSE) + analogRead(pinLdrIE); // vindo da Esquerda
  int luzC = analogRead(pinLdrSD) + analogRead(pinLdrSE); // vindo de Cima
  int luzB = analogRead(pinLdrID) + analogRead(pinLdrIE); // vindo de Baixo
  
  /* Comparação se a luz tem mais incidência na Esquerda */
  if(luzE > luzD) {
    if(anguloHor < 180){
        /* O angulo muda pra Esquerda */
      anguloHor += 1;
    }   
  } else if(luzD > luzE){
    if(anguloHor > 0){
        /* O angulo muda pra Esquerda */
      anguloHor -= 1;
    }
  }
  
  /* Comparação se a luz tem mais incidência em cima */
  if(luzC > luzB) {
    if(anguloVer < 180){
        /* O angulo muda pra Cima */
        anguloVer += 1;
    } 
  } else if(luzB > luzC){
    if(anguloVer > 0){
        /* O angulo muda pra Baixo */
        anguloVer -= 1;
    }
  }

  /* A placa muda por lado do angulo */
  servoHor.write(anguloHor);
  servoVer.write(anguloVer);
  
}

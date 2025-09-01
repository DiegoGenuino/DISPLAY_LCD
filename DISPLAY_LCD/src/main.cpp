//--------------------------------INTERNET DAS COISAS - PROFº LUCAS FELFOLDI------------------------------------
/*
AUTOR       : DIEGO GENUINO DE OLIVEIRA
TURMA       :
AULA        : 6
PROJETO     : Código Base com função float_map
VERSÃO      : 1.0
DATA        :
COMENTARIOS : Este projeto visa escrever comentarios no display lcd
*/
//_____________________________________________________________________________________________________________

// INCLUI BIBLIOTECAS------------------------------------------------------------------------------------------
#include <Arduino.h>      // Inclui bibliotecas de compatibilidade de funções do Arduino
#include <esp_task_wdt.h> // Biblioteca que permite manipular o watchdog no segundo núcleo
#include <LiquidCrystal_I2C.h>
TaskHandle_t Task1; // Declara tarefa que será executada no segundo núcleo (dual core)
//_____________________________________________________________________________________________________________

// DEFINE PINOS DO HARDWARE------------------------------------------------------------------------------------
// Saidas Digitais (LEDs)
#define LED_1 19
#define LED_2 18
#define LED_3 5
#define LED_4 4
#define LED_5 2

// Entradas Digitais (Botões)
#define BT_1 35
#define BT_2 32
#define BT_3 27
#define BT_4 25
#define BT_5 26

// Entradas Analógicas (Sensores)
#define POT 33
#define LDR 34

// Outras Definções de Hardware

//_____________________________________________________________________________________________________________
// DECLARA VARIÁVEIS E CONSTANTES GLOBAIS ----------------------------------------------------------------------

int contador = 0;
unsigned long tempo_atual = 0;
unsigned long tempo_decorrido = 0;

//_____________________________________________________________________________________________________________

// INICIALIZA OBJETOS ----------------------------------------------------------------------------------------

LiquidCrystal_I2C Lcd(0x27, 16, 2);

//_____________________________________________________________________________________________________________

// DECLARA FUNÇÕES -------------------------------------------------------------------------------------------
float float_map(float x, float in_min, float in_max, float out_min, float out_max);
void loop_2();
void Task1code(void *pvParameters);

void tela_1();
void tela_2();
void tela_3();

//_____________________________________________________________________________________________________________

// CONFIGURAÇÃO DO SISTEMA -------------------------------------------------------------------------------------
void setup()

{
  Serial.begin(9600); // Inicia comunicação Serial USB a 9600 bits por segundo (bps)

  // Inicia comuniçaão com o display lcd i2c
  Lcd.init();
  Lcd.backlight();
  Lcd.clear();

  // Configura LEDS como saídas (OUTPUT)
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);

  // Configura BOTÕES como entradas (INPUT)
  pinMode(BT_1, INPUT);
  pinMode(BT_2, INPUT);
  pinMode(BT_3, INPUT);
  pinMode(BT_4, INPUT);
  pinMode(BT_5, INPUT);

  // xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 0, &Task1, 0);

  xTaskCreatePinnedToCore(
      Task1code, // 1. A função que contém o código da tarefa
      "Task1",   // 2. Um nome descritivo para a tarefa
      10000,     // 3. O tamanho da memória "stack" para a tarefa
      NULL,      // 4. Parâmetros a serem passados para a tarefa (nenhum neste caso)
      0,         // 5. A prioridade da tarefa
      &Task1,    // 6. Um "handle" para controlar a tarefa depois
      0          // 7. O núcleo (core) da CPU onde a tarefa deve rodar
  );
}

//_____________________________________________________________________________________________________________

// LAÇO PRINCIPAL ----------------------------------------------------------------------------------------------

void loop()
{
  // TAREFAS RÁPIDAS

  // ENTRADA DE DADOS

  // PROCESSAMENTO DE DADOS

  // SAIDA DE DADOS

tempo_atual = millis();

if(tempo_atual - tempo_decorrido > 2000){
  contador ++;
  Lcd.clear();
  tempo_decorrido = tempo_atual;
}

  if (contador >= 3)
  {
    contador = 0;
  }

  switch (contador)
  {
  case 0:
    tela_1();
    break;

    case 1:
    tela_2();
    break;

    case 2:
    tela_3();
    break;

  default:
  tela_1();
  }


}

//_____________________________________________________________________________________________________________

// LAÇO SECUNDARIO ----------------------------------------------------------------------------------------------

void loop_2()
{
  // TAREFAS LENTAS, COMO COMUNICAÇÕES COM OUTROS DISPOSITIVOS

  digitalWrite(LED_2, HIGH);
  delay(500);
  digitalWrite(LED_2, LOW);
  delay(500);
}

//_____________________________________________________________________________________________________________

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// NÃO ALTERAR ESSA FUNÇÃO!
void Task1code(void *pvParameters)
{
  esp_task_wdt_init(3000, false);
  while (1)
  {
    loop_2();
  }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

float float_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  // Função que realiza proporções/ regra de três com variaveis REAIS
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void tela_1()
{
  Lcd.setCursor(0, 0);
  Lcd.print("    Nome   ");
  Lcd.setCursor(0, 1);
  Lcd.print("  Diego Genuino ");
}

void tela_2()
{
  Lcd.setCursor(0, 0);
  Lcd.print(" LUMINOSIDADE ");
  Lcd.setCursor(0, 1);
  float valorLDR = analogRead(LDR);
  Lcd.print(valorLDR);
}

void tela_3()
{
  Lcd.setCursor(0, 0);
  Lcd.print(" IOT KIT 2025 ");
}
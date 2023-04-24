/*
   Autor: Pablo T. Monteiro
   Versão 6
   CACULADORA CIENTIFICA RPN COMPLEXA
*/

#include <LiquidCrystal.h>
#include <math.h>
#include <string.h>

#define MAX_BUFFER_SIZE 20
#define  col_0   9                   //coluna 1 controlada pelo pino digital 09 (será usado como digital)
#define  col_1   10                   //coluna 2 controlada pelo pino digital 10 (será usado como digital)
#define  col_2   11                   //coluna 3 controlada pelo pino digital 11 (será usado como digital)
#define  col_3   12                   //coluna 4 controlada pelo pino digital 12 (será usado como digital)
#define  col_4   13                   //coluna 5 controlada pelo pino digital 13 (será usado como digital)
#define  row_A   5//0                    //linha A  controlada pelo pino digital 10
#define  row_B   6//2                    //linha B  controlada pelo pino digital 11
#define  row_C   7//3                    //linha C  controlada pelo pino digital 12
#define  row_D   8//4                    //linha D  controlada pelo pino digital 13

LiquidCrystal lcd(A5, A4, A3, A2, A1, A0); //lcd(A5, /*13,*/ A4, /*8, 7, 6, 5,*/ A3, A2, A1, A0);

//---------------------------------------------------Rotina TIMER----------------------
unsigned char counter = 0x00, control = 0x01;
ISR(TIMER2_OVF_vect) {
  TCNT2 = 255;
  counter++;
  if (counter == 0xFF) {
    counter = 0x00;
    if (!digitalRead(col_0) & control == 0x01) {
      control = 0x02;
      digitalWrite(col_1, LOW);
      digitalWrite(col_2, LOW);
      digitalWrite(col_3, LOW);
      digitalWrite(col_4, LOW);
      digitalWrite(col_0, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x41); //1,8 'A'
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x46); //1,7 'F'
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D)) keyboard(0x4B); //1,6 'K'
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D)) keyboard(0x50); //1,5 'P'
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D)) keyboard(0x61); //1,4 'a'
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x62); //1,3 'b'
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x63); //1,2 'c'
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x64); //1,1 'd'
    } else if (!digitalRead(col_1) & control == 0x02) {
      control = 0x03;
      digitalWrite(col_0, LOW);
      digitalWrite(col_2, LOW);
      digitalWrite(col_3, LOW);
      digitalWrite(col_4, LOW);
      digitalWrite(col_1, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x42); //2,8
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x47); //2,7
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0x4C); //2,6
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x51); //2,5
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x37); //1,4
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x34); //2,3
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x31); //2,2
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x30); //2,1
    } else if (!digitalRead(col_2) & control == 0x03) {
      control = 0x04;
      digitalWrite(col_0, LOW);
      digitalWrite(col_1, LOW);
      digitalWrite(col_3, LOW);
      digitalWrite(col_4, LOW);
      digitalWrite(col_2, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x43); //3,8
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x48); //3,7
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0x4D); //3,6
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x52); //3,5
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x38); //1,4
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x35); //3,3
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x32); //3,2
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x2E); //3,1
    } else if (!digitalRead(col_3) & control == 0x04) {
      control = 0x05;
      digitalWrite(col_0, LOW);
      digitalWrite(col_1, LOW);
      digitalWrite(col_2, LOW);
      digitalWrite(col_4, LOW);
      digitalWrite(col_3, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x44); //4,8
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x49); //4,7
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0x4E); //4,6
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x53); //4,5
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x39); //1,4
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x36); //4,3
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x33); //4,2
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x65); //4,1
    } else if (!digitalRead(col_4) & control == 0x05) {
      control = 0x01;
      digitalWrite(col_0, LOW);
      digitalWrite(col_1, LOW);
      digitalWrite(col_2, LOW);
      digitalWrite(col_3, LOW);
      digitalWrite(col_4, HIGH);
      delay(10);
      if (!digitalRead(row_A)&digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x45); //5,8
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x4A); //5,7
      else if (!digitalRead(row_A) & !digitalRead(row_B)&digitalRead(row_C)&digitalRead(row_D))  keyboard(0x4F); //5,6
      else if (!digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x54); //5,5
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C)&digitalRead(row_D))  keyboard(0x2F); //1,4
      else if (digitalRead(row_A) & !digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D)) keyboard(0x2A); //5,3
      else if (digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x2D); //5,2
      else if (!digitalRead(row_A)&digitalRead(row_B) & !digitalRead(row_C) & !digitalRead(row_D))  keyboard(0x2B); //5,1
    }
  }
}
//-----------------------------------------------Fim Rotina TIMER----------------------

void setup() {
  //lcd.display();
  lcd.begin(16, 2/*, LCD_5x8DOTS8*/);
  lcd.noAutoscroll();
  lcd.setCursor(0, 0);
  lcd.cursor();
  lcd.blink();
  lcd.print("PocketRPN v6");
  pinMode(col_0, OUTPUT);
  pinMode(col_1, OUTPUT);
  pinMode(col_2, OUTPUT);
  pinMode(col_3, OUTPUT);
  pinMode(col_4, OUTPUT);
  pinMode(row_A,  INPUT);
  pinMode(row_B,  INPUT);
  pinMode(row_C,  INPUT);
  pinMode(row_D,  INPUT);
  //inicializar tudo em LOW
  digitalWrite(col_0, LOW);
  digitalWrite(col_1, LOW);
  digitalWrite(col_2, LOW);
  digitalWrite(col_3, LOW);
  digitalWrite(col_4, LOW);
  digitalWrite(row_A, LOW);
  digitalWrite(row_B, LOW);
  digitalWrite(row_C, LOW);
  digitalWrite(row_D, LOW);
  delay(100);
  //lcd.clear();
  //-----------------------------------------SET DO TIMER2 E INTERRUPCAO----------------------------------------
  TCCR2A = 0x00;   //Timer operando em modo normal
  TCCR2B = 0x07;   //Prescaler 1:1024
  TCNT2  = 255;    //10 ms overflow again
  TIMSK2 = 0x01;   //Habilita interrupção do Timer2
  //----------------------------------------------------------------------------------
}

typedef struct{
  double Re = 0;
  double Im = 0;
  unsigned char rep = 0x00;
  // 00 = real
  // 01 = rect
  // 02 = polar rad
  // 03 = polar deg
}cmp;

char keyBufReal[MAX_BUFFER_SIZE + 1];
char keyBufComplexo[MAX_BUFFER_SIZE + 1];
int bufReal_size;
int bufComplexo_size;
bool SHIFT, type_flag;
cmp float_buf, Num[10];

unsigned char ang = 0x00;
// 00 = rad
// 01 = deg
// 02 = grad
unsigned char rep = 0x00;
// 00 = fix
// 01 = sci
// 02 = eng

void keyboard(char c) {
  char i;                                //variável de iterações
  TIMSK2 = 0x00;                         //Desabilita interrupçãodo Timer2
  //--------------------------------------------------------------

  //--------------------------------------------------------------
  while (digitalRead(row_A) | digitalRead(row_B) | digitalRead(row_C) | digitalRead(row_D)) { //----------------------------------------impede o efeito boucing
  }
  TIMSK2 = 0x01;   //Habilita interrupção do Timer2
}

void loop() {
  
}

void type_number(char c){
  if(float_buffer.rep == 0x00){
    if((c > 0x2F && c < 0x3A) || c == 0x2E || c == 0x53 || c == 0x52){
      if(bufferReal_size < MAX_BUFFER_SIZE){
        keybufferReal[bufferReal_size] = c;
        bufferReal_size++;
      }
      keybufferReal[bufferReal_size + 1] = '\0';
    }else if (c == 0x54 && bufferReal_size > 0){
      if(SHIFT){
        clear_key();
      }else{
        bufferReal_size--;
        keybufferReal[bufferReal_size] = 0x00;
      }
    }
    float_buffer.Re = double(atof(keybufferReal));
  }else{
    if((c > 0x2F && c < 0x3A) || c == 0x2E || c == 0x53 || c == 0x52){
      if(bufferComplexo_size < MAX_BUFFER_SIZE){
        keybufferComplexo[bufferComplexo_size] = c;
        bufferComplexo_size++;
      }
      keybufferComplexo[bufferComplexo_size + 1] = '\0';
    }else if(c == 0x54){
        if(SHIFT){
          clear_key();
        }else{
          if(bufferComplexo_size == 0){
            float_buffer.rep = 0x00;
          }else{
            bufferComplexo_size--;
            keybufferComplexo[bufferComplexo_size] = 0x00;
          }
        }
      }
      float_buffer.Im = double(atof(keybufferComplexo));
    }
 if(c == 0x65){
    if(SHIFT){
      float_buffer.rep = 0x02;
    }else{
      float_buffer.rep = 0x01;
    }
  }
}

void operate_number(char c) {
  if(Num[0].rep==0x02){ // Se polar, converte para cartesiano
    Num[0].Im = Num[0].Im * cos(Num[0].Im); // parte Im
    Num[0].Re = Num[0].Re * sin(Num[0].Re); // parte Re
  }if(Num[1].rep==0x02){ // Se polar, converte para cartesiano
    Num[1].Im = Num[1].Im * cos(Num[1].Im); // parte Im
    Num[1].Re = Num[1].Re * sin(Num[1].Re); // parte Re
  }
  type_flag = true;
  //double A = Num[0];
  //Num[0] = Num[1]; //y^x
  //Num[1] = A;
  if (c == 0x2D) { // char '-' to do: minus
    Num[1].Re  =  Num[1].Re  -  Num[0].Re;
    Num[1].Im  =  Num[1].Im  -  Num[0].Im;
  } else if (c == 0x2B) { // char '+' to do: plus
    Num[1].Re  =  Num[1].Re  +  Num[0].Re;
    Num[1].Im  =  Num[1].Im  +  Num[0].Im;
  } else if (c == 0x2A) { // char '*' to do: mult
    Num[1].Re  =  Num[1].Re * Num[0].Re + ( -1 * Num[0].Im * Num[1].Im);
    Num[1].Im  =  Num[0].Re * Num[1].Im + Num[1].Re * Num[0].Im;
  } else if (c == 0x2F) { // char '/' to do: div
    double Re  =  Num[1].Re * Num[0].Re + ( -1 * Num[1].Im * Num[0].Im);
    double Im  =  Num[1].Re * (-1 * Num[0].Im ) + Num[0].Re + Num[1].Im;
    Num[1].Re = Re / pow(Num[0].Re, 2);
    Num[1].Im = Im / pow(Num[0].Im, 2);
  } else if (c == 0x45){
    double r = sqrt(Num[1].Re * Num[1].Re + Num[1].Im * Num[1].Im);
    double theta = atan2(Num[1].Im, Num[1].Re);
    double x = pow(r, Num[0].Re) * exp(-Num[0].Im * theta);
    double y = Num[0].Re * theta + 0.5 * Num[0].Im * log(r * r);
    Num[1].Re = x * cos(y);
    Num[1].Im = x * sin(y);
  } else if (c == 0x44){
    if(Num[0].rep == 0x00){
      if(SHIFT){
        Num[0].Re = pow(Num[0].Re, 2);
      }else{
        Num[0].Re = sqrt(Num[0].Re);
      }
      
    }else{
      if(SHIFT){
        double a = Num[0].Re;
        double b = Num[0].Im;
        Num[0].Re = pow(a, 2) - pow(b, 2);
        Num[0].Im = 2 * a * b;
      }else{
        double r = sqrt(Num[0].Re*Num[0].Re + Num[0].Im*Num[0].Im);
        double theta = atan2(Num[0].Im, Num[0].Re);
        double a = sqrt(r) * cos(theta/2);
        double b = sqrt(r) * sin(theta/2);
        Num[0].Re = a;
        Num[0].Im = b;
      }
    }
    return;
  }else if (c == 0x51){
    if(SHIFT){
    }else{
      double b = Num[0].Re;
      Num[0].Re = Num[1].Re;
      Num[1].Re = b;
      b = Num[0].Im;
      Num[0].Im = Num[1].Im;
      Num[1].Im = b;
      char a = Num[0].rep;
      Num[0].rep = Num[1].rep;
      Num[1].rep = a;
      type_flag = false;
    }
    return;
  }else if (c == 0x42) {
    if(SHIFT){
      Num[0].Re = pow(10,Num[0].Re);
    }else{
      Num[0].Re = exp(Num[0].Re);
      Num[0].Im = exp(Num[0].Im);
    }
    return;
  } else if (c == 0x43) {
    if(SHIFT){
      //função fatorial
    }else{
      double a = Num[0].Re;
      double b = Num[0].Im;
      Num[0].Re = a / (a*a + b*b);
      Num[0].Im = (-1 * b) / (a*a + b*b);
    }
    return;
  }else if (c == 0x4D || c == 0x4E || c == 0x4F){
    if(mode==0x01){
      Num[0].Re = (Num[0].Re*PI)/180;
    }else if(mode==0x02){
      Num[0].Re = (Num[0].Re*PI)/200;
    }
    if(c == 0x4D){
      if(SHIFT){
        Num[0].Re = asin(Num[0].Re);
      }else{
        Num[0].Re = sin(Num[0].Re);
      }
    }else if(c == 0x4E){
      if(SHIFT){
        Num[0].Re = acos(Num[0].Re);
      }else{
        Num[0].Re = cos(Num[0].Re);
      }
    }else{
      if(SHIFT){
        Num[0].Re = atan(Num[0].Re);
      }else{
        Num[0].Re = tan(Num[0].Re);
      }
    }
  }else if(c == 0x49){
    if(SHIFT){
      Num[0].Re = PI;
    }else{
      Num[0].Re = log10(Num[0].Re);
    }
  }else if(c == 0x4A){
    if(SHIFT){
      Num[0].Re = M_E;
    }else{
      Num[0].Re = log(Num[0].Re);
    }
  }else if(c == 0x4C){
    type_flag = false;
    if(SHIFT){
      rollthrough();
    }else{
      rollback();
    }
    return;
  }
  rollback();
  Num[19].Re = 0;
}

void clear_key() {
  bufferReal_size = 0;
  bufferComplexo_size = 0;
  for (int i = 0; i < MAX_BUFFER_SIZE; i++) {
    keybufferReal[i] = 0x00;
    keybufferComplexo[i] = 0x00;
  }
}
void store_number() {
  clear_key();
  rollthrough();
  Num[0].Re = Num[1].Re;
}
void rollthrough(){
  double temporarioRe = Num[19].Re;
  double temporarioIm = Num[19].Im;
  double temporariorep = Num[19].rep;
  for(int j=19; j>0; j--){
    Num[j].Re = Num[j-1].Re;
    Num[j].Im = Num[j-1].Im;
    Num[j].rep = Num[j-1].rep;
  }
  Num[0].Re = temporarioRe;
  Num[0].Im = temporarioIm;
  Num[0].rep = temporariorep;
}

void rollback(){
  double temporarioRe = Num[19].Re;
  double temporarioIm = Num[19].Im;
  double temporariorep = Num[19].rep;
  for(int j=0; j<19; j++){
    Num[j].Re = Num[j+1].Re;
    Num[j].Im = Num[j+1].Im;
    Num[j].rep = Num[j+1].rep;
  }
  Num[19].Re = temporarioRe;
  Num[19].Im = temporarioIm;
  Num[19].rep = temporariorep;
}

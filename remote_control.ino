#include <IRremote.h>
#include <LiquidCrystal.h>

const int RECV_PIN = 7;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
#define Maximum_value 10
int value[Maximum_value] = {0,0,0,0,0,0,0,0,0,0,};
int value_change = 0;
char mode_serect = 'n';
    
int carry(int number){
  int carry_number = number * 10;
  return(carry_number);
}

void screen_display(int number){
  lcd.print(number);
}

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  irrecv.blink13(true);
  lcd.begin(16, 2);
}

void loop(){

  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
        results.value = key_value;
        lcd.setCursor(0, 0);
        //lcd.clear();
        
        switch(results.value){
          case 0xFFA25D:          
          lcd.print("CH-");
          break;
          case 0xFF629D:  //CH
          for(int i = 0; i < Maximum_value; i++)
            value[i] = 0;
          value_change = 0;
          mode_serect = 'n';
          lcd.clear();
          break;
          case 0xFFE21D:
          lcd.print("CH+");
          break;
          case 0xFF22DD:
          lcd.print("|<<");
          break;
          case 0xFF02FD:
          lcd.print(">>|");
          break ;  
          case 0xFFC23D:  //=
          if(mode_serect == 'a'){
            int result_prace = 0;
            for(int i = 0; i < Maximum_value; i++)
              result_prace += value[i];
            screen_display(result_prace);
            value[0] = result_prace;
            for(int j = 1; j < Maximum_value; j++)
              value[j] = 0;
            result_prace = 0;
            }
          else if(mode_serect == 'b'){
            int result_mainace = value[0];
            for(int i = 1; i < Maximum_value; i++)
              result_mainace -= value[i];
            screen_display(result_mainace);
            value[0] = result_mainace;
            for(int j = 1; j <Maximum_value; j++)
              value[j] = 0;
            result_mainace = 0;
          }
          break;
          case 0xFFE01F:  //-
          value_change++;
          mode_serect = 'b';
          lcd.clear();
          break ;  
          case 0xFFA857:  //+
          value_change++;
          mode_serect = 'a';
          lcd.clear();
          break ;  
          case 0xFF906F:
          lcd.print("EQ");
          break ;  
          case 0xFF6897:  //0
          value[value_change] *= 10;
          screen_display(value[value_change]);
          break ;  
          case 0xFF9867:
          lcd.print("100+");
          break ;
          case 0xFFB04F:
          lcd.print("200+");
          break ;
          case 0xFF30CF:  //1
          value[value_change] = carry(value[value_change]);
          value[value_change] += 1;
          screen_display(value[value_change]);
          break ;
          case 0xFF18E7:  //2
          value[value_change] = carry(value[value_change]);
          value[value_change] += 2;
          screen_display(value[value_change]);
          break ;
          case 0xFF7A85:  //3
          value[value_change] = carry(value[value_change]);
          value[value_change] += 3;
          screen_display(value[value_change]);
          break ;
          case 0xFF10EF:  //4
          value[value_change] = carry(value[value_change]);
          value[value_change] += 4;
          screen_display(value[value_change]);
          break ;
          case 0xFF38C7:  //5
          value[value_change] = carry(value[value_change]);
          value[value_change] += 5;
          screen_display(value[value_change]);
          break ;
          case 0xFF5AA5:  //6
          value[value_change] = carry(value[value_change]);
          value[value_change] += 6;
          screen_display(value[value_change]);
          break ;
          case 0xFF42BD:  //7
          value[value_change] = carry(value[value_change]);
          value[value_change] += 7;
          screen_display(value[value_change]);
          break ;
          case 0xFF4AB5:  //8
          value[value_change] = carry(value[value_change]);
          value[value_change] += 8;
          screen_display(value[value_change]);
          break ;
          case 0xFF52AD:  //9
          value[value_change] = carry(value[value_change]);
          value[value_change] += 9;
          screen_display(value[value_change]);
          break ;                   
        }
        delay(50);
        key_value = results.value;
        irrecv.resume(); 
  }
}

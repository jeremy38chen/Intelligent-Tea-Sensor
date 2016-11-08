//AnalogPin  5 TDS_current
//AnalogPin  2 TEMP_current
//DigitalPin 3 LED_Red
//DigitalPin 5 LED_Green
//DigitalPin 6 LED_Blue
//DigitalPin 8 recordPin( TDS_taste TEMP_taste)
//DigitalPin 9 bluetoothPin
#include "eeprom_anything.h"
#include <EEPROM.h>
#include <math.h>  
#include <SoftwareSerial.h>


#define recordPin          8
#define bluetoothPin       9
#define ThermistorPIN      2                 
#define TdsPin             5       
#define PwmPin             13
#define PwmFreq            5000
#define Error_Range        10
#define Differential_Value 20
#define Waiting_Time       10000
const int redPin   = 3;
const int greenPin = 5;
const int bluePin  = 6;



unsigned long        Vpeak_StartTime;
unsigned long        Record_StartTime;
static unsigned long NotReaching_StartTime;
unsigned long    PressTime             = 700;
unsigned long    Bluetooth_buttonTimer = 0;
unsigned long    Record_buttonTimer    = 0;
boolean Bluetooth_buttonActive = false;
boolean Record_buttonActive    = false;
boolean trigger = true;
boolean Search  = true;
int setData,setData2;//for receiving phone data
byte serialA;//判斷port
SoftwareSerial I2CBT(10,11); // TX:10, RX:11

struct User 
{
  double temp_taste;
  double tds_taste;
  double Its_temp_taste;
  double Its_tds_taste;
};
User UserData;//for eeprom

void setup() {

  Vpeak_StartTime = millis();
  tone(PwmPin,PwmFreq);//PWM 5000Khz 方波
  
  pinMode(recordPin,   INPUT);//DigitalPin 8 Record_button TDS_taste TEMP_taste
  pinMode(bluetoothPin,INPUT);//DigitalPin 9 Bluetooth_button 
  pinMode(redPin,      OUTPUT);
  pinMode(greenPin,    OUTPUT);
  pinMode(bluePin,     OUTPUT);  

  UserData.Its_temp_taste = 0; //智慧泡茶器的口感與記錄口感初始
  UserData.Its_tds_taste = 0; 
  UserData.temp_taste = 0; 
  UserData.tds_taste = 0;

  Off_light(redPin, bluePin, greenPin);
  Serial.begin(9600);
  I2CBT.begin(9600);//bluetooth 
  
}

void loop() {
  
  double         TEMP_current,TDS_current,TDS_theoretical=0.0;
  int            interval_taste;
  int            sensorValue,Vpeak;
  static int     LedOption,Replace_mode=0,Bluetooth_lighting=0;
  static double  TEMP_taste,TDS_taste,TDS_current_past;
  int state;
  int test = analogRead(4);
  //讀藍芽傳上來的口感
  EEPROM_readAnything(0,UserData);
  control(TEMP_current, TDS_current,6,TDS_theoretical);
  if(serialA == 50){
  UserData.Its_temp_taste= setData;
  UserData.Its_tds_taste= setData2;}
  //
  //UserData.Its_temp_taste = 45; 
  //UserData.Its_tds_taste = 700; 
  EEPROM_writeAnything(0,UserData);
  
            EEPROM_readAnything(0, UserData);//Check

  
  Vpeak = 0;
  //ㄧ秒內，最高值
  while((millis() - Vpeak_StartTime) <= 1000){
    
    sensorValue = analogRead(TdsPin);//AnalogPin  TDS_current
    Vpeak < sensorValue ? Vpeak = sensorValue : Vpeak = Vpeak;
    
  }
  
  Vpeak_StartTime = millis();//存現在時間
  

  TEMP_current = getTemperature(ThermistorPIN);//存現在的溫度
  TDS_current  = Vpeak;//存現在的tds
    
    
  //放入水中
  if(TDS_current > 270){

      if(LedOption !=4 && LedOption !=5)
        LedOption = 6;
     control(TEMP_current,TDS_current,7,TDS_theoretical);//for bluetooth (Its is in the water)
     
    //開始泡茶
    if(Search == 1 && UserData.Its_temp_taste != 0 && UserData.Its_tds_taste !=0){

          interval_taste  = Determine_TDSinterval(UserData.Its_temp_taste, UserData.Its_tds_taste);
          TDS_theoretical = Determine_THEORETICAL_TDS(UserData.Its_temp_taste, UserData.Its_tds_taste, interval_taste, TEMP_current);
        
        control(TEMP_current,TDS_current,1,TDS_theoretical);//for bluetooth (Searching)
        state = 1;//CHECK "Start to search!"
        
          
          if(TDS_current > TDS_theoretical +Error_Range)
          {
               LedOption = 5;
               control(TEMP_current,TDS_current,3,TDS_theoretical);//for bluetooth (Can't reach the consentration)
               state = 2; //check "Can't reach the consentration"
               Search = 0;//停止尋找
               trigger = 1;
          }
          //如果前一次的tds與現在的tds相差在Differential_Value內（達不到口感），開始計時
          else if(TDS_current - TDS_current_past < Differential_Value){

              if(trigger == 1){
                  NotReaching_StartTime = millis();
                  trigger = 0;//關
               }

                //如果開始計時後一分鐘還是在Differential_Value內，代表無法到達指定口味
               if(millis() - NotReaching_StartTime > Waiting_Time){
                
                  if(TDS_theoretical-Error_Range > TDS_current){        
                      LedOption = 5;
                      control(TEMP_current,TDS_current,3,TDS_theoretical);//for bluetooth (Can't reach the consentration)
                      state = 3; //check "Can't reach the consentration"
                      Search = 0;//停止尋找
                      trigger = 1;
                      
                    }
               
                 }

             }
             else{trigger = 1;}//開

          TDS_current_past = TDS_current;

          //如果現在tds與理論上的tds在error_range裡面，代表找到口味
          if(TDS_theoretical+Error_Range > TDS_current && TDS_current > TDS_theoretical-Error_Range ){
              
              control(TEMP_current,TDS_current,4,TDS_theoretical);//for bluetooth (Matched taste)
              state = 4;// "Matched taste"
              LedOption = 4;
              Search = 0;//停止尋找
 
            }

   
     }
      
     //記錄茶
    if(digitalRead(recordPin) == HIGH){
      
       if(Record_buttonActive == false){
        
          Record_buttonActive = true;
          Record_buttonTimer = millis();
        
        }
        
       if(millis() - Record_buttonTimer > PressTime){
        
          if(digitalRead(recordPin) ==1){
            LedOption = 3;
            control(TEMP_current,TDS_current,5,TDS_theoretical);//for bluetooth (Like button is pressed)
            UserData.temp_taste = TEMP_current;
            UserData.tds_taste  = TDS_current;
            if(Replace_mode ==1){
              
              UserData.Its_temp_taste = TEMP_current; 
              UserData.Its_tds_taste  = TDS_current;
              
              }
            Replace_mode = 0;
            EEPROM_writeAnything(0, UserData);//Save to eeprom
            EEPROM_readAnything(0, UserData);//Check
          }
          
        }
        
     }else{Record_buttonActive = false;}
      
    }
    //覆蓋模式
    else if(digitalRead(recordPin) == HIGH){
      
       if(Record_buttonActive == false){
        
          Record_buttonActive = true;
          Record_buttonTimer = millis();
        
        }
        
       if(millis() - Record_buttonTimer > PressTime){
        
          if(digitalRead(recordPin) ==1){
            LedOption = 7; //Replacemode_light
            control(TEMP_current,TDS_current,8,TDS_theoretical);
            Replace_mode = 1;
            Search = 0;
          }
          
        }
    }
    //按下藍芽按件
    else if(digitalRead(bluetoothPin) == HIGH){
      if(Bluetooth_buttonActive == false){
        
          Bluetooth_buttonActive = true;
          Bluetooth_buttonTimer = millis();
        
        }
      if(millis() - Bluetooth_buttonTimer > PressTime){

          if(digitalRead(bluetoothPin) ==1)
          {
             LedOption = 2; 
             Serial.println("Blue press");
             Bluetooth_lighting =1;//連線中
             //Bluetooth_lighting =0;//連線結束
            }
          
        }
    }   
    else if (Replace_mode != 1){
      
      Record_buttonActive = false;
      LedOption = 1; 
      Search = 1;//進入水質開始收尋
    }
    else{
      Bluetooth_buttonActive = false;
      Record_buttonActive = false;
    }  
   switch(LedOption){
      case 1:
        On_light(redPin,greenPin,bluePin); 
        break;
      case 2:
        Bluetooth_light(redPin,greenPin,bluePin);
        break;
      case 3:
        Record_light( redPin, greenPin, bluePin); 
        break;
      case 4:
        Readytodrink_light(redPin, greenPin, bluePin); 
        break;
      case 5:
        NotReaching_light( redPin, greenPin, bluePin);
        break;
      case 6:
        Water_light(redPin,greenPin,bluePin);
        break;
      case 7:
        Replacemode_light(redPin,greenPin,bluePin);
        break;
      }
       Serial.print("State of Its: ");//CHECK
            switch(state){
              case 1: 
                Serial.println("Start to search!");
                break;
              case 2:
                Serial.println("Can't reach the consentration");
                break;
              case 3:
                Serial.println("Can't reach the consentration");
                break;
              case 4:
                Serial.println("Matched taste");
                break;
              }
            Serial.print("Its_TEMP_taste: ");//CHECK
            Serial.print(UserData.Its_temp_taste);//CHECK
            Serial.print("   Its_TDS_taste: ");//CHECK
            Serial.println(UserData.Its_tds_taste);//CHECK
            Serial.print("TEMP_taste: ");//CHECK
            Serial.print(UserData.temp_taste);//CHECK
            Serial.print("   TDS_taste: ");//CHECK
            Serial.println(UserData.tds_taste);//CHECK
            Serial.println("----------------------------------------------");
            Serial.print("TEMP_current: ");//CHECK
            Serial.print(TEMP_current);//CHECK
            Serial.print("    TDS_current: ");//CHECK
            Serial.println(TDS_current);//CHECK
            Serial.print("TEMP_current: ");//CHECK
            Serial.print(TEMP_current);//CHECK
            Serial.print("    TDS_Theoretical: ");//check
            Serial.println(int(TDS_theoretical));//check
            Serial.println("  ");
}

//d3:state
//  1 = Searching
//  2 = Successful 
//  3 = Not reaching 
//  4 = Matched taste
//  5 = Like button is pressed
//  6 = 不寫
//  7 = Its is in the water
//  8 = Saving mode
// d1:temp的值 d2:ads的值 d3:state(以數字表示)
void control(int d1, int d2, int d3, int d4){

  if(I2CBT.available()>0){
    serialA=I2CBT.read();
 
       switch(serialA){
        
         case 49:   
          monitor(d1,d2,d3,d4);
          break;

         case 50:
          Serial.print("TMP:");
          Serial.println(setData = receive());     
          Serial.println(setData2 = receive());
                    
          break;

         case 51:
          
          break;

         default:
          break;
         
        }
      serialA=0;
    }
}


void monitor(int d1, int d2, int d3, int d4){

    byte Data[9];
    
    Data[0]='a';
    Data[1]=d1/256;
    Data[2]=d1%256;
    Data[3]='b';
    Data[4]=d2/256;
    Data[5]=d2%256;
    Data[6]='c';
    Data[7]=d3/256;
    Data[8]=d3%256;
    Data[9]='d';
    Data[10]=d4/256;
    Data[11]=d4%256;

    for(int j=0;j<=11;j++){
      I2CBT.write(Data[j]);
    }
  
  // Print
  Serial.print(d1);
  Serial.print(" , ");
  Serial.print(d2);
  Serial.print(" , ");
  Serial.println(d3);
  Serial.print(" , ");
  Serial.println(d4);
  }

int receive(){

   int data[2];
   int setData;
   if(I2CBT.available()>0){
      data[0] = I2CBT.read();
      data[1] = I2CBT.read();
  }
   data[0] *= 256;
   if(data[1]<0)
    data[1]+=256;
   setData=data[0]+data[1];
  
   return setData;
}

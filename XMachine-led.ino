#include <Wire.h>

#include <FastLED.h> 

#define NUM_LEDS_METR 60
#define NUM_LEDS 144
#define LED_TYPE NEOPIXEL
#define NUM_STRIPS 8       
//#define LED_TYPE   WS2815
#define MAX_BRIGHT 240
#define MIN_BRIGHT 40
#define BRIGHT_1 30
#define BRIGHT_2 100
#define BRIGHT_3 150
#define STEP_BRIGHT_1 10
#define STEP_BRIGHT_2 4
#define STEP_BRIGHT_3 5
#define SATURATION 255
#define FIRST NUM_LEDS_METR*1
#define SECOND 2*NUM_LEDS_METR
#define THIRD 3*NUM_LEDS_METR
#define FOURTH 4.5*NUM_LEDS_METR+40
#define FIFTH 5.5*NUM_LEDS_METR-19
#define SIXTH 6*NUM_LEDS_METR+16
#define SEVENTH 144
#define EIGHTH 144


#define STEPS_CNT_RANGE 7
#define MAX_RANGE 1024
#define MIN_RANGE 146

double stepp= MAX_RANGE/STEPS_CNT_RANGE;
bool alarm_flag=false;
int type_processing=0;
//byte COLOR = 0; 
byte BRIGHTNESS = 0;
byte STEP_BRIGHT;
uint8_t current_color;
int j_pred=STEPS_CNT_RANGE;
double val_pred;
double val_predd=MAX_RANGE;
#define OFFSET 9
int num_leds[8] ={FIRST,SECOND,THIRD,FOURTH,FIFTH,SIXTH,SEVENTH,EIGHTH};


CRGB leds1[FIRST];
CRGB leds2[SECOND+THIRD];
CRGB leds4[int(FOURTH)];
CRGB leds5[int(FIFTH)];
CRGB leds6[int(SIXTH)];
CRGB leds7[SEVENTH];
CRGB leds8[EIGHTH];

CRGB* leds[8];

int BRIGHT[8];
int COLOR=0;
int SATURATION2=0;
void setup() {
  pinMode(0,INPUT_PULLUP);
  pinMode(A0,INPUT_PULLUP);
  
   Serial.begin(9600);

  //A0, A1, A2 as outputs.
//  leds[0]=leds1;
//  leds[1]=leds2;
//  leds[2]=leds3;
//  leds[3]=leds4;
//  leds[4]=leds5;
//  leds[5]=leds6;
//  leds[6]=leds7;


  FastLED.addLeds<LED_TYPE, 8>(leds1, FIRST,0);
  FastLED.addLeds<LED_TYPE, 4>(leds2, SECOND+THIRD);
  FastLED.addLeds<LED_TYPE, 7>(leds4, int(FOURTH));
  FastLED.addLeds<LED_TYPE, 6>(leds5, int(FIFTH));
  FastLED.addLeds<LED_TYPE, 9>(leds6, int(SIXTH));
  FastLED.addLeds<LED_TYPE, 3>(leds7, SEVENTH);
  FastLED.addLeds<LED_TYPE, 5>(leds8, EIGHTH);

  leds[0]=leds1;
  leds[1]=&leds2[0];
  leds[2]=leds2;
  leds[3]=leds4;
  leds[4]=leds5;
  leds[5]=leds6;
  leds[6]=leds7;
  leds[7]=leds8;
  
  COLOR=0;
  SATURATION2=0;
  
  BRIGHT[0]=255;
  BRIGHT[1]=255;
  BRIGHT[2]=255; 
  BRIGHT[3]=255;
  BRIGHT[4]=255;
  BRIGHT[5]=255;
  BRIGHT[6]=255;
  BRIGHT[7]=255;  
//
//         for(int i=0;i<NUM_STRIPS;i++){
//    //turn_on(i,COLOR,SATURATION,BRIGHTNESS)
//    // i - не трогать, остальные значения 0-255
//    turn_on(i,COLOR,SATURATION2,BRIGHT[i]);
//    
//    }
////
//    for(int i=0;i<NUM_STRIPS;i++){
//    //turn_on(i,COLOR,SATURATION,BRIGHTNESS)
//    // i - не трогать, остальные значения 0-255
//    turn_on(i,0,0,MIN_BRIGHT);
//    }
//  }
//   FastLED.showColor(CRGB::White);
// turn_on(0,COLOR,SATURATION2,BRIGHT[0]);
 processing(0);
  j_pred=-2;
 val_predd=-100;
  delay(3000);
}


  void loop(){
  
 //   test();
    read_ports();
    //checkChange();
  }

void test(){
  for (int i=126;i<860;){

    processing2(i);
    i=i+20;

    }
    for (int i=860;i>126;){
    processing2(i);
    i=i-20;

    }
   
  }
void read_buttons() {
  bool CHECK_BTN_2_STATE = digitalRead(11);
  bool CHECK_BTN_1_STATE = digitalRead(12);
  bool CHECK_BTN_3_STATE = digitalRead(13);
//  Serial.println(CHECK_BTN_2_STATE);
//  Serial.println(CHECK_BTN_1_STATE);
//  Serial.println(CHECK_BTN_3_STATE);

  if (!CHECK_BTN_1_STATE) {
    
    if (BRIGHTNESS > 0) BRIGHTNESS--;
    //color_palette();
  }

  if (!CHECK_BTN_3_STATE) {
    if (BRIGHTNESS < 255) BRIGHTNESS++;
    //color_palette();
  }
  
  if (!CHECK_BTN_2_STATE ) {
    color_palette();
  }
 
} 

void read_ports() {
  int val = -1;
  val=analogRead(A0);
    Serial.println("val:");   
  Serial.println(val);
   Serial.println(MAX_RANGE-val);
 Serial.print("type_processing: ");
   Serial.println(type_processing);
   processing2(MAX_RANGE-val);   
// switch(type_processing){
//  case 0:
//     processing2(MAX_RANGE-val);
//   
//    break;
//  case 1:
//   breathe();
//    break;
//  case 2:
//    processing(MAX_RANGE-val);   
//    break;
//  }

}

void breathe(){

    for (int bright=MIN_BRIGHT;bright<MAX_BRIGHT;){
    for(int i=0;i<NUM_STRIPS;i++){
    //turn_on(i,COLOR,SATURATION,BRIGHTNESS)
    // i - не трогать, остальные значения 0-255
    turn_on(i,100,0,bright);
    
    }
    bright=bright+10;
    FastLED.show();
    FastLED.show();
    }
    
    for (int bright=MAX_BRIGHT;bright>MIN_BRIGHT;bright--){
    for(int i=0;i<NUM_STRIPS;i++){
    //turn_on(i,COLOR,SATURATION,BRIGHTNESS)
    // i - не трогать, остальные значения 0-255
    turn_on(i,100,0,bright);
    }
    bright=bright-10;
      FastLED.show();
    FastLED.show();
    }
  
  }
void checkChange(){
  int val =digitalRead(0);

  delay(50);
  if (val!=digitalRead(0)){
    return;
    }

  if(val !=0){
    return;
    }  
  type_processing++;
  if (type_processing>3){
    type_processing=0;
    }
    j_pred=STEPS_CNT_RANGE;

 val_predd=MAX_RANGE;
 processing(0);
  }

  
void checkAl(){
  int val=digitalRead(0);
  delay(50);
  if (val!=digitalRead(0)){
    return;
    }

   Serial.print("val");
   Serial.println(val);
  if (val==0){
    if(!alarm_flag){
      Serial.println("alarm");
 Serial.println("alarm");
      alarm();
     
      }
  alarm_flag=true;   
  }else{
    if(alarm_flag){
      Serial.println("norm");
    alarm_flag=false;
    whiteC();
      }
    }
    
}

void whiteC(){
    for(int i=0;i<NUM_STRIPS;i++){
    //turn_on(i,COLOR,SATURATION,BRIGHTNESS)
    // i - не трогать, остальные значения 0-255
    turn_on(i,COLOR,SATURATION2,BRIGHT[i]);
    
    }
    FastLED.show();
    FastLED.show();
  
  
}
void alarm(){
    for(int i=0;i<NUM_STRIPS;i++){
    //turn_on(i,COLOR,SATURATION,BRIGHTNESS)
    // i - не трогать, остальные значения 0-255
    turn_on(i,96,255,255);
    
    }
    
    FastLED.show();
    FastLED.show();
  //FastLED.showColor(CHSV(96,255,255)); 
  
}
  

void processing(int val){
   
    if(abs(val-val_predd)<OFFSET){
      return;
      }
    
    if (val>MAX_RANGE){
      val=MAX_RANGE;
    }
    if (val<MIN_RANGE){
      val = MIN_RANGE;
      }
    

    val_predd=val;  
    
    Serial.print("step:");
    Serial.println(val/stepp);
    int temp;
    int j;
    double temp2;
    j=val/stepp;
    j--;
    Serial.print("j:");
    Serial.println(j);
    Serial.print("j_pred:");
    Serial.println(j_pred);
    if(j !=j_pred){
      if(j-j_pred>0){
          //smooth(j_pred,val_pred,MAX_BRIGHT);
          for(int i=j_pred;i<=j;i++){
          Serial.print("on:");
          Serial.println(i);
          turn_on2(i,MAX_BRIGHT);
        
          }  
          val_pred=MIN_BRIGHT;
           j_pred=j;
           
        }else{
            turn_on2(j_pred+1,MIN_BRIGHT);
            //smooth(j_pred+1,val_pred,MIN_BRIGHT);
            for(int i=j_pred;i>j+1;i--){
            Serial.print("off:");
            Serial.println(i);
            //smooth(i,MAX_BRIGHT,MIN_BRIGHT);
            turn_on2(i,MIN_BRIGHT);
          }
          val_pred=MAX_BRIGHT;
        }
//      for(int i=j+2;i<NUM_STRIPS;i++){
//      turn_off2(i,255);
//      }
//      for(int i = 0;i<=j;i++){
//      turn_on2(i,255);
//      }
    j_pred=j;
    }
    int jx=j+1;
    temp2=val-jx*stepp;
    temp2=temp2/stepp;
    temp=temp2*255;
      Serial.print("temp:");
      Serial.println(temp);
    if(temp<MIN_BRIGHT){
      temp=MIN_BRIGHT;
      }
    if(temp>MAX_BRIGHT){
      temp=MAX_BRIGHT;
      }  
      Serial.print("val_pred:");
      Serial.println(val_pred);
    Serial.print("update:");
    Serial.println(temp);
    if(temp==MIN_BRIGHT){
      return;
      }
    turn_on2(j+1,temp);
    val_pred=temp;
      
  }

void color_palette() {
Serial.println("change");  
FastLED.clear();
FastLED.show();
      
}



void processing2(int val){
    if(abs(val-val_predd)<OFFSET){
      return;
      }
    
    if (val>MAX_RANGE){
      val=MAX_RANGE;
    }
    if (val<MIN_RANGE){
      val = MIN_RANGE;
      }
    
     val_predd = val;

       
    Serial.print("step:");
    Serial.println(val/stepp);
    int j;
    double temp;
    double K;
    j=val/stepp;
    K=255/stepp;
    Serial.print("j:");
    Serial.println(j);
    Serial.print("j_pred:");
    Serial.println(j_pred);
    if(j !=j_pred){
      if(j-j_pred>0){
          //smooth(j_pred,val_pred,MAX_BRIGHT);
          for(int i=j_pred;i<=j-2;i++){
          Serial.print("off:");
          Serial.println(i);
          turn_on2(i,MIN_BRIGHT);
          }  
           turn_on2(j,MIN_BRIGHT);
          val_pred=MIN_BRIGHT;
          
        }else{
            for(int i=j_pred;i>j+2;i--){
            Serial.print("off:");
            Serial.println(i);
            turn_on2(i,MIN_BRIGHT);
          }
          turn_on2(j-3,MIN_BRIGHT);
          val_pred=MAX_BRIGHT;
        }

    j_pred=j;
    return;
    }
    
    temp=double(val%int(stepp));
    temp=K*temp;

    double off_val=255-temp;
    if(temp<MIN_BRIGHT){
      temp=MIN_BRIGHT;
      }
    if(temp>MAX_BRIGHT){
      temp=MAX_BRIGHT;
      }  

    if(off_val<MIN_BRIGHT){
      off_val=MIN_BRIGHT;
      }
    if(off_val>MAX_BRIGHT){
      off_val=MAX_BRIGHT;
      }  

     if(abs(temp-val_pred)<OFFSET){
      return;
      }
      Serial.print("val_pred:");
      Serial.println(val_pred);
    Serial.print("on led:");
    Serial.println(temp);
    Serial.print("off led:");
    Serial.println(off_val);
    if(temp==MIN_BRIGHT){
      return;
      }
    turn_on2(j,temp);
    turn_on2(j-2,off_val);
    
    val_pred=temp;
    
  }

void processing3(int val,bool clear_leds){
    if(abs(val-val_predd)<OFFSET){
      return;
      }
    
    if (val>MAX_RANGE){
      val=MAX_RANGE;
    }
    if (val<MIN_RANGE){
      val = MIN_RANGE;
      }
    
     val_predd = val;

       
    Serial.print("step:");
    Serial.println(val/stepp);
    int j;
    double temp;
    double K;
    j=val/stepp;
    K=255/stepp;
    Serial.print("j:");
    Serial.println(j);
    Serial.print("j_pred:");
    Serial.println(j_pred);
    if(j !=j_pred){
      if(j-j_pred>0){
          //smooth(j_pred,val_pred,MAX_BRIGHT);
          //turn_on2(j,MIN_BRIGHT);
          val_pred=MIN_BRIGHT;
          
        }else{
          turn_on2(j-3,MIN_BRIGHT);
          val_pred=MAX_BRIGHT;
        }

    

    j_pred=j;
    return;
    }
    
    temp=double(val%int(stepp));
    temp=K*temp;

    double off_val=255-temp;
    if(temp<MIN_BRIGHT){
      temp=MIN_BRIGHT;
      }
    if(temp>MAX_BRIGHT){
      temp=MAX_BRIGHT;
      }  

    if(off_val<MIN_BRIGHT){
      off_val=MIN_BRIGHT;
      }
    if(off_val>MAX_BRIGHT){
      off_val=MAX_BRIGHT;
      }  

     if(abs(temp-val_pred)<OFFSET){
      return;
      }
      Serial.print("val_pred:");
      Serial.println(val_pred);
    Serial.print("on led:");
    Serial.println(temp);
    Serial.print("off led:");
    Serial.println(off_val);
    if(temp==MIN_BRIGHT){
      return;
      }
  if (clear_leds){
   for(int i=0;i<6;i++){
    turn_on(i,0,0,MIN_BRIGHT);
    
    }
  }
    turn_on2(j,temp);
    turn_on2(j-2,off_val);
    val_pred=temp;
    
  }
 void clear_strip(int strip){
     int nums;
    int i;
     if(strip == 1){
      i=THIRD;
      nums=SECOND+THIRD;
      }else if(strip==2){
       i=0;
       strip=1;
       nums=THIRD-1; 
      }else{
        i=0;
        nums=num_leds[strip];
      }
     for(; i <nums; i++) {
      leds[strip][i] = CHSV(0,0,0);
      }
      //FastLED.show();
  
  }


 void turn_on(int strip,int color,int saturation,int brightness){
    int nums;
    int i;
     if(strip == 1){
      i=THIRD;
      nums=SECOND+THIRD;
      }else if(strip==2){
       i=0;
       strip=1;
       nums=THIRD-1; 
      }else{
        i=0;
        nums=num_leds[strip];
      }
     for(; i <nums; i++) {
      leds[strip][i] = CHSV(color,saturation,brightness);
      }
      //FastLED.show();
   
  }
  

  void turn_off(int strip,int color){
      Serial.println("off");  
      for(; BRIGHTNESS > MIN_BRIGHT; BRIGHTNESS = BRIGHTNESS-STEP_BRIGHT){
       if (BRIGHTNESS<BRIGHT_1){
        STEP_BRIGHT=STEP_BRIGHT_1;
        }else if(BRIGHTNESS<BRIGHT_2){
          STEP_BRIGHT=STEP_BRIGHT_2;
          }else if (BRIGHTNESS<BRIGHT_3){
            STEP_BRIGHT=STEP_BRIGHT_3;
            } 
      for(int i = 0; i < num_leds[strip]; i++) {
     leds[strip][i] = CHSV(color,SATURATION,BRIGHTNESS);
     
        }
        FastLED.show();
      }
  
  }

void turn_on2(int strip,int color){
    if (strip==0){
      return;
      }
    int nums;
    int i;
     if(strip == 1){
      i=THIRD;
      nums=SECOND+THIRD;
      }else if(strip==2){
       i=0;
       strip=1;
       nums=THIRD-1; 
      }else{
        i=0;
        nums=num_leds[strip];
      }
     for(; i <nums; i++) {
      leds[strip][i] = CHSV(0,0,color);
      }
      FastLED.show();
   
  }

  void turn_off2(int strip,int color){
    int nums;
    int i;
     if(strip == 1){
      i=THIRD;
      nums=SECOND+THIRD;
      }else if(strip==2){
       i=0;
       strip=1;
       nums=THIRD; 
      }else{
        i=0;
        nums=num_leds[strip];
      }
     for(; i <nums; i++) {
      leds[strip][i] = CHSV(0,0,color);
      }
      FastLED.show();
   
  }

  void smooth(int strip, int val1, int val2){
     int i,k,j,nums;
     if(strip == 1){
      i=THIRD;
      nums=SECOND+THIRD;
      }else if(strip==2){
       i=0;
       strip=1;
       nums=THIRD; 
      }else{
        i=0;
        nums=num_leds[strip];
      }     
     
     if(val2 -val1>0){
      for(j=val1;j<val2;j+=STEP_BRIGHT_1){  
      k=i;
      for(; k <nums; k++) {
      leds[strip][k] = CHSV(0,0,j);
      }
      FastLED.show();
      }
      }else{
      for(j=val1;j>val2;j-=STEP_BRIGHT_1){  
      k=i;
      for(; k <nums; k++) {
      leds[strip][k] = CHSV(0,0,j);
      }
      FastLED.show();
      }
  
          
      }
//     
//     if(strip == 1){
//      i=THIRD;
//      nums=SECOND+THIRD;
//      }else if(strip==2){
//       i=0;
//       strip=1;
//       nums=THIRD; 
//      }else{
//        i=0;
//        nums=num_leds[strip];
//      }
//     for(; i <nums; i++) {
//      leds[strip][i] = CHSV(0,0,0);
//      }
//      FastLED.show();
    
    }
 
//void color_palette2(int a, int b,int c) {
//  for (uint8_t ch = 0; ch <= 7; ch++) { // Перебираем каждый канал мультиплексора
//    for (int i = 0; i < 255; i++) {// Загоняем всю последовательность пикселей о оперативку
//      leds[i] = CHSV(a, b, c);
//    }
//    PORTF = channels[ch];
//    FastLED.show();
//  }
//}

//
//void receiveEvent(int howMany)
//{
//  Serial.println("get!");
//  while(Wire.available()) // loop through all but the last
//  {
//    if(inc>2)exit(0);
//    int x = Wire.read();
//    Serial.println(x);   
//    if(x == 0){
//      inc = 0;
//  
//    return;
//    }  
//    rgb[inc] = x;
//    inc++;
//        if(inc == 3){
//      inc = 0;
//      for(int l =0;l<3;l++)
//    Serial.println(rgb[l]);  
//    //color_palette2(rgb[0],rgb[1],rgb[2]);
//    return;
//    }  
//  }
//
//}

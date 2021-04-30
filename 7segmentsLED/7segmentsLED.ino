//デジタル時計:7セグ

#define ASCII_ZERO 48;
 
int pin_A[4] = {1,2,3,4};             //アノード　桁選択
int pin_n[7] = {13,12,11,10,9,8,7};    //カソード　数値選択
const char buzzer = A4;
//int pin_k = 11;                       //: 2桁目のみ
bool state;
 
byte num_def[11] = {B11000000,  // 0  (各bit: 0_ON, 1_OFF)
                B11111001,      // 1
                B10100100,      // 2
                B10110000,      // 3
                B10011001,      // 4
                B10010010,      // 5
                B10000010,      // 6
                B11111000,      // 7
                B10000000,      // 8
                B10010000,      // 9
                B11111111};     // OFF
 
void setup(void) {
  //Serial.begin(9600);
 
  //各ピンの初期化
  for(int i=1; i<=5; i++){
    pinMode(i,OUTPUT);  
    digitalWrite(i,LOW);
  }  
  for(int i=7; i<=13; i++){
    pinMode(i,OUTPUT);  
    digitalWrite(i,HIGH);
  }
  pinMode(A4,OUTPUT);
  pinMode(A5,INPUT_PULLUP);  
}
 
void loop(void) {
  
  seg_clock();
   
}
 
void seg_clock(void){
  //7セグに時刻を出力
  int buf[4] = {0,0,0,0};
  int time = 9999 - round(millis()/1000);
 
  buf[0] = time%10;       //分　10位
  buf[1] = time/10%10;    //分　1位
  buf[2] = time/100%10;   //秒　10位
  buf[3] = time/1000%10;  //秒　1位
   
  //4桁表示
  for (int i=0; i<=3; i++){
    digitalWrite(pin_A[i],HIGH);    
    for (int j=0; j<7; j++ ){
      digitalWrite(pin_n[j],bitRead(num_def[buf[i]],j));  
    }
    //digitalWrite(pin_k,LOW);    //:を表示  
    delay(5);  
    digitalWrite(pin_A[i],LOW);
  }
  if ((millis()/100%10 == 0) && (state == HIGH)){
    tone(buzzer, 500, 30);
  }
  //Serial.println(millis()/100%10);
  if (digitalRead(A5) == LOW){
    state = !state;
    delay(20);
  }
}

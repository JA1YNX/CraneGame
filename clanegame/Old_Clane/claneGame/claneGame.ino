/*
 Arduinoでクレーンゲーム
 
   * コイン（10円）投入されたら、ゲーム開始。照明と音楽スタート。
   * S2,s3それぞれ押してる間だけ、モーターが回転する。
   * lim1～4にギアボックスが当たって押下されるとモーターはストップ。
*/

#define pin_swR 10        // SW Red
#define pin_swB 11        // SW Blue

#define pin_Xlim A0       
#define pin_Ylim A1       
#define pin_ZlimTop A3
#define pin_ZlimBot A2

#define Arm A5

#define pin_mdXA 4
#define pin_mdXB 5
#define pin_mdYA 3
#define pin_mdYB 2
#define pin_mdZA 6
#define pin_mdZB 7

const bool ArmOPEN = 1;
const bool ArmCLOSE = 0;

bool s_red=1, s_blue=1, s_xlim = 1, s_ylim = 1, s_zlimTop = 1, s_zlimBot = 1;
bool zflag = 1; 

void X();
void Y();
void Z();

const bool CW = 1;
const bool CCW = 0;

void mvX(bool _mvx){
  digitalWrite(pin_mdXA, _mvx);
  digitalWrite(pin_mdXB, !_mvx);
}
void mvY(bool _mvy){
  digitalWrite(pin_mdYA, _mvy);
  digitalWrite(pin_mdYB, !_mvy);
}
void mvZ(bool _mvz){
  digitalWrite(pin_mdZA, _mvz);
  digitalWrite(pin_mdZB, !_mvz);
}
void stopall(){
  digitalWrite(pin_mdXA, HIGH);
  digitalWrite(pin_mdXB, HIGH);
  digitalWrite(pin_mdYA, HIGH);
  digitalWrite(pin_mdYB, HIGH);
  digitalWrite(pin_mdZA, HIGH);
  digitalWrite(pin_mdZB, HIGH);

  Serial.println("stop");
}

void setup() 
{
  pinMode(pin_swR, INPUT_PULLUP);
  pinMode(pin_swB, INPUT_PULLUP);
  pinMode(pin_Xlim, INPUT_PULLUP);    // lim1(ピン14)を入力に設定
  pinMode(pin_Ylim, INPUT_PULLUP);    // lim1(ピン15)を入力に設定
  pinMode(pin_ZlimTop, INPUT_PULLUP);    // lim1(ピン16)を入力に設定
  pinMode(pin_ZlimBot, INPUT_PULLUP);    // lim1(ピン17)を入力に設定

  pinMode(Arm, OUTPUT);
  stopall();

  Serial.begin(115200);

  stopall();
  delay(500);

  digitalWrite(Arm, ArmOPEN);
  delay(500);

  Serial.println("start");
}

void loop()
{
  X();
  Y();
  Z(ArmCLOSE);
  Home();
}

void X(){
  Serial.println("x");
  
  // wait SW Red pushed
  while(s_red){
    delay(1);
    s_red=digitalRead(pin_swR);
  }
  
  Serial.println("s red pushed");
  mvX(CW);
  
  //wait SW Red released
  while(!s_red)
  {
    delay(1);
    s_red=digitalRead(pin_swR); 
  }

  Serial.println("s red released");
  stopall();

  s_red = s_blue = s_xlim = s_ylim = s_zlimTop = s_zlimBot = 1;
}

void Y(){
  Serial.println("y");
  
  //wait sw blue pushed
  while(s_blue)
  {
    delay(1);
    s_blue = digitalRead(pin_swB);
  }
  
  Serial.println("s blue pushed");
  mvY(CW);

  //wait sw blue released
  while(!s_blue)// PBS2が押されている間は、
  {
    delay(1);
    s_blue = digitalRead(pin_swB);
  }
  
  Serial.println("s blue released");
  stopall();
  s_red = s_blue = s_xlim = s_ylim = s_zlimTop = s_zlimBot = 1;
  delay(500);
}

/*****************Z***************/
void Z(bool _armOorC){
  Serial.println("z");
  delay(500);
  
  zflag ? mvZ(CW) : mvZ(CCW);

  while(s_zlimBot && !s_zlimTop){
    delay(1);
    s_zlimBot = digitalRead(pin_ZlimBot);
    s_zlimTop = digitalRead(pin_ZlimTop);
  }

  Serial.println("Max depth");
  stopall();

  delay(500);

  Serial.println("ArmCLOSE");
  digitalWrite(Arm, _armOorC);
  delay(50);

  mvZ(CCW);
  
  while(s_zlimTop){
    delay(1);
    s_zlimTop = digitalRead(pin_ZlimTop);
  }
  
  Serial.println("min depth");
  delay(1000);

  s_red = s_blue = s_xlim = s_ylim = s_zlimTop = s_zlimBot = 1;
}

void Home(){
  stopall();
  delay(500);

  mvY(CCW);
  while(s_ylim){
    s_ylim = digitalRead(pin_Ylim);
  }
  Serial.println("Y Home");

  mvX(CCW);
  while(s_xlim){
    s_xlim = digitalRead(pin_Xlim); 
  }
  Serial.println("X Home");
  stopall();
  
  Z(ArmOPEN);
}

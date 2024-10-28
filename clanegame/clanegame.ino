//クレーンゲーム(/・ω・)/


//ピンどもの定義
//モーターどもの定義
const int X_motor1 = 2; //motorDriver 1 1A pin
const int X_motor2 = 3; //motorDriver 1 1B pin
const int Y_motor1 = 4; //motorDriver 1 2A pin
const int Y_motor2 = 5; //motorDriver 1 2B pin
const int Z_motor1 = 6; //motorDriver 2 1A pin
const int Z_motor2 = 7; //motorDriver 2 1B pin 
const int Arm_motor1 = 9; //motorDriver 2 2A pin
const int Arm_motor2 = 10; //motorDriver 2 2B pin

//リミッターどもの定義
//Xのリミッターの導線よく外れる。注意。
const int X_limit1 = 13; //X limitter 手前 PULLUP
const int Y_limit1 = 14; //Y limitter front PULLUP
const int Y_limit2 = 15; //Y limitter back PULLUP
const int Z_limit1 = 16; //Z limitter DOWN PULLUP
const int Z_limit2 = 17; //Z limitter UP PULLUP
const int sensor = 35; //microwave trig NOT USE

//ボタンたちの定義
const int button1 = 30; //L button
const int button2= 31; //R button

//変数どもの宣言
int xl; //x limitter
int zl1; //z limitter 1
int zl2; //z limitter 2
int yl1; //y limitter 1
int yl2; //y limitter 2
int b1 = 0; //L button status
int b2 = 0; //R button status
int teat = 0; //Wats is this
float distance; //NOT USE
int s = 0;

int clear = 0; //TO CLEAR NOT USE

void setup() {
  //pinModeの山
  pinMode(X_motor1,OUTPUT);
  pinMode(Y_motor1,OUTPUT);
  pinMode(Y_motor2,OUTPUT);
  pinMode(X_motor2,OUTPUT);
  pinMode(Z_motor1,OUTPUT);
  pinMode(Z_motor2,OUTPUT);
  pinMode(X_limit1,INPUT_PULLUP);
  pinMode(Z_limit1,INPUT_PULLUP);
  pinMode(Z_limit2,INPUT_PULLUP);
  pinMode(Y_limit1,INPUT_PULLUP);
  pinMode(Y_limit2,INPUT_PULLUP);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(Arm_motor1,OUTPUT);
  pinMode(Arm_motor2,OUTPUT);
  pinMode(sensor,INPUT_PULLUP);

  Serial.begin(9600); //シリアル通信開始。速度9600

  Serial.println("Hello!"); //開始合図

  //リセット
Serial.println("リセットします"); //TX、RXに他マイコン接続時注意。
Serial.println("Z　リセット中...");

      digitalWrite(Z_motor1,LOW);
      digitalWrite(Z_motor2,HIGH);
      delay(300);

   while(1){
      zl2 = digitalRead(Z_limit2);

  if(zl2 == 1){      //nolimit
      digitalWrite(Z_motor1,LOW);
      digitalWrite(Z_motor2,HIGH);
    }
    else{
      delay(500);
      digitalWrite(Z_motor1,LOW);
      digitalWrite(Z_motor2,LOW);
      break;
    }
}

  Serial.println("Z リセット　終了");

    Serial.println("X Y リセット中...");

    int i = 0;

    digitalWrite(X_motor1,HIGH);
    digitalWrite(X_motor2,LOW);
    digitalWrite(Y_motor1,HIGH);
    digitalWrite(Y_motor2,LOW);
    delay(2000);
    digitalWrite(X_motor1,LOW);
    digitalWrite(X_motor2,LOW);
    digitalWrite(Y_motor1,LOW);
    digitalWrite(Y_motor2,LOW);

Serial.println("X Y リセット　終了");
Serial.println("アームを開いています...");
//OPEN
digitalWrite(Arm_motor1,LOW);
digitalWrite(Arm_motor2,LOW);

Serial.println("リセット終了！");

}


void loop() {
 Serial.println("待機時間");

  delay(700);
  digitalWrite(Arm_motor1,LOW);
  digitalWrite(Arm_motor2,HIGH);
  delay(100);
  digitalWrite(Arm_motor1,LOW);
  digitalWrite(Arm_motor2,LOW);

  Serial.println("新しいゲームがスタートしました");
//one round
  //X prosess
  xl = digitalRead(X_limit1);

   Serial.println("X 待機中...");

 while(1){
  b1 = digitalRead(button1);
  if(b1 == 0){   
     Serial.println("X　ボタンが押されました");
    while(b1 == 0){
    b1 = digitalRead(button1);
    digitalWrite(X_motor1,LOW);
    digitalWrite(X_motor2,HIGH);
    }
    digitalWrite(X_motor1,LOW);
    digitalWrite(X_motor2,LOW);
    break;
  }
 }

Serial.println("X 終了");
Serial.println("Y 待機中...");

 while(1){
  b2 = digitalRead(button2);
  if(b2 == 0){   
    Serial.println("Y ボタンが押されました");
    while(b2 == 0){
    b2 = digitalRead(button2);
    digitalWrite(Y_motor1,LOW);
    digitalWrite(Y_motor2,HIGH);
    }
    digitalWrite(Y_motor1,LOW);
    digitalWrite(Y_motor2,LOW);
    break;
  }
 }

 Serial.println("Y 終了");

  delay(300);

 Serial.println("アームを下ろしています...");

    digitalWrite(Z_motor1,HIGH);
    digitalWrite(Z_motor2,LOW);
    delay(4000);
    digitalWrite(Z_motor1,LOW);
    digitalWrite(Z_motor2,LOW);

Serial.println("アームを閉じています...");

digitalWrite(Arm_motor1,LOW);
digitalWrite(Arm_motor2,HIGH);

delay(200);

Serial.println("アームを閉じました");
Serial.println("アームを持ち上げています...");

  while(1){
  zl2 = digitalRead(Z_limit2);

  if(zl2 == 1){      //nolimit
      digitalWrite(Z_motor1,LOW);
      digitalWrite(Z_motor2,HIGH);
    }
    else{
      delay(500);
      digitalWrite(Z_motor1,LOW);
      digitalWrite(Z_motor2,LOW);
      break;
    }
  }

  Serial.println("アームを持ち上げました");
  Serial.println("元の位置に戻っています...");
  Serial.println("X Y 戻っています...");


    digitalWrite(X_motor1,HIGH);
    digitalWrite(X_motor2,LOW);
    digitalWrite(Y_motor1,HIGH);
    digitalWrite(Y_motor2,LOW);
  delay(2000);
    digitalWrite(X_motor1,LOW);
    digitalWrite(X_motor2,LOW);
    digitalWrite(Y_motor1,LOW);
    digitalWrite(Y_motor2,LOW);

Serial.println("X Y　リセット終了"); 
Serial.println("アームを開きます...");

delay(400);
//OPEN
digitalWrite(Arm_motor1,LOW);
digitalWrite(Arm_motor2,LOW);

Serial.println("プロセス終了。");
Serial.println("ゲーム終了"); //ここで一連の流れは終了。
}
/*while(1){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  duration /= 2;

  distance = duration * 340 * 100 / 1000000;

  Serial.println(distance);
  delay(100);
}*/
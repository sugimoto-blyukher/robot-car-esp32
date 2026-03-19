#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

const int IN1 = 23;
const int IN2 = 22;
const int IN3 = 0;
const int IN4 = 2;

#define ESP_MAC_BT 90 : 15 : 06 : 7C : 3D : C2

String cmd[5] = { "stop", "forward", "right", "left", "backward" };

char buffer[100];

String label = "stop";

const unsigned long frame_ms = 10;
unsigned long merc;        //フレーム管理時計
unsigned long curr;        //現在時刻
unsigned long curr_micro;  //現在時刻をマイクロ秒で取得する用
int framecount;            //現在フレーム何周期目かのカウンタ

int i;

void stop();
void forward();
void right();
void left();
void backward();

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
  SerialBT.begin("SPP-TEST");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (SerialBT.available()) {
    byte inBuf[1];
    SerialBT.readBytes(inBuf, 1);

    Serial.print((char)inBuf[0]);
    Serial.println("");

    //右旋回
    if (inBuf[0] == 'a') {
      SerialBT.println("right");
      Serial.println("right");
      right();
    }
    //左旋回
    if (inBuf[0] == 'd') {
      SerialBT.println("left");
      Serial.println("left");
      left();
    }
    //前進
    if (inBuf[0] == 'w') {
      SerialBT.println("w");
      Serial.println("w");
      forward();
    }
    //後退
    if (inBuf[0] == 'x') {
      SerialBT.println("w");
      Serial.println("w");
      backward();
    }
    //停止
    if (inBuf[0] == 's') {
      SerialBT.println("s");
      Serial.println("s");
      stop();
    }
  }

  int index = 0;
  bool hasData = false;

  while (Serial.available() > 0) {
    hasData = true;
    buffer[index] = Serial.read();
    index++;
    if (index >= 100) {
      break;
    }
  }

  //int* pindex = &index;

  buffer[index] = '\0';
  if (hasData == true) {
    label = buffer;
    label.trim();
  }
  /*
  if (label == cmd[0]) {
    stop();
  } else if (label == cmd[1]) {
    forward();
  } else if (label == cmd[2]) {
    right();
  } else if (label == cmd[3]) {
    left();
  } else if (label == cmd[4]) {
    backward();
  } else {
    Serial.println("Invalid command");
  }
*/
  delay(1000);
  Serial.println(label);
  /*

  curr = millis(); //現在時刻を取得
  if (curr > merc) {
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, LOW);
  } else {
    return;
  }
  framecount = framecount + 2;
  if (framecount > 10000) {
    framecount = 0;
  }

  curr = millis(); //現在時刻を取得
  curr_micro = micros(); //現在時刻をマイクロ秒で取得する用
  while (curr < merc) {
    curr = millis(); //現在時刻を取得
  }

  merc += frame_ms;

*/
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

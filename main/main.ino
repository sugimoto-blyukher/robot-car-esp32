#include "BluetoothSerial.h"
#include <Ps3Controller.h>

const int IN1 = 23;
const int IN2 = 22;
const int IN3 = 0;  
const int IN4 = 2;  

int battery = 0;

String cmd[5] = { "stop", "forward", "right", "left", "backward" };

char buffer[100];

void stopMotor();
void forward();
void right();
void left();
void backward();
void onConnect();
void onDisconnect();
void notify();

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisconnect);
  Ps3.begin("90:15:06:7c:3d:c2");
}

void loop() {
  // 切断中は必ず停止
  if (!Ps3.isConnected()) {
    stopMotor();
    delay(20);
    return;
  }

  // 押している間だけ動く
  if (Ps3.data.button.up) {
    forward();
  } else if (Ps3.data.button.right) {
    left();
  } else if (Ps3.data.button.down) {
    backward();
  } else if (Ps3.data.button.left) {
    right();
  } else if (Ps3.data.button.circle) {
    stopMotor();
  } else {
    // 何も押されていなければ停止
    stopMotor();
  }

  delay(20);
}

void stopMotor() {
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

void onConnect() {
  Serial.println("Connected.");
}

void onDisconnect() {
  Serial.println("Disconnected.");
  stopMotor();
}

void notify() {
  if (battery != Ps3.data.status.battery) {
    battery = Ps3.data.status.battery;
    Serial.print("The controller battery is ");

    if (battery == ps3_status_battery_charging) Serial.println("charging");
    else if (battery == ps3_status_battery_full) Serial.println("FULL");
    else if (battery == ps3_status_battery_high) Serial.println("HIGH");
    else if (battery == ps3_status_battery_low) Serial.println("LOW");
    else if (battery == ps3_status_battery_dying) Serial.println("DYING");
    else if (battery == ps3_status_battery_shutdown) Serial.println("SHUTDOWN");
    else Serial.println("UNDEFINED");
  }
}

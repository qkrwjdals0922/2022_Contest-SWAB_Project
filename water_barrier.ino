//엑츄레이터(모터드라이버)
int motor_1 = 8;
int motor_2 = 7;
int motor_pwm = 9;
int btn = A3;
int btn_a = A8;
int sw = A7;
int btn_m = A15;
int piezo = 5;
//LED
int led_m = 12;
int led_a = 11;
//수,자동 전환변수
int state = 0;
int stateis = 0;
int stable = 0;
int j=1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
  pinMode(motor_pwm, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  pinMode(btn_a,INPUT_PULLUP);
  pinMode(btn_m,INPUT_PULLUP);
  pinMode(piezo, OUTPUT);
  analogWrite(motor_pwm, 0);
  pinMode(sw, INPUT);
  pinMode(led_m, OUTPUT);
  pinMode(led_a, OUTPUT);
  
  setLight(LOW, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // 수,자동별 작동
  Serial.println("start");
  int autobt = analogRead(btn_a);
  int manual = analogRead(btn_m);
  if(manual <= 500){
    Serial.println("mode::manual");
    setLight(HIGH, LOW);
    Serial.print(stateis);
    Serial.print("::");
    Serial.println(state);
    piezosound();

    ActuatorManualOperation();
   } else if(autobt <= 500) {
     Serial.println("mode::auto");
    auto_btn();
    setLight(LOW, HIGH);
    if(analogRead(btn) >= 1000) {
      digitalWrite(motor_1, LOW);
      digitalWrite(motor_2, HIGH);
      analogWrite(motor_pwm, 255);
      
    }
   }
    else if(autobt >=500 && manual >= 500 ){
      Serial.println("mode::neutrality");
      setLight(HIGH,HIGH);
    }

}

// 엑츄레이터 버튼별 작동 코드
void ActuatorManualOperation() {
  Serial.println(analogRead(btn));
  int al = analogRead(btn);
  if(al >= 500){
    Serial.print("state::down::");
    state = 2;
    Serial.println(state);
    digitalWrite(motor_1, LOW);
    digitalWrite(motor_2, HIGH);
    analogWrite(motor_pwm, 255);
    
  } else if(al <= 500){
    Serial.println("state:🆙:");
    stateis = 1;
    Serial.println(state);
    digitalWrite(motor_1, HIGH);
    digitalWrite(motor_2, LOW);
    analogWrite(motor_pwm, 255);
  }
  return;
}

// 수동,자동 전환 표시등
void setLight(int m, int a) {
  digitalWrite(led_m, m);
  digitalWrite(led_a, a);
}

void auto_btn() {
  Serial.println(analogRead(sw));
  delay(100);
  bool wa2 = false;
  int wa = analogRead(sw);
  if(wa <= 165){
    piezosound_auto();
    j=2;

    digitalWrite(motor_1, HIGH);
    digitalWrite(motor_2, LOW);
    analogWrite(motor_pwm, 255);
    j=2;
  }
    }


void piezosound() {
  if(state == 2 && stateis == 1){
    for (int i = 0; i <= 1; i++){ // 사이렌 반복
      for (int i =262; i <= 523; i++){ //부저 사이렌  
        tone(piezo, i);
        delay(10);
      }
      for (int i = 523; i >= 262; i--){ // 부저 사이렌 소리
        tone(piezo, i);
        delay(10);
      }
      if(state == 1 && stateis == 1) {piezostop1();return;}
      piezostop();
      
      delay(500);
   }

   }
   Serial.println("state::piezon::end");
   return;
}
void piezostop() {
  noTone(piezo);
  state = 1;
  return;
}
void piezostop1() {
  noTone(piezo);
  stateis = 0;
  return;
}
void piezosound_auto(){
    j =1;
  switch(j){
  case 1:
      for (int i = 0; i <= 1; i++){ // 사이렌 반복
      for (int i =262; i <= 523; i++){ //부저 사이렌  
        tone(piezo, i);
        delay(10);
      }
       for (int i = 523; i >= 262; i--){ // 부저 사이렌 소리
        tone(piezo, i);
        delay(10);
      }
      noTone(piezo);
}break;
case 2:
noTone(piezo);
break;
  }
}
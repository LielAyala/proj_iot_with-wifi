#define LdrPin A0
#define LedPin D2

int LdrVal;
int LedVal;
int MapDir=1;
void setup() {
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT);
  WifiSetup();
}

void loop() {
  LdrVal = analogRead(LdrPin);
  //הדפסה של המטח 
  Serial.println(LdrVal);
  //זה יחס שאנחנו מקבלים ורוצים להמיר את המערכים מ 0 ל255
  if(MapDir == 1){
    LedVal=map(LdrVal,0,1023,0,255);
  } else {
    LedVal=map(LdrVal,0,1023,255,0);
  }
  analogWrite(LedPin,LedVal);
  wifi_loop();
}

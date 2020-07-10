#define BAUD 9600
#define DELAY_TIME 20

String DataToSend;
String Delim = ",";

byte Xpin = A0;
byte Ypin = A1;
byte SWpin = 7;
//byte CTRLpin = 2;

int Xpos = 0;
int Ypos = 0;
bool SWstate = 0;
//bool CTRLstate = 0;

void setup() {
  Serial.begin(BAUD);
  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  pinMode(SWpin, INPUT_PULLUP);
  //pinMode(CTRLpin, INPUT_PULLUP);
}

void loop() {
  Xpos = analogRead(Xpin);
  Ypos = analogRead(Ypin);
  SWstate = digitalRead(SWpin);
  //CTRLstate = digitalRead(CTRLpin);

  DataToSend = String(Xpos)+Delim+String(Ypos)+Delim+String(SWstate)+"\n";
  Serial.print(DataToSend);
  delay(DELAY_TIME);
}

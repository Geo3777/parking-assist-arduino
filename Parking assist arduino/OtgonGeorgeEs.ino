 
#include <LiquidCrystal_I2C.h>//libraria ecranului lcd
#include <Encoder.h>//libraria encoderului
LiquidCrystal_I2C lcd(0x27,20,4);//setarile prestabilite a ecranului

//senzor
const int trigPin = 9;//introducem pinul trig in pinul digital 9 a placii Arduino
const int echoPin = 10;//introducem pinul Echo in pinul digital 10 a placii Arduino
double duration;//durata in care calatoreste ultrasunetul
double distance;//distanta calculata


//encoder
Encoder myEnc(2, 3);//Legam encoderul la pinurile digitale 2 si 3 ale placii
double distance_set=5;//distanta prestabilita de la care sa ne alerteze dispozitivul

//led
//Legam ledul la pinurile digitale 6 si 7 ale placii
int led1 = 6; 
int led2 = 7; 


//buzzer
int buzzer = 8;//Legam buzzerul la pinul digital 8 a placii

void setup() {
//senzor
pinMode(trigPin, OUTPUT);//trigPin emite sunetul, deci este output 
pinMode(echoPin, INPUT); //echoPin ne da durata in care calatoreste ultrasunetul, deci este input

//led este output
pinMode(led1, OUTPUT); 
pinMode(led2, OUTPUT);

//buzzer emite sunet, deci este output
pinMode(buzzer, OUTPUT);


//lcd
lcd.init();//initializam lcd-ul
//lcd.backlight();
}


void loop() {
//lcd //afisam pe randul 1 distanta setata de encoder
lcd.setCursor(0,0);
lcd.print("distanta 1:");
lcd.print(distance_set);
//afisam pe randul 2 distanta citita de senzor
lcd.setCursor(0,1);
lcd.print("distanta 2:");
lcd.print(distance);

//senzor// trigpin emite sunet,iar echopin ne returneaza durata calatoriei dus-intors a sunetului
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;//distanta=timp*viteza_sunetului(/2 deoarece echopin citeste dus-intors)
delay(400);

//encoder
double newPosition = myEnc.read();//Encoderul citeste constant daca a fost miscat
  if (newPosition != distance_set) {
    distance_set = newPosition;// daca a fost miscat schimbam valoarea distantei setate
  }

//led si buzzer
if(distance<=distance_set){//daca distanta citita de senzor este mai mica decat cea setata pe encoder
  digitalWrite(led1, HIGH);//ledul se face rosu
  digitalWrite(led2, LOW);
  digitalWrite(buzzer,LOW);//porneste buzzerul(buzzerul porneste cand este pe low)
}
else if(distance>distance_set){//daca distanta citita de senzor este mai mare decat cea setata pe encoder
  digitalWrite(buzzer,HIGH);//se opreste buzzerul(buzzerul porneste cand este pe low)
  digitalWrite(led2, HIGH);//ledul se face verde
  digitalWrite(led1, LOW);
}
}

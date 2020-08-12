int s[5];
void setup() {
  // put your setup code here, to run once:
pinMode(6,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(4,INPUT);
 pinMode(5,INPUT);
 pinMode(7,INPUT);
Serial.begin(9600);
}

void loop() {
  s[0]=digitalRead(2);
     s[1]=digitalRead(3);
     s[2]=digitalRead(4);
     s[3]=digitalRead(5);
     s[4]=digitalRead(7);
 Serial.print(s[0]);
 Serial.print(s[1]);
 Serial.print(s[2]);
 Serial.print(s[3]);
 Serial.print(s[4]);
 Serial.println("done");
 Serial.println("");
if(s[0]==0 && s[1]==0 && s[2]==0 && s[3]==0 && s[4]==0)
{
digitalWrite(6,0);
digitalWrite(8,1);
digitalWrite(10,1);
digitalWrite(12,0);
analogWrite(9,130);
analogWrite(11,130);
}
else
 {digitalWrite(6,1);
 digitalWrite(8,0);
 digitalWrite(10,1);
 digitalWrite(12,0);
 analogWrite(9,90);
 analogWrite(11,90);
 }
}

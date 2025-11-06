void setup(){
pinMode(11, OUTPUT);
pinMode( 10, OUTPUT );
}

void loop(){
 digitalWrite(10,HIGH);
delayMicroseconds(9500);
digitalWrite(10,LOW);
delayMicroseconds(500);
digitalWrite(11,HIGH);
delayMicroseconds(9500);
digitalWrite(11,LOW);
delayMicroseconds(500);

}

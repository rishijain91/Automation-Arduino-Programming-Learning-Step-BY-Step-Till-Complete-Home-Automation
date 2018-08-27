long x,y;
int flag=0;
void setup(){
Serial.begin(9600);

}
void loop(){
//Serial.println(millis());
if(flag==0){
x=millis();
flag=1;
y=x+2000;
}
if(y<=millis()){
Serial.println("Hello");
flag=0;
}
//delay(2000);

}

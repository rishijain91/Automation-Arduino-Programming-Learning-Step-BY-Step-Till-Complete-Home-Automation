long x,y;
int signal=0;
int flag=0;
void setup(){
Serial.begin(9600);
pinMode(4,OUTPUT);
pinMode(8,INPUT);
}
void loop(){
signal=digitalRead(8);
if(signal==1){
  if((x+10000)<=millis() || flag==0){
   x=millis();
   y=x+15000;
  }
  
  if(flag==0){
    
   Serial.println("LOW");
   digitalWrite(4,LOW);
   flag=1;  
}

}else{
 //  Serial.println("LOW");
 if(y<=millis()){
 digitalWrite(4,HIGH);  
 flag=0;
 }
}
}

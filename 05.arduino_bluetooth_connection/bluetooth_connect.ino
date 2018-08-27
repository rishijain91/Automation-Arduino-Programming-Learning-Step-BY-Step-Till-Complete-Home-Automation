#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10,11);
 String s;
char arr[20];
int i=0;
void setup(){
  Serial.begin(9600);
  Serial.println("Setup Started");
  
  BTSerial.begin(38400);
}
void loop(){
 
  if(BTSerial.available()){
    
  arr[i]=BTSerial.read();
   //Serial.write(arr[i]);
 if(arr[i]!=',')
 {
   i++;
 }else{
int j=0;
 char ss[4]; 
for(j=0;j<i;j++)
{
  s+=arr[j];
  
 
} if(s=="hello"){
   Serial.println("hello world");
   BTSerial.write("hello world");
}else{
 Serial.println(s);//Serial.write(ss);
 }  
 }
/*

  if(arr=="hello"){
    Serial.write("hello World");
  }else{
  */  // Serial.write(BTSerial.read());
  //}
  }
 
  if(Serial.available()){
    
    BTSerial.write(Serial.read());
}
}

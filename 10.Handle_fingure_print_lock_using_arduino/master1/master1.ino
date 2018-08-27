// Include the required Wire library for I2C<br>#include 

#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial123(4,5); // RX | TX
//int x = 0;


long int hexToDec(String hexString) {
  //Serial.println("I am Here");
  long int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);  //map function long map(long x, long in_min, long in_max, long out_min, long out_max){ 
                                                                                // return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);    
    decValue = (decValue * 16) + nextInt;
  }
  return decValue;
}

char TestArray[12];
int j=0; 
int v=0;
int x=0; 
void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
  Serial.begin(9600);
  mySerial123.begin(9600);  // HC-05 default speed in AT command more
}
void loop() {
                     if(mySerial123.available())
                           {
                               TestArray[v] = mySerial123.read(); 
                                v++; 
                                if(v==12) 
                                    {
                                           String p;
                                           String abc; 
                                           String strone,pq;
                                           long ppp;
                                           int qqq;
                                                      {
                                                        j=3;
                                                                  while(j<10)
                                                                     {
                                                                        p+=(TestArray[j]);
                                                                        j++; 
                                                                     }          
                                                                   
                                                                    ppp=hexToDec(p);
                                                                    char temp[10];
                                                                    ltoa(ppp,temp,10);
                                                                     //////////////////////////////////////////////////////////////
                                                                     //Serial.println(p);
                                                                      Wire.beginTransmission(9); // transmit to device #9
                                                                      Wire.write(temp);              // sends x 
                                                                      Wire.endTransmission();    // stop transmitting
                                                                     //////////////////////////////////////////////////////////////
                                                                     Serial.println(temp);
                                                                    memset(TestArray,'\0',10); //clears the input array
                                                         } 
                                                                  v=0; 
                                                                  j=0;
                                                        }
                                                        
                                   }
  
}
         

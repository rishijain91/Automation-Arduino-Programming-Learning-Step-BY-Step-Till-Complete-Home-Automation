#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>
#include <Wire.h>

SoftwareSerial BTSerial(4,5); // RX | TX

uint8_t id;

SoftwareSerial mySerial(2,3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//as Connection RX=11 TX=10 in Declaration They are opposite RX=10 and TX=11

//int a;      

char TestArray1[100];
char Btkey;
int j=0;
int h=0;
String q;

String str;

char sub[20];

int result[20];

//int position1, length;    
/////////////////////////// Search ////////////

char bufferid[20]; 
////////////////////////////Enroll/////////////
char bufferenroll[4];
 unsigned long loopStart;
unsigned long p_current_milli;
 unsigned long loopStart1;
unsigned long p_current_milli1;
////////////////////////////Delete//////////////////
uint8_t delid;
char bufferdel[4];

//////////////////////////// RFID RC522 ///////////

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 6
#define RESET_DIO 5

/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 

char bufferrc[20];

////////////////////////// RFID ///////////////////

String data="";
char bufferrfid[20];


int flag1234=0;

////////////////////////// Bluetooth Setting//////////////////
char bufferblue[20];
char buffer123[4];
/////////////////////////////////////////////////////////////


///////////////////////// Motor On/Off //////////////////////
int flagmo=0;
int flagmo1=0;
unsigned long pmo;
unsigned long waitTimemo;
unsigned long waitTimemo1;

unsigned long testmillis;
unsigned long testmillis1;
int op;

int counter_test;
char c_test[20];
/////////////////////////////////////////////////////////////

const int switchPin = 52;

///////////////////////////////////////////////////////////////
int flag_mag1=0;
int flag_mag=0;
//////////////////////////////////////////////////////////////
///////////////////////////////////////////////// Void Setup() Start //////////////////////////////////////////
void setup()
{ 
  pinMode(8, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(8, LOW);
  Serial.begin(9600);
  
  pinMode(switchPin, INPUT);
  digitalWrite(switchPin,HIGH);
 
  
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  
  BTSerial.write("h");
  
  finger.begin(57600);
  if (finger.verifyPassword()) 
  {
    Serial.println("Found fingerprint sensor!");
    BTSerial.write("Found fingerprint sensor!");
  }
  else{
    Serial.println("Did not find fingerprint sensor :(");
    BTSerial.write("Did not find fingerprint sensor :(");
    //while (1);
  }
  
  Wire.begin(9); 
 
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init(); 
 
 ///////////////////// Magnetic switch//////////////////////// 
 
}

void loop()
{

  ////////////////////////////////  Magnetic Switch  ///////////////////////////////////////

               if((digitalRead(switchPin) == 1) && flag_mag==0)
                   {
                     
                     //Serial.println("Open");
                       flag_mag=1;
                       flag_mag1=0; 
                       for(int z=0;z<=3;z++)
                        {
                       Serial.println("Lock Open");
                        BTSerial.write("Lock Open");  
                       }  
                   }
               else if((digitalRead(switchPin) == 0) && flag_mag1==0)
                    {
                        //Serial.println("Close");
                      flag_mag1=1; 
                      flag_mag=0; 
                      for(int z1=0;z1<=3;z1++)
                          {
                            Serial.println("Lock Close");
                            BTSerial.write("Lock Close");  
                           }    
                    }     
     
  ////////////////////////////  Motor On/Off  /////////////////////////////////////////////
  
  pmo=millis();
  if(flagmo==1)
  {
    counter_test++;
    itoa(counter_test,c_test,10); 
    BTSerial.write(c_test);
     BTSerial.write("MOTOR ON");
     digitalWrite(op,HIGH);
     Serial.println("Pin High");
     waitTimemo=pmo+4000;
     waitTimemo1=pmo+6000;
     
     
     flagmo=0;
     flagmo1=1;
  }
  if(flagmo1==1)
  {
    if(pmo<=waitTimemo)
     {
       Serial.println(op);
       testmillis=millis();
       digitalWrite(op,LOW);
       Serial.println("Pin Low");
       unsigned long testmillis;
       delay(30);
       testmillis1=millis();
       digitalWrite(op,HIGH);
       Serial.println("Pin High");         
       Serial.println(testmillis1);
      
     }
  
  if(pmo>waitTimemo)
  {
    digitalWrite(op,LOW);
    Serial.println("pin Low");

   

    //flagmo=0;
  }
  
  if(pmo>waitTimemo1)
   {
      
       flagmo=0;
       flagmo1=0;
   }  
  }
  /////////////////////////////////////////////////////////////////////////////
  
  digitalWrite(8,LOW);
  //delay(50);  
  if(flag1234==0)
   { 
   mySerial.listen();  
   int finger123=getFingerprintID();
   if(finger123==13)
     {
       int fing_id=getFingerprintIDez();  
       if(fing_id==-1)
         {     Serial.println("Sorry Not a Valid Finger");
               BTSerial.write("Sorry Not a Valid Finger");
         }
     }
   }
 delay(80);
 BTSerial.listen();
  //delay(150);
  delay(150);
  if (BTSerial.available())
  {
       // Serial.println("I am here");
       Btkey=BTSerial.read();
       Serial.println(Btkey);
       if(Btkey)
       {
          flag1234=1;
          TestArray1[j]=Btkey;
          j++;
          if(Btkey=='#') 
           {
             str=TestArray1;
             memset(TestArray1, 0, sizeof(TestArray1)); 
             int p=str.length();

             //j=0;
      ///////////////////////////////////////////////////
            
         h=0;   
         for (int i = 0; str[i] != '\0'; i++) {
              if (str[i] == 'a')
              {
                    result[h]= i+1;
                    //Serial.println(result[h]);
                    h++;
              }                            
          }

          // Serial.println(str);
          int sizeofh=h-1;
          // Serial.println(sizeofh);
        
          for (int m = 0;m<sizeofh; m++) {    
              int c=0;
   
             // Serial.println(result[m]);
             // Serial.println(result[m+1]);
              
              int position1=result[m];
              int length=result[m+1];    
              
              while (position1 < length) {
                 sub[c] = str[position1];
                 c++;
                 position1++;
                }
              sub[c]='\0';
              Serial.println(sub);
              
              Serial.println("substring");
              
              ////////////////////////////////////////// Lock Pin High/Low ////////////////////////////
              
              if(sub[0]=='1')
                 {
                        Serial.println("OutPut");
                        Serial.println(sub[1]);
                        Serial.println(sub[2]);                        
                        
                        char buffer[2];
                        buffer[0]=sub[1];
                        buffer[1]=sub[2];
                        buffer[2] = '\0';
                        Serial.println(buffer);
                        op=atoi(buffer);
                        
                        pinMode(op, OUTPUT);                        
                         if(sub[3]=='1')
                             {
                                  //digitalWrite(op, HIGH);    
                                  //Serial.println("OutPut pin High");    
                                  //BTSerial.write("OutPut pin High");   
                                   flagmo=1;
                                   
                             }
                         else if(sub[3]=='0')    
                             {
                                 digitalWrite(op, LOW);      
                                 Serial.println("OutPut pin LOW"); 
                                 //BTSerial.write("OutPut pin LOW");    
                             }
                 }
                 
                //////////////////////////////////////Enroll And Delete Fingerprint ////////////////// 
                if(sub[0]=='e') 
                  {
                        Serial.println("Enroll");
                        Serial.println(sub[1]);
                        Serial.println(sub[2]);
                        Serial.println(sub[3]); 
                        
                        bufferenroll[0]=sub[1];
                        bufferenroll[1]=sub[2];
                        bufferenroll[2]=sub[3];
                        bufferenroll[3] = '\0';
                        Serial.println(bufferenroll);
                        int enroll=atoi(bufferenroll);                        
                        
                        //////////////////////////////////////////Enroll
                        id = enroll;
                        Serial.print("Enrolling ID #");
                        Serial.println(id);
                        mySerial.listen();  
                        delay(20);       
                        int e_id=getFingerprintEnroll(); 
                        
                        if(e_id==9)
                           {
                              Serial.println("Successfully Enrolled");
                              BTSerial.write("Successfully Enrolled");
                           }
                           else
                           {
                              Serial.println("Not Enrolled");
                              BTSerial.write("Not Enrolled");
                           }
                        
                  }
                else if(sub[0]=='d') 
                  {
                        Serial.println("Delete");
                        Serial.println(sub[1]);
                        Serial.println(sub[2]);
                        Serial.println(sub[3]);   
                        
                        bufferdel[0]=sub[1];
                        bufferdel[1]=sub[2];
                        bufferdel[2]=sub[3];
                        bufferdel[3] = '\0';
                        Serial.println(bufferdel);
                        int del=atoi(bufferdel);   
                       ///////////////////////////////////////////////Delete///////////////////////////////////
                       mySerial.listen();  
                       delay(20);       
                       int load_id=loadmodel(del);
                       Serial.println(load_id);
                        if(load_id==9)
                                { 
                                     Serial.println(del);
                                     Serial.println(deleteFingerprint(del));
                                }
                        else   
                               {
                                       Serial.println("Sorry You Entered Number not available");
                                       BTSerial.write("Sorry You Entered Number not available");
                               }       
                    }
             else if(sub[0]=='o')
                 {
                    Serial.println(sub[0]);
                    Serial.println("Hello");
                    delay(500);
                    digitalWrite(8,HIGH);
                    delay(100);
                    BTSerial.write("AT+ORGL"); 
                    BTSerial.write("\r\n");  
                    delay(100);
                    BTSerial.write("AT+RMAAD");  
                    BTSerial.write("\r\n");  
                    delay(100);
                    digitalWrite(8,LOW);
                 }
                    
             else if(sub[0]=='c')
                 {
                        Serial.println("OutPut"); 
                        Serial.println(sub[1]); 
                        Serial.println(sub[2]);                        
                        
                      
                        buffer123[0]=sub[1];
                        buffer123[1]=sub[2];
                        buffer123[2]=sub[3];
                        buffer123[3]=sub[4];
                        buffer123[4] = '\0';
                        
                        Serial.println(buffer123);
                        
                           digitalWrite(8,HIGH);
                           delay(100);
                           //str.toCharArray(bufferrfid,20);
                           BTSerial.write("AT+PSWD=");
                           BTSerial.write(buffer123);  
                           BTSerial.write("\r\n");  
                           delay(50);
                           BTSerial.write("AT+RMAAD");  
                           BTSerial.write("\r\n");  
                           delay(50);
                           digitalWrite(8,LOW);
                           
                           BTSerial.write("Successfully Password Change");  
                 }
                 
      
                    ////////////////////////////////////////    
        }  
              
              //////////////////////////////// 
             TestArray1[j]='\0'; 
             j=0;
             flag1234=0;
             str="";
             Btkey='\0';
            
            }
            
             // flag1234=0;                
        
            
         }
      }
      ///////////////////////////////// Bluetooth Code Ended ///////////////////////////////////
      
  
  
     
      ////////////////////////////////  RFID RC255 /////////////////////////////////////////////
      
       byte k;
              if (RC522.isCard())
                    {
                        RC522.readCardSerial();

                        Serial.println("Card detected:");

                          for(k = 0; k <= 4; k++)
                                {
                                    Serial.print(RC522.serNum[k],HEX);
                                    itoa(RC522.serNum[k],bufferrc,16);       
                                    BTSerial.write(bufferrc);  
                                    Serial.print(" ");
                                }
                          Serial.println();
                          Serial.println();
                      }     
      ////////////////////////////////   RFID  /////////////////////////////////////////////////
      
      Wire.onReceive(receiveEvent);
      
  }
/////////////////////////////////////// Void Loop() Ended /////////////////////////////////////// 

///////////////////////////////////// RFID RC255 ////////////////////////////////////////////////




  
////////////////////////////////////// RFID ////////////////////////////////////////////////////


void receiveEvent(int bytes) {
// x = Wire.read();    // read one character from the I2C
//  Serial.print(x);
 data = "";
  while( Wire.available()){
    data += (char)Wire.read();
  }
  Serial.println(data);
  data.toCharArray(bufferrfid,20);
  BTSerial.write(bufferrfid); 
 // BTSerial.write(data);
}  

/////////////temp///
int temp() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

 Serial.print("Found ID #"); Serial.print(finger.fingerID); 
// BTSerial.write("Found ID #"); 
// itoa(finger.fingerID,bufferid,10);       
// BTSerial.write(bufferid);  
//  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
////////////////////
  
/////////////////////////////////////// Searching ////////////////////////////////////////////////

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
 Serial.print("Found ID #"); Serial.print(finger.fingerID); 
 BTSerial.write("Found ID #"); 
 itoa(finger.fingerID,bufferid,10);       
 BTSerial.write(bufferid);  
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}



/////////////////////////////////////////////For finger press or not ///////////////////////////
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println("No finger Detected");        
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
}



//////////////////////////////////////// Enroll //////////////////////////////////////////////////
uint8_t getFingerprintEnroll() {
  int flager=0;
  int flagenroll=0;
unsigned long waitTime1;
unsigned long waitTime;
int flag2=0;
int flag1=0;

  if(flag2==0)
  {
  loopStart1=millis();
 // Serial.println(loopStart1);
  waitTime1 = loopStart1 + 3000;  
 // Serial.println(waitTime1);
  flag2++;
  }
  
  p_current_milli1=millis(); 
   // Serial.println(p_current_milli1);
    
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  BTSerial.write("Put Your Finger");
  while (p != FINGERPRINT_OK) {
    p_current_milli1=millis(); 
  //  Serial.println(p_current_milli1);
    p = finger.getImage();
    
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      flagenroll=1;
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
    
      if(p_current_milli1>=waitTime1 && flag2==1)
      {
          flag2=0;
          break;
      }
  
  }
  
  // OK success!
 if(flagenroll==1)
 {
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  Serial.println("Remove finger");
  //delay(2000);
  p = 0;
 // while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  //}
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  if(flag1==0)
  {
  loopStart=millis();
 // Serial.println(loopStart);
  waitTime = loopStart + 3000;  
 // Serial.println(waitTime);
  flag1++;
  }
  
  p_current_milli=millis(); 
  Serial.println(p_current_milli);
  
  while (p != FINGERPRINT_OK) {
     p_current_milli=millis(); 
 //   Serial.println(p_current_milli);
    p = finger.getImage();    
    
     if(p_current_milli>=waitTime && flag1==1)
      {
          flag1=0;
          break;
      }
    
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      flager=1;
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");      
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
    //flag1=0;
  }
  // OK success!
  if(flager==1)
  {
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p; 
  }   
  }
  else
  {
  Serial.println("Stop");
  }
 }
 else
  {
    Serial.println("Sorry Your Finger is not pressed");
    BTSerial.write("Sorry Your Finger is not pressed");
  }
}  

/////////////////////////////////////////////////Delete/////////////////////////////////////////////////////////////////

uint8_t loadmodel(uint8_t delid) {
  int p = -1;
 // p = finger.deleteModel(delid);
 Serial.println(delid);
  p=finger.loadModel(delid);
  if (p == FINGERPRINT_OK) {
    Serial.println("Loaded!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
}

uint8_t deleteFingerprint(uint8_t delid1) {
  uint8_t p = -1;
  Serial.println(delid1);
  p = finger.deleteModel(delid1);
  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
    BTSerial.write("Successfully Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
}


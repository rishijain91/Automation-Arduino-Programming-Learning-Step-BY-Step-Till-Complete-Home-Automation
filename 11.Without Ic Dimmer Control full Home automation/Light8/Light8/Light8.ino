#include <SoftwareSerial.h>
#include <Keypad.h>

SoftwareSerial BTSerial(12,13); // RX | TX  Cross pin for arduino, arduino 12 -> bluetooth tx,arduino 13 -> bluetooth rx 

char TestArray1[100];       
//char Btkey;
int j=0;
int h=0;
String q;

unsigned long p_current_milli;
unsigned long loopStart;
unsigned long waitTime;

String str;

//char sub[20];

int result[20];

int ip_1;
int op_1;

//int flag=0;
//////////////////

int in_pin_result=0;

/////////////////////// Keypad ////////////////////

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'3','4','5','H'},
   {'6','7','8','P'},
  {'B','C','D','Z'},
   {'*','+','#','D'}
};
byte rowPins[ROWS] = {6,5,4,3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10,9,8,7}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int flag3=0;
int flagH=0;
int flag4=0;
/////////////////////////////////////

int bluetooth_switch_reset=0;

////////////////////////////////////////////////// Dimmer ///////////////////////////

///////////////////////  How many Dimmer You Want ////////////////////////

int dimmercount=5;

//////////////////////////////////////////////////////////////////////////

////////////////  changes in array for how many dimmer You want ///////////////////////

byte b[5]={};

////////////////////////////////////////////////////////////////////////////////////////

 //int pins[]={3,7,9};
 int pins[]={A1,A2,3,4,5};  // pin declaration first in array
 //long dim_time;
 
 ////////////////  changes in array for how many dimmer You want ///////////////////////
 
 int pos[5]={};
 int pos1[5]={};
 
 int duplicate[5]={};
 int duplicate1[5]={};
 
 ///////////////////////////////////////////////////////////////////////////////////////

long dimtime=0;
long dimtime1=0;
//long cal=0;
int flag_zc=0;

int dimming=1;
int dimming1=1;
int dimming2=1;
int dimming3=1,dimming4=1;

long cal=0;
long cal1=0;

/////////////////////// Dimmer Variable //////////////////////////////////

int fandimmercount1=0;
int fandimmercount2=0;
int fandimmercount3=0;

//////////////////////////////////////////////////////////////////////////

void setup()
 { 
  //pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  //digitalWrite(9,LOW);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  
    for(int t=0;t<dimmercount;t++)                     // For Dimmer Pin Initialization
     {
        pinMode(pins[t],OUTPUT);           
        digitalWrite(pins[t],LOW);
     }
     
  attachInterrupt(0, zero_crosss_int, RISING);            // Zero Crossing Signal Detection
  
  BTSerial.write("h");                                    // Hardware Reset send bluetooth
  
//  pinMode(3,INPUT); 
//  digitalWrite(3,LOW);
//
//  pinMode(2,OUTPUT); 
//  digitalWrite(2,HIGH);
  
  pinMode(A0,OUTPUT);
  digitalWrite(A0,LOW);
  
  pinMode(A4,OUTPUT);
  digitalWrite(A4,LOW);
  
 }
 
 void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{     
  
 flag_zc=1;
} 
 
 
///////////// A3 pin is used for reset purpose. Do not use A3 pin for other purpose ////////////////////////////////////////// 
 
void loop()
 {
    //digitalWrite(9,LOW);
    ///////////////////////////////////////////////////////////////////////////////    
      
    char customKey = customKeypad.getKey();           // Which Key pressed store in char
    
    if (customKey){                                
          Serial.println(customKey);
    }
    
    /////////////////////////////////////////////////////
    
    if(customKey=='3' && flag3==0)                       // If 3 key pressed then what action you want to take
     {
        Serial.println("A0 ON");
        digitalWrite(A0,HIGH);
        BTSerial.write("1A01;"); 
        flag3=1;
     }
    else if(customKey=='3' && flag3==1)                  // Again,If 3 key pressed then what action you want to take
     {
        Serial.println("A0 OFF");
        digitalWrite(A0,LOW);
        BTSerial.write("1A00;"); 
        flag3=0;                                          // Reset Flag
     }   
     
     /////////////////////////////////////////////////// Same as Above 
     
      if(customKey=='4' && flag4==0)
     {
        Serial.println("A4 ON");
        digitalWrite(A4,HIGH);
        BTSerial.write("1A41;"); 
        flag4=1;
     }
    else if(customKey=='4' && flag4==1) 
     {
        Serial.println("A4 OFF");
        digitalWrite(A4,LOW);
        BTSerial.write("1A40;"); 
        flag4=0;
     }   
     
     ///////////////////////////////////////////////////
     
     
     
     
     ///////////////////////////////////////////////////
     
     
     
     
     // Fan 
     
//    if(customKey=='3' && flagH==0)
//     {
//        Serial.println("11 ON");
//        //digitalWrite(A0,HIGH);
//        //BTSerial.write("A0 HIGH"); 
//        dimming=14;
//        flagH=1;
//     }
     
     
   if(customKey=='B')                                   // Key pressed for dimmer  
     {
       fandimmercount1++;                       
        
       if(fandimmercount1==1)                           // fandimmercount1 variable increment,for dimmer level changes as per increment     
         {
            dimming=128;                                // and set multiple dimming level in dimming variable
            BTSerial.write("yB128;"); 
            Serial.println("128");
         }
       if(fandimmercount1==2)
          {
             dimming=95;
             BTSerial.write("yB95;"); 
             Serial.println("95");
          }  
       if(fandimmercount1==3)   
          {
             dimming=76;
             BTSerial.write("yB076;"); 
             Serial.println("076");
          }
        if(fandimmercount1==4)
          {
             dimming=50;
             BTSerial.write("yB050;"); 
             Serial.println("050");
          }
        if(fandimmercount1==5)
          {
             dimming=26;
             BTSerial.write("yB026;"); 
             Serial.println("026");
          }  
        if(fandimmercount1==6)
         {
            dimming=2;
            BTSerial.write("yB002;"); 
            Serial.println("002");
         }  
        
        if(fandimmercount1>6)
          {
             fandimmercount1=0;
          } 
     }    
     
     
      if(customKey=='C')                     // Aame As Above
     {
        fandimmercount2++;
       
       if(fandimmercount2==1)
         {
            dimming1=128;
            BTSerial.write("yC128;"); 
            Serial.println("128");
         }
       if(fandimmercount2==2)
          {
             dimming1=95;
             BTSerial.write("yC95;"); 
             Serial.println("95");
          }  
       if(fandimmercount2==3)   
          {
             dimming1=76;
             BTSerial.write("yC076;"); 
             Serial.println("076");
          }
        if(fandimmercount2==4)
          {
             dimming1=50;
             BTSerial.write("yC050;"); 
             Serial.println("050");
          }
        if(fandimmercount2==5)
          {
             dimming1=26;
             BTSerial.write("yC026;"); 
             Serial.println("026");
          }  
        if(fandimmercount2==6)
         {
            dimming1=2;
            BTSerial.write("yC002;"); 
            Serial.println("002");
         }  
        
        if(fandimmercount2>6)
          {
             fandimmercount2=0;
          } 
     }    
     
   
    if(customKey=='D')                                             //  Same As Above  
     {
       fandimmercount3++;
       
       if(fandimmercount3==1)
         {
            dimming2=128;
            BTSerial.write("yD128;"); 
            Serial.println("128");
         }
       if(fandimmercount3==2)
          {
             dimming2=95;
             BTSerial.write("yD95;"); 
             Serial.println("95");
          }  
       if(fandimmercount3==3)   
          {
             dimming2=76;
             BTSerial.write("yD076;"); 
             Serial.println("076");
          }
        if(fandimmercount3==4)
          {
             dimming2=50;
             BTSerial.write("yD050;"); 
             Serial.println("050");
          }
        if(fandimmercount3==5)
          {
             dimming2=26;
             BTSerial.write("yD026;"); 
             Serial.println("026");
          }  
        if(fandimmercount3==6)
         {
            dimming2=2;
            BTSerial.write("yD002;"); 
            Serial.println("002");
         }  
        
        if(fandimmercount3>6)
          {
             fandimmercount3=0;
          } 
     }    
     
        
  byte a[]={dimming,dimming1,dimming2,dimming3,dimming4};            // Array for dimming.  
  
  //byte a[]={40,80,55,80};  
  
  ////////////////  changes in array for how many dimmer You want ///////////////////////
  
  byte c[5]={};                                    
  
  ///////////////////////////////////////////////////////////////////////////////////////
  
  for(int i=0;i<dimmercount;i++)                    // copy all a array values to c array.  
     {
         c[i]=a[i];
         //Serial.println(a[i]);
     }
     
     isort(a,sizeof(a));                            // Function for Sort Array in ascending order
     
    //////////////////////////////////////////////////////////////////////////////
      if (BTSerial.available())
    {                                               // For bluetooth Communication
       char Btkey;
       str="";
       Btkey=BTSerial.read();                       // Read Bluetooth in character variable
       Serial.println(Btkey);
       if(Btkey)                                      
       {
          //flag1234=1; 
          TestArray1[j]=Btkey;                       //  Take array for storing character
          j++;
          if(Btkey=='#')                               // packet ends with '#' 
           {   
             str=TestArray1;                             // copy array in string
             memset(TestArray1, 0, sizeof(TestArray1));   // reset memory of array , for garbage
             int p=str.length();                          // take string length  
             //j=0;
      ///////////////////////////////////////////////////
         h=0;   
         
         for (int i = 0; str[i] != '\0'; i++) {           // for multiple packets find a's location
              if (str[i] == 'a')
              {
                    result[h]= i+1;
                    //Serial.println(result[h]);
                    h++;
              }                            
          }

          // Serial.println(str);
           int sizeofh=h-1;                                // take count of a's location in packets
          // Serial.println(sizeofh);
         char sub[20];
          
          for (int m = 0;m<sizeofh; m++) {                 
              int c=0;
   
             // Serial.println(result[m]);
             // Serial.println(result[m+1]);              
              int position1=result[m];                      // take a's first position
              int length=result[m+1];                       // take a's next position
          
              while (position1 < length) {                  // collect data between a's position which is our packet
                 sub[c] = str[position1];
                 c++;
                 position1++;
                }
              Serial.println(c);                              
              sub[c]='\0';                               // do last array value null
             
              Serial.println(sub);                      
              Serial.println("substring");
                 
                //////////////////////////////////////Light On/Off load ////////////////// 
                if(sub[0]=='1')                           // If packet 0's position is 1 i.e means packet for Output pin
                  {
                    
                      if(sub[1]=='A')                                // Packet For Analog pin 
                          {
                                    Serial.println("Analog");
                                    //Serial.println(sub[3]);                                     
                                    if(sub[2]=='0')                  // Packet For A0 
                                       {
                                           pinMode(A0,OUTPUT);       
                                           if(sub[3]=='1')
                                              {                                                 
                                                    digitalWrite(A0,HIGH); 
                                                    Serial.write("High");
                                                    BTSerial.write("1A01;");                                                     
                                              }
                                            else if(sub[3]=='0')
                                              {                                                 
                                                    digitalWrite(A0,LOW); 
                                                    Serial.write("LOW");
                                                    BTSerial.write("1A00;"); 
                                              } 
                                       }
                                       
                                     if(sub[2]=='1')            // Packet For A1 
                                       {
                                           pinMode(A1,OUTPUT);       
                                           if(sub[3]=='1')
                                              {                                                 
                                                    digitalWrite(A1,HIGH); 
                                                    Serial.write("High");
                                                    BTSerial.write("1A11;"); 
                                              }
                                            else if(sub[3]=='0')
                                              {                                                 
                                                    digitalWrite(A1,LOW); 
                                                    Serial.write("LOW");
                                                    BTSerial.write("1A10;"); 
                                              } 
                                       }
                                     
                                     if(sub[2]=='2')            // Packet For A2 
                                       {
                                           pinMode(A2,OUTPUT);       
                                           if(sub[3]=='1')
                                              {                                                 
                                                    digitalWrite(A2,HIGH); 
                                                    Serial.write("High");
                                                    BTSerial.write("1A21;"); 
                                              }
                                            else if(sub[3]=='0')
                                              {                                                 
                                                    digitalWrite(A2,LOW); 
                                                    Serial.write("LOW");
                                                    BTSerial.write("1A20;"); 
                                              } 
                                       }
                                       
                                      if(sub[2]=='3')          // Packet For A3
                                       {
                                           pinMode(A3,OUTPUT);       
                                           if(sub[3]=='1')
                                              {                                                 
                                                    digitalWrite(A3,HIGH); 
                                                    Serial.write("High");
                                                    BTSerial.write("1A31;"); 
                                              }
                                            else if(sub[3]=='0')
                                              {                                                 
                                                    digitalWrite(A3,LOW); 
                                                    Serial.write("LOW");
                                                    BTSerial.write("1A30;"); 
                                              } 
                                       }
                                      
                                      if(sub[2]=='4')            // Packet For A4
                                       {
                                           pinMode(A4,OUTPUT);       
                                           if(sub[3]=='1')
                                              {                                                 
                                                    digitalWrite(A4,HIGH); 
                                                    Serial.write("High");
                                                    BTSerial.write("1A41;"); 
                                              }
                                            else if(sub[3]=='0')
                                              {                                                 
                                                    digitalWrite(A4,LOW); 
                                                    Serial.write("LOW");
                                                    BTSerial.write("1A40;"); 
                                              } 
                                       } 
                                       
                                     if(sub[2]=='5')            // Packet For A5 
                                       {
                                           pinMode(A5,OUTPUT);       
                                           if(sub[3]=='1')
                                              {                                                 
                                                    digitalWrite(A5,HIGH); 
                                                    Serial.write("High");
                                                    BTSerial.write("1A51;"); 
                                              }
                                            else if(sub[3]=='0')
                                              {                                                 
                                                    digitalWrite(A5,LOW); 
                                                    Serial.write("LOW");
                                                    BTSerial.write("1A50;"); 
                                              } 
                                       }  
                                       
                                     if(sub[2]=='6')           // Packet For A6
                                       {
                                           pinMode(A6,OUTPUT);       
                                           if(sub[3]=='1')
                                              {                                                 
                                                    digitalWrite(A6,HIGH); 
                                                    Serial.write("High");
                                                    BTSerial.write("1A61;"); 
                                              }
                                            else if(sub[3]=='0')
                                              {                                                 
                                                    digitalWrite(A6,LOW); 
                                                    Serial.write("LOW");
                                                    BTSerial.write("1A60;"); 
                                              } 
                                       }  
                                       
                                     if(sub[2]=='7')            // Packet For A7
                                       {
                                           pinMode(A7,OUTPUT);       
                                           if(sub[3]=='1')              
                                              {                                                 
                                                    digitalWrite(A7,HIGH); 
                                                    Serial.write("High");
                                                    BTSerial.write("1A71;"); 
                                              }
                                            else if(sub[3]=='0')
                                              {                                                 
                                                    digitalWrite(A7,LOW); 
                                                    Serial.write("LOW");
                                                    BTSerial.write("1A70;"); 
                                              } 
                                       }                                  
                              } 
                              else
                                {                                    // For Digital Pin
                    
                                    Serial.println(sub[2]);
                                    Serial.println(sub[3]); 
                                    
                                    char buffer_op[2];              // Take character Array
                                    buffer_op[0]=sub[1];
                                    buffer_op[1]=sub[2];
                                    //buffer_op[]=sub[3];
                                    buffer_op[2] = '\0';
                                    //Serial.println(buffer_op);
                                    
                                    int op_pin_result=atoi(buffer_op);     // Convert character to int,(pinmode needs int value)
                                    Serial.println(op_pin_result);
                                    
                                    pinMode(op_pin_result,OUTPUT);       
                                    Serial.println(op_pin_result);
                                    if(sub[3]=='1')                        //For pin High
                                       {
                                            digitalWrite(op_pin_result,HIGH); 
                                            Serial.write("High");
                                            BTSerial.write("1"); 
                                            BTSerial.write(op_pin_result); 
                                            BTSerial.write("1");
                                            BTSerial.write(";"); 
                                       }
                                    else if(sub[3]=='0')                //For pin LOW
                                       {
                                            digitalWrite(op_pin_result,LOW); 
                                            Serial.write("LOW");
                                            BTSerial.write("1"); 
                                            BTSerial.write(op_pin_result); 
                                            BTSerial.write("0"); 
                                            BTSerial.write(";"); 
                                       }
                             }       
                   
                  }
                  //Fan Action
                 if(sub[0]=='y')                                                             // packet 'y' for non ic dimmer
                     {                                                                       // For Multiple fan use B,C,D,E...... 
                                                                                             // packet like ayB050a# means 1st fan speed 50 
                       Serial.println("Heyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");            
                           if(sub[1]=='B')
                                {
                                     Serial.print("B");  
                                     String a=String(sub[2])+String(sub[3])+String(sub[4]);
                                     int a1=a.toInt();
                                      dimming=a1;
                                     Serial.println(a1);
                                     
                                     char bcollect[3];                                     
                                     bcollect[0]=sub[2];
                                     bcollect[1]=sub[3];
                                     bcollect[2]=sub[4];
                                     bcollect[3]='\0';
                                     
                                     BTSerial.write("yB"); 
                                     BTSerial.write(bcollect); 
                                     BTSerial.write(";"); 
                                } 
                              else if(sub[1]=='C')  
                                {
                                     Serial.print("C");  
                                     String b=String(sub[2])+String(sub[3])+String(sub[4]);
                                     int b1=b.toInt();
                                     dimming1=b1;
                                     Serial.println(b1);
                                     
                                     char ccollect[3];
                                     ccollect[0]=sub[2];
                                     ccollect[1]=sub[3];
                                     ccollect[2]=sub[4];
                                     ccollect[3]='\0';
                                     
                                     BTSerial.write("yC"); 
                                     BTSerial.write(ccollect); 
                                     BTSerial.write(";"); 
                                     
                                }
                              else if(sub[1]=='D')  
                                {
                                     Serial.print("D");  
                                     String c=String(sub[2])+String(sub[3])+String(sub[4]);
                                     int c1=c.toInt();
                                     dimming2=c1;
                                     Serial.println(c1);
                                     
                                     char ccollect[3];
                                     ccollect[0]=sub[2];
                                     ccollect[1]=sub[3];
                                     ccollect[2]=sub[4];
                                     ccollect[3]='\0';
                                     
                                     BTSerial.write("yD"); 
                                     BTSerial.write(ccollect); 
                                     BTSerial.write(";"); 
                                }   
                     }
                else if(sub[0]=='x')                                                    // x for current status of battery i.e mobile charged
                       {
                            Serial.println("charged");
                            Serial.println(sub[1]);
                            Serial.println(sub[2]);
                            Serial.println(sub[3]); 
                            
                            char buffer_op_charge_2[3];                               // Take character array
                            buffer_op_charge_2[0]=sub[1];
                            buffer_op_charge_2[1]=sub[2];
                            buffer_op_charge_2[2]=sub[3];
                            buffer_op_charge_2[3] = '\0';
                            Serial.println(buffer_op_charge_2);
                            int op_pin_result_charge_3=atoi(buffer_op_charge_2);      // convert char array to int battery level
                           
                            if(op_pin_result_charge_3<=30)                            // check battery level is less than 30 
                              {
                                  //int op_pin_result_charge=atoi(buffer_op_charge);                                    
                                  digitalWrite(2,HIGH);  
                                  BTSerial.write("x"); 
                                  BTSerial.write(buffer_op_charge_2);                 // send response to mobile
                                  BTSerial.write(";"); 
                                 
                                  Serial.println("///////////////////////");
                                  Serial.println("x"); 
                                  Serial.println(buffer_op_charge_2); 
                                  Serial.println("************************");
                              }
                              
                            if(op_pin_result_charge_3>=90)                            // check battery level is greater than 90   
                              {
                                  //int op_pin_result_charge_1=atoi(buffer_op_charge);                                    
                                  digitalWrite(2,LOW); 
                                  BTSerial.write("x"); 
                                  BTSerial.write(buffer_op_charge_2);                  // send response to mobile
                                  BTSerial.write(";"); 
                                  
                                Serial.println("///////////////////////");
                                Serial.println("x"); 
                                Serial.println(buffer_op_charge_2); 
                                Serial.println("************************");
                                
                              }                              
                           
                        }  
                else if(sub[0]=='r')                                              // r for current status of battery i.e mobile charging ,Rest code same as above i.e x
                       {
                            Serial.println("charging");
                            Serial.println(sub[1]);
                            Serial.println(sub[2]);
                            Serial.println(sub[3]); 
                            
                         
                            char buffer_op_charge_3[3];
                            buffer_op_charge_3[0]=sub[1];
                            buffer_op_charge_3[1]=sub[2];
                            buffer_op_charge_3[2]=sub[3];
                            //buffer_op[]=sub[3];
                            buffer_op_charge_3[3] = '\0';
                            Serial.println(buffer_op_charge_3);
                            int op_pin_result_charge_4=atoi(buffer_op_charge_3);
                            
                         
                            if(op_pin_result_charge_4<=30)
                            {
                                //int op_pin_result_charge_2=atoi(buffer_op_charge_1);                                    
                                digitalWrite(2,HIGH);  
                                BTSerial.write("r");
                                BTSerial.write(buffer_op_charge_3); 
                                BTSerial.write(";"); 
                                //BTSerial.write("1"); 
                               
                               //Serial.println("1"); 
                                Serial.println("///////////////////////");
                                Serial.println("r"); 
                                Serial.println(buffer_op_charge_3); 
                                Serial.println("************************");
                            }
                            
                          if(op_pin_result_charge_4>=90)
                            {
                                //int op_pin_result_charge_3=atoi(buffer_op_charge_1);                                    
                                digitalWrite(2,LOW);  
                                BTSerial.write("r");
                                BTSerial.write(buffer_op_charge_3); 
                                BTSerial.write(";"); 
                                //BTSerial.write("0"); 
                                Serial.println("///////////////////////");
                                Serial.println("r");
                               Serial.println(buffer_op_charge_3);
                                Serial.println("***********************");
                            }    
                     
                        }           
//                //Bluetooth AT command
//                else if(sub[0]=='o')
//                       {
//                         // Serial.println(sub[0]);
//                          Serial.println("Bluetooth Original Setting");
//                          delay(500);
//                          digitalWrite(9,HIGH);
//                          delay(100);
//                          BTSerial.write("AT+ORGL"); 
//                          BTSerial.write("\r\n");  
//                          delay(100);
//                          BTSerial.write("AT+RMAAD");  
//                          BTSerial.write("\r\n");  
//                          delay(100);
//                          digitalWrite(9,LOW);
//                        }       
//                else if(sub[0]=='c')
//                       {
//                        Serial.println("OutPut"); 
//                        Serial.println(sub[1]); 
//                        Serial.println(sub[2]);                        
//                        
//                        char buffer123[4];
//                        buffer123[0]=sub[1];
//                        buffer123[1]=sub[2];
//                        buffer123[2]=sub[3];
//                        buffer123[3]=sub[4];
//                        buffer123[4] = '\0';
//                        
//                        Serial.println(buffer123);
//                        
//                           digitalWrite(8,HIGH);
//                           delay(100);
//                           //str.toCharArray(bufferrfid,20);
//                           BTSerial.write("AT+PSWD=");
//                           BTSerial.write(buffer123);  
//                           BTSerial.write("\r\n");  
//                           delay(50);
//                           BTSerial.write("AT+RMAAD");  
//                           BTSerial.write("\r\n");  
//                           delay(50);
//                           digitalWrite(8,LOW);
//                           BTSerial.write("Successfully Password Change");  
//                     }
                     
          }  
         
              //////////////////////////////// 
             TestArray1[j]='\0'; 
             j=0;
              str="";
             Btkey='\0';
            }
              
         }
        
      }
      ////////////////////////////////////////////////////////////
      
       
 if(flag_zc==1)
 {          
    // byte a[]={40,78,78,78};
    
    // byte a[]={80,80,80,80};
    
    
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////
                   int flag=0;
                   int g=0;  
                   int de=0;
                   int we=0;
                   //int we1=0;
                   
                   for(int i=0;i<dimmercount;i++)                       // for loop dimmer count 
                                                                        // This check the duplicate elements in array  
                      {
                          flag=0;
                          int v=(int)a[i];                                        
                          for(int x=i-1;x>=0;x--)
                                  {
                                    if(a[x]==v)
                                       {                                 // If found duplicate then flag 1 and break the loop     
                                             flag=1;
                                             break;
                                      }
                                     else
                                       {                                 // else flag 0   
                                          flag=0; 
                                       }
                  
                                  }
                                  
                          if(flag==0)
                           {           
                         
                          for(int j=i+1;j<dimmercount;j++)
                             {                                                    // This loop for finding index from array            
                                     if(a[i]==a[j])         
                                         {           
                                                ////////////////////////////////////
                                                      int q3=(int)(a[i]);
                                                      //Serial.println(q3);
                                                      duplicate[de]=q3;              // de contains length
                                                      de++;
                                                     
                                                ////////////////////////////////////
                                           
                                                  for(int k=0;k<dimmercount;k++)    
                                                         {                           // This loop for store index in array
                                                            if(a[i]==a[k])
                                                               {                         
                                                                  b[g]=k;
                                                                  g++; 
                                                                 
                                                               }
                                                         }
                                                   break;
                                          }                                          
                              }
                           }
                      }
                  ///////////////////////////////////////////////////////////////////////////////          
                               
                               //Serial.println(de);
                               int flagup=0;                            // Again filter for non duplicate elements in array
                               for(int kl1=0;kl1<de;kl1++)
                                  {
                                       flagup=0;
                                       int dupfir=duplicate[kl1];             
                                       for(int ai=0;ai<dimmercount;ai++)
                                          {
                                            if(dupfir!=a[ai])
                                            {
                                             // Serial.println(a[ai]);
                                              if(dupfir<a[ai])
                                                 {
                                                     flagup=1;
                                                     break;
                                                 }
                                                 else 
                                                   {
                                                      flagup=0;
                                                   }
                                            }   
                                          }
                                        
                                       if(flagup==1)
                                         {
                                             break;
                                         }   
                                  
                                  }
                                
                                
                                  if(flagup==1)
                                    {
                                               /////////////////////////////////
                         
                                                            for(int dupli=0;dupli<de;dupli++)                        // for dimming level minus level 2nd from 1st
                                                               {
                                                                  int dup1=0;
                                                                  int dup12=0;
                                                                   //Serial.println(duplicate[dupli]);
                                                                   dup1=duplicate[dupli];
                                                                   dup12=duplicate[dupli]-duplicate[dupli-1];       
                                                                   if(dupli==0)                                      // condition for 0 update dup1
                                                                      {
                                                                         dup12=duplicate[dupli];
                                                                      }
                                                                      else if(dupli>0)
                                                                       {
                                                                            dup12=dup12;
                                                                       }
                                                                    // Serial.println(dup12);  
                                                                      // delay(1000);
                                                                   if(dup1>1 && dup1<=15)                             //for 0-15 level set pin high
                                                                     {
                                                                                   for(int inr=0;inr<sizeof(c);inr++)
                                                                                       {
                                                                                             if(dup1==c[inr])
                                                                                                {
                                                                                                                                                           
                                                                                                              digitalWrite(pins[inr],HIGH);      
                                                                                                }
                                                                                       }
                                                                          
                                                                     }
                                                                     else if(dup1>15 && dup1<=125)                  //for 15-128 level set pin on delay basis
                                                                     {
                                                                         dimtime1=75*dup12;                                                
                                                                         delayMicroseconds(dimtime1); 
                                                                         for(int inr=0;inr<sizeof(c);inr++)
                                                                             {
                                                                                   if(dup1==c[inr])
                                                                                     {            
                                                                                                    digitalWrite(pins[inr],HIGH);                       
                                                                                                    delayMicroseconds(10);                              
                                                                                                    digitalWrite(pins[inr],LOW);  
                                                                                        
                                                                                      }
                                                                             }
                                                                     }
                                                                    else if(dup1==128)                        // if 128 set pin low
                                                                       {
                                                                             for(int inr=0;inr<sizeof(c);inr++)
                                                                                       {
                                                                                             if(dup1==c[inr])
                                                                                                {
                                                                                                                                                           
                                                                                                              digitalWrite(pins[inr],LOW);      
                                                                                                }
                                                                                       }
                                                                       }        
                                                               }
                                                             
                                          /////////////////////////////////////
                                                                                               
                                                                                                                                     
                                          int flag1=0;                                                    // other than duplicate
                                          for(int t=0;t<dimmercount;t++)
                                             {
                                               flag1=0;
                                                    for(int r=0;r<g;r++) 
                                                      {   
                                                         if(b[r]==t)
                                                             {
                                                                  flag1=1;
                                                                  break;
                                                             }
                                                      }
                                                      if(flag1==0)
                                                       {
                                                          
                                                         //////////////////////////////
                                                                  int q1=(int)(a[t]);
                                                                  //Serial.println(q1);                                                        
                                                                  for(int j=0;j<dimmercount;j++)
                                                                      { 
                                                                             int q2=(int)(c[j]);
                                                                             if(q1==q2)
                                                                                {                                                                                                           
                                                                               
                                                                                    cal=a[t]-a[t-1];
                                                                                     if(t>0)
                                                                                       {
                                                                                          cal=cal;
                                                                                       }
                                                                                       else if(t==0)
                                                                                          {
                                                                                             cal=a[t];
                                                                                          }
                                                                                         // Serial.println(a[t]);
                                                                                         if(a[t]>1 && a[t]<=15)
                                                                                              {
                                                                                                digitalWrite(pins[j],HIGH);   
                                                                                              }
                                                                                            else if(a[t]>15 && a[t]<=125)
                                                                                              {
                                                                                                   dimtime=75*cal;  
                                                                                                   delayMicroseconds(dimtime); 
                                                                                                   digitalWrite(pins[j],HIGH);                       
                                                                                                   delayMicroseconds(10);                              
                                                                                                   digitalWrite(pins[j],LOW);
                                                                                              }
                                                                                              else if(a[t]==128)
                                                                                                {
                                                                                                   digitalWrite(pins[j],LOW); 
                                                                                                }
                                                                                    //we1++;
                                                                                }
                                                                      }          
                                                                     
                                                       }
                                                     
                                              }
                                    
                                           }
                                    else                                                          // else flag 0
                                       {
                                              int flag1=0;
                                              int we12=0;
                                              for(int t=0;t<dimmercount;t++)
                                                 {
                                                   flag1=0;
                                                        for(int r=0;r<g;r++) 
                                                          {   
                                                             if(b[r]==t)
                                                                 {
                                                                      flag1=1;
                                                                      break;
                                                                 }
                                                          }
                                                          if(flag1==0)
                                                           {
                                                             //////////////////////////////
                                                                      int q1=(int)(a[t]);
                                                                      //Serial.println(q1);                                                        
                                                                      for(int j=0;j<dimmercount;j++)
                                                                          { 
                                                                                 int q2=(int)(c[j]);
                                                                                 if(q1==q2)
                                                                                    {
                                                                                       pos1[we12]=c[j];
                                                                                                                                                                      
                                                                                       cal1=a[t]-a[t-1];
                                                                                       if(t>0)
                                                                                         {
                                                                                            cal1=cal1;
                                                                                         }
                                                                                         else if(t==0)
                                                                                            {
                                                                                               cal1=a[t];                                                                                               
                                                                                            }
                                                                                           // Serial.println(cal1);
                                                                                           if(a[t]>1 && a[t]<=15)
                                                                                                  {
                                                                                                    digitalWrite(pins[j],HIGH);   
                                                                                                  }
                                                                                                else if(a[t]>15 && a[t]<=125)
                                                                                                  {
                                                                                                       dimtime=75*cal1;  
                                                                                                       delayMicroseconds(dimtime); 
                                                                                                       digitalWrite(pins[j],HIGH);                       
                                                                                                       delayMicroseconds(10);                              
                                                                                                       digitalWrite(pins[j],LOW);
                                                                                                  }
                                                                                                  else if(a[t]==128)
                                                                                                     {
                                                                                                        digitalWrite(pins[j],LOW);  
                                                                                                     }
                                                                                        //we++;
                                                                                        we12++;
                                                                                    }
                                                                          }          
                                                                         
                                                           }
                                                         
                                                  }
                                                  
                                                  //Serial.println(pos1[we12]);
                                                  //int gt=0;
                                                   int gt1=0;
                                                    for(int e=0;e<we12;e++)
                                                    {
//                                                           int f=we12;
//                                                           Serial.println(pos1[f]);
                                                             gt1=pos1[e];
                                                         //  gt++;
                                                    }
                                                    
                                                    //Serial.println(gt1);
                                                    //Serial.println(pos1[gt]);
                                                    
                                     /////////////////////////////////////////////////////////////////////////////////////////////////////////                                     
 
                                          for(int dupli=0;dupli<de;dupli++)
                                             {
                                                 //Serial.println(duplicate[dupli]);
                                                 int dup11=0;
                                                 //Serial.println(dup1);
                                                  int dup13=0; 
                                                 dup11=duplicate[dupli];                                              
                                                 if(dupli==0)
                                                    {
                                                      
                                                      //Serial.println("Yup");
                                                       if(gt1<duplicate[dupli])
                                                        {
                                                           dup13=duplicate[dupli]-gt1;
                                                        }
                                                       else if(gt1>=duplicate[dupli])
                                                         {
                                                             dup13=duplicate[dupli];
                                                         } 
                                                    }
                                                    else if(dupli>0)
                                                     {
                                                       //Serial.println("Go");
                                                         if(gt1<duplicate[dupli])
                                                        {
                                                           dup13=duplicate[dupli]-gt1;
                                                        }
                                                       else if(gt1>=duplicate[dupli])
                                                         {
                                                             dup13=duplicate[dupli];
                                                         } 
                                                     } 
                                                     //Serial.println(dupli);                                                     
                                                    // Serial.println(dup13);
                                                 if(dup11>1 && dup11<=15)
                                                   {
                                                                 for(int inr=0;inr<sizeof(c);inr++)
                                                                     {
                                                                           if(dup11==c[inr])
                                                                              {
                                                                                                                                         
                                                                                            digitalWrite(pins[inr],HIGH);      
                                                                              }
                                                                     }
                                                        
                                                   }
                                                   else if(dup11>15 && dup11<=125)
                                                   {
                                                       //Serial.println(dup13);
                                                       //dup13=dup13-70;
                                                       dimtime1=75*dup13; 
                                                       delayMicroseconds(dimtime1); 
                                                       for(int inr=0;inr<sizeof(c);inr++)
                                                           {
                                                                 if(dup11==c[inr])
                                                                   {            
                                                                                  digitalWrite(pins[inr],HIGH);                       
                                                                                  delayMicroseconds(10);                              
                                                                                  digitalWrite(pins[inr],LOW);  
                                                                      
                                                                    }
                                                                    
                                                           }
                                                   }
                                                   else if(dup11==128)
                                                      {
                                                           for(int inr=0;inr<sizeof(c);inr++)
                                                                     {
                                                                           if(dup11==c[inr])
                                                                              {
                                                                                                                                         
                                                                                            digitalWrite(pins[inr],LOW);      
                                                                              }
                                                                     }
                                                      }    
                                                 
                                             }
                                                                                               
                                                                                               /////////////////////////////////////
                                  
                                  
                                    /////////////
                                         
                                       }
                               
                                   // delay(1000);
      flag_zc=0;
   }  
      
    //////////////////////////////////////////////////////////////
    
    
     if(millis()>864000000)                          // 10 days millis, After that arduino Reset
   {
     
       pinMode(A3,OUTPUT);
       digitalWrite(A3,LOW);
       delay(2000);
       digitalWrite(A3,HIGH);
   }
    
 }
 
 

void isort(byte *a, int n)            // Sorting function
{
     for (int i = 1; i < n; ++i)
     {
       int j = a[i];
       int k;
       for (k = i - 1; (k >= 0) && (j < a[k]); k--)
       {
         a[k + 1] = a[k];
       }
       a[k + 1] = j;
     }
 
}

 

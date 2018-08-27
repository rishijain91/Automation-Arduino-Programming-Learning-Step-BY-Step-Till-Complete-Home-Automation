#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10,11); // RX | TX

char TestArray1[100];

String str;

int h=0;

int blu=0;

int result[20];

///////////////////////////////////////////////////////////////////////////////

byte b[5]={};
//int pos[4]={};
 //int p,q;

String inData;
///////////////////////////////////////////////////////////////////////////////

int p,q;
long dimtime=0;
long dimtime1=0;
//long cal=0;
int flag_zc=0;

//////////////////////////////////////////////////////////////////////////////////////////////

 //int pins[]={3,7,9};
 int pins[]={3,7,9,12,A0};
 //long dim_time;
 int pos[5]={};
 int pos1[5]={};
 
 /////////////////////////////////////////////////////////////////////////////////////////////

int dimming=1;
int dimming1=1;
int dimming2=1;
int dimming3=1;
int dimming4=1;

///////////////////////////////////////////////////////////////////////////////////////////

int duplicate[5]={};

int duplicate1[5]={};

long cal=0;
long cal1=0;

int dimmercount=5;

void setup()
{
 Serial.begin(9600);

 Serial.println("Reset");
 BTSerial.begin(38400);  // HC-05 default speed in AT command more
   for(int t=0;t<5;t++)
     {
        pinMode(pins[t],OUTPUT);
        digitalWrite(pins[t],LOW);
     }
     
  attachInterrupt(0, zero_crosss_int, RISING);
                                    
}

void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{     
 flag_zc=1;
 
} 

//we'll not use loop for this
void loop()
{
  
       if(BTSerial.available()>0)
    {
        char recieved = BTSerial.read();
       
        inData += recieved; 
        //Serial.println(recieved);
        // Process message when new line character is recieved
        if (recieved == '\n')
        {                                
              if(inData[0]=='a')
                {
                     Serial.print("A");  
                     String a=String(inData[1])+String(inData[2])+String(inData[3]);
                     int a1=a.toInt();
                     dimming=a1;
                     Serial.println(a1);
                    
                } 
              else if(inData[0]=='b')  
                {
                     Serial.print("B");  
                     String b=String(inData[1])+String(inData[2])+String(inData[3]);
                     int b1=b.toInt();
                     dimming1=b1;
                     Serial.println(b1);
                }
              else if(inData[0]=='c')  
                {
                     Serial.print("C");  
                     String c=String(inData[1])+String(inData[2])+String(inData[3]);
                     int c1=c.toInt();
                     dimming2=c1;
                     Serial.println(c1);
                }  
               else if(inData[0]=='d')  
                {
                     Serial.print("D");  
                     String d=String(inData[1])+String(inData[2])+String(inData[3]);
                     int d1=d.toInt();
                     dimming3=d1;
                     Serial.println(d1);
                }   
              else if(inData[0]=='e')  
                {
                     Serial.print("E");  
                     String e=String(inData[1])+String(inData[2])+String(inData[3]);
                     int e1=e.toInt();
                     dimming4=e1;
                     Serial.println(e1);
                }     
                
                
            inData = ""; // Clear recieved buffer
        }
    }
  
    
  byte a[]={dimming,dimming1,dimming2,dimming3,dimming4};  
  //byte a[]={40,80,55,80};  
  
  byte c[5]={};             
  
  for(int i=0;i<5;i++)
     {
         c[i]=a[i];
         //Serial.println(a[i]);
     }
     
       isort(a,sizeof(a));     
     
     
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
                   
                   for(int i=0;i<dimmercount;i++)
                      {
                          flag=0;
                          int v=(int)a[i];
                          for(int x=i-1;x>=0;x--)
                                  {
                                    if(a[x]==v)
                                       {
                                             flag=1;
                                             break;
                                      }
                                     else
                                       {
                                          flag=0; 
                                       }
                  
                                  }
                                  
                          if(flag==0)
                           {           
                         
                          for(int j=i+1;j<dimmercount;j++)
                             {     
                                     if(a[i]==a[j])         
                                         {           
                                                /////////////////////////////////////////////////
                                                      int q3=(int)(a[i]);
                                                      //Serial.println(q3);
                                                      duplicate[de]=q3;
                                                      de++;
                                                     
                                                ///////////////////////////////////////////////////////////
                                           
                                                  for(int k=0;k<dimmercount;k++) 
                                                         {
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
                               int flagup=0;
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
                         
                                                            for(int dupli=0;dupli<de;dupli++)
                                                               {
                                                                  int dup1=0;
                                                                  int dup12=0;
                                                                   //Serial.println(duplicate[dupli]);
                                                                   dup1=duplicate[dupli];
                                                                   dup12=duplicate[dupli]-duplicate[dupli-1];
                                                                   if(dupli==0)
                                                                      {
                                                                         dup12=duplicate[dupli];
                                                                      }
                                                                      else if(dupli>0)
                                                                       {
                                                                            dup12=dup12;
                                                                       }
                                                                    // Serial.println(dup12);  
                                                                      // delay(1000);
                                                                   if(dup1>1 && dup1<=15)
                                                                     {
                                                                                   for(int inr=0;inr<sizeof(c);inr++)
                                                                                       {
                                                                                             if(dup1==c[inr])
                                                                                                {
                                                                                                                                                           
                                                                                                              digitalWrite(pins[inr],HIGH);      
                                                                                                }
                                                                                       }
                                                                          
                                                                     }
                                                                     else if(dup1>15 && dup1<=125)
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
                                                                    else if(dup1==128)
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
                                                                                               
                                                                                                                                     
                                          int flag1=0;
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
                                    else
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
  
}


void isort(byte *a, int n)
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


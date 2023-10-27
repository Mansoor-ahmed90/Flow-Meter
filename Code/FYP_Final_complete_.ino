
//                                     Final Arduino Program of FINAL YEAR Project(Design & Fabrication of Multifunctional Flowmeter)
//                                                  Project Supervisor : Dr Izhar-ul-Haq
//                                                  Co-supervisor      : Dr Kamran Shah
//                                                    Project Members:
//                                                                   1) Mansoor Ahmed
//                                                                   2) Husnain Saeed
//                                                    Institute of Mechatronics Engineering
//                                           University of Engineering & technology Peshawar, Pakisatn
//                                                                                            Created On(Final): 13th August 2014


//********************************************************************************************************************************************************
//********************************************************************************************************************************************************


#include <LiquidCrystal.h>                                       //LCD library                                      
#include "Wire.h"                                                // SDL Library
                                   

#define DS1307_ADDRESS 0x68                                      // for RTC DS1307s

#define trigPin_width_1 23                                         // Trigger Pin for width sensor_1
#define echoPin_width_1 27                                      // Echo Pin for width sensor_1
#define trigPin_width_2 31                                      // Trigger Pin for width sensor_2
#define echoPin_width_2 35                                       // echo pin for width sensor_2
#define trigPin_depth 39                                        // Trigger Pin for sensors 3
#define echoPin_depth 43                                        // echo pin for sensor 3

# define Counter  44

LiquidCrystal lcd(22, 24, 26, 28, 30, 32);                     // initialize the library with the numbers of the interface pins

long duration_width_1=0, width_1=0;                                // Variables for width-sensor 1
long duration_width_2=0, width_2=0;                                // Variables for width-sensor 2
long  width =0;
long duration_depth,depth, depth_sen;                                    // Variables for depth-sensor 

int second,minute, hour, weekDay, monthDay, month, year;

int subsections, sub_width;

int timer=0, ptimer=0, incr=0;

int Count=0;

int i;

int a=0, b=0,c=0, d=0;

# define Push_A_width 47
# define Push_B_depth 48
# define Push_C_depth 51

//***********************************************************************************************************************
//***********************************************************************************************************************
void setup() {
             
            Wire.begin();
           Serial.begin (9600);
           
                     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% For Ultrasonic_sensors    %%%%%%%%%%%%%%%%%%%%
                     
                       pinMode(trigPin_width_1, OUTPUT);                          // trigger pin defined for width sensor_1
                       pinMode(trigPin_width_2, OUTPUT);                          // trigger pin defined for width sensor_2
                       pinMode(trigPin_depth, OUTPUT);                           // trigger pin defined for depth sensor
                       
                       
                       pinMode(echoPin_width_1, INPUT);                          // for width sensor_1 echo defin
                       pinMode(echoPin_width_2, INPUT);                          // for width sensor_2 echo defin
                       pinMode(echoPin_depth, INPUT);                            // for  depth sensor echo defin
                     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% End-ultrasonic_sensors    %%%%%%%%%%%%%%%%%%%%%%
          
                        pinMode(Counter, INPUT);
          
                     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% For LCD   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                     
                        lcd.begin(16, 2);                  // set up the LCD's number of columns and rows:
                        lcd.print(" WELCOME ");            // Print a message to the LCD.
                        delay(2000);
                       //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% End-LCD-    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
  
  
                    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% For PUSH-BUTTONS    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                    
                        pinMode(Push_A_width, INPUT);
                        pinMode(Push_B_depth, INPUT);
                        pinMode(Push_C_depth, INPUT);
                   //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% End-Push-Buttons    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
  
  
}


//****************************************************************************************************************************
//****************************************************************************************************************************
void loop() {
  
              
              //@@@@@@@@@@@@@@@@@@@@@@@@@@@@   DATE DISPLAY      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                  
                  printDate();
                  lcd.clear();
                  lcd.setCursor(0,0);

                                lcd.print(" ");
                                switch(weekDay){
                                            case 1:
                                                  lcd.print("Sun");
                                                break;
                                            case 2:
                                                   lcd.print("Mon");
                                                break;
                                            case 3:
                                                   lcd.print("Tue");
                                                break;
                                            case 4:
                                                  lcd.print("Wed");
                                                break;
                                            case 5:
                                                  lcd.print("Thu");
                                                break;
                                            case 6:
                                                  lcd.print("Fri");
                                                break;
                                            case 7:
                                                  lcd.print("Sat");
                                                break;
                                            }
                                lcd.print(" ");
                                lcd.print(monthDay);
                                lcd.print("/");
                                lcd.print(month);
                                lcd.print("/20");
                                lcd.print(year);
                                delay(1000);
                                lcd.setCursor(0, 1);
                                lcd.print(" ");
                                lcd.print(hour);
                                lcd.print(":");
                                lcd.print(minute);
                                lcd.print(":");
                                lcd.print(second);
                                delay(5000);
                                
                  
                  
               
               //@@@@@@@@@@@@@@@@@@@@@@@@@@  For Width of Channel   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
               
                  lcd.clear();
                  lcd.print("Channel Width ");
                  lcd.setCursor(0, 1);
                  lcd.print("In centimeter");
                  //lcd.clear();
                  delay(2000);
                  lcd.print("Channel Width ");
                  while(1){
                                     width_1=0;
                                     width_2=0;
                                     width=0;
                                     lcd.clear();
                                     lcd.print("Channel Width ");
                                     width_1 =   width_sensor1();
                                     width_2 =   width_sensor2();
                                     
                                     lcd.setCursor(0, 1);
                                     lcd.print(width_1);
                                     delay(500);
                                     lcd.print(" + ");
                                     lcd.print(width_2);
                                     delay(1000);
                                     //Serial.print(width_1);
                                    // Serial.print(width_2);
                                     if(digitalRead(Push_A_width) == HIGH)                         /// break condition to break out of loop if Push Button is pressed
                                                 {
                                                         width = (width_1) + (width_2) + 17;
                                                         lcd.clear();
                                                         lcd.print("Channel Width ");
                                                         lcd.setCursor(0, 1);
                                                         lcd.print(width);
                                                         delay(2000);          
                                                         break;
                                                 }
                  }
                  
                  //@@@@@@@@@@@@@@@@@@@@@@@@@@ Conditions For Width of Channel   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                        Serial.print("width 1=  ");
                        Serial.print(width_1);
                        Serial.print(".......width 2=");
                        Serial.print(width_2);
                        delay(2000);
                        if (width > 0 && width < 200){
                            
                                      subsections =  width/20;     
                                     lcd.clear();
                                     lcd.print("Number of Sub- ");
                                     lcd.setCursor(0, 1);
                                     lcd.print("Sections :");
                                     lcd.print(subsections);     
  
                        }
             
                     if (width > 200 && width < 300){
                            
                                    subsections =  width/30;     
                                   lcd.clear();
                                   lcd.print("Number of Sub- ");
                                   lcd.setCursor(0, 1);
                                   lcd.print("Sections :");
                                   lcd.print(subsections);     
  
                        }
                        
                    if (width > 300 && width < 400){
                            
                                    subsections =  width/40;     
                                   lcd.clear();
                                   lcd.print("Number of Sub- ");
                                   lcd.setCursor(0, 1);
                                   lcd.print("Sections :");
                                   lcd.print(subsections);     
  
                        }
                        
                   if (width > 400 && width < 800){
                            
                                    subsections =  width/100;     
                                   lcd.clear();
                                   lcd.print("Number of Sub- ");
                                   lcd.setCursor(0, 1);
                                   lcd.print("Sections :");
                                   lcd.print(subsections);     
  
                        }
              
                  if (width > 800 && width < 1500){
                            
                                    subsections =  width/150;     
                                   lcd.clear();
                                   lcd.print("Number of Sub- ");
                                   lcd.setCursor(0, 1);
                                   lcd.print("Sections :");
                                   lcd.print(subsections);     
  
                        }
                        
                    if (width > 1500 && width < 2500){
                            
                                    subsections =  width/200.0;     
                                   lcd.clear();
                                   lcd.print("Number of Sub- ");
                                   lcd.setCursor(0, 1);
                                   lcd.print("Sections :");
                                   lcd.print(subsections);     
  
                        }
                        
                        if (width > 2500 && width < 3500){
                            
                                    subsections =  width/300.0;     
                                   lcd.clear();
                                   lcd.print("Number of Sub- ");
                                   lcd.setCursor(0, 1);
                                   lcd.print("Sections :");
                                   lcd.print(subsections);     
  
                        }
                        
                         if (width > 3500 ){
                            
                                    subsections =  (width/500.0);     
                                   lcd.clear();
                                   lcd.print("Number of Sub- ");
                                   lcd.setCursor(0, 1);
                                   lcd.print("Sections :");
                                   lcd.print(subsections);     
  
                        }
                        delay(1000);
                        sub_width = width/ subsections;
                        a = sub_width/2;
                        //b = a;
              
          // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Area-Velocirty Calculations  @@@@@@@@@@@@@@@@@@@@@
              
                    // on the basis of number of sub-section, we will proceed toward the area calculations
              
              /// for sub-sections
                  
                                   lcd.clear();
                                   lcd.print("Calculations for");
                                   lcd.setCursor(0, 1);
                                   lcd.print("Each section");
                                    delay(2000); 
                  
                  // LOOP for calculations at subsections
                  
                      for(i=1; i<=subsections; i++)
                            {
                                                 lcd.clear();
                                                 lcd.print("For Subsection");
                                                 lcd.setCursor(0, 1);
                                                 lcd.print("  ");
                                                 lcd.print(i);
                                                 delay(2000); 
                                   
                                   //******************** for width of subsections *************************
                                  
                                                 width_subsection();
                                  
                                  //***********************  for Depth at each section **********************
                                  
                                                   lcd.clear();
                                                   lcd.print("Depth of Sub-");
                                                   lcd.setCursor(0, 1);
                                                   lcd.print("section :");
                                                   lcd.print(i);
                                                   delay(2000);
                                         
                                         while(1){
                                    
                                                       depth=0;
                                                       lcd.clear();
                                                       lcd.print("Depth : ");
                                                       depth = depth_sensor();
                                     
                                     
                                                       lcd.setCursor(0, 1);
                                                       lcd.print(depth);
                                                       delay(1000);

                                                         if(digitalRead(Push_B_depth) == HIGH)                         /// break condition to break out of loop if Push Button is pressed
                                                                     {
                                                                             depth = depth;
                                                                             lcd.clear();
                                                                             lcd.print("Section depth ");
                                                                             lcd.setCursor(0, 1);
                                                                             lcd.print(depth);
                                                                             delay(2000);          
                                                                             break;
                                                                     }
                                                  }
                                        /// ************************** RPM Calculations on the basis of depth***********************
                                                    
                                                    // ************** depth CASE: 01 (Depth < 1.05 m)***********************
       
                                          if (depth <= 105 && depth >= 0)
                                                       {
                                                              lcd.clear();
                                                              lcd.print("Depth < 105 cm");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print("take reading");
                                                              delay(2000);   
                                                              lcd.clear();
                                                              lcd.print("At 40% from ");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print("bottom which is");
                                                                            delay(2000);
                                                                             c=0;
                                                                             c = 0.4*depth;
                                                                             lcd.clear();
                                                                             lcd.print(c); 
                                                                             lcd.print("  cm  "); 
                                                                             delay(2000);
                                                                             
                                                                             ///***********************
                                                           depth=0; 
                                                           lcd.clear();
                                                           lcd.print("Set depth "); 
                                                           delay(2500);                                
                                              while(1){
                                    
                                                           
                                                           lcd.clear();
                                                           lcd.print("Depth : ");
                                                           depth = depth_sensor();
                                                           lcd.setCursor(0, 1);
                                                           lcd.print(depth);
                                                           delay(500);
                        
                                                          if(digitalRead(Push_B_depth) == HIGH)       
                                                                        {
                                                                           depth = depth;
                                                                           lcd.clear();
                                                                           lcd.print("Section depth ");
                                                                           lcd.setCursor(0, 1);
                                                                           lcd.print(depth);
                                                                           delay(2000);          
                                                                           break;
                                                                                             }
                                                                                  }
                                                                             
                                          //********************* RPM COUNTER ******************************
                                                                             
                                                     lcd.clear();
                                                              lcd.print("Revolution ");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print("Counter");
                                                              delay(2000); 
                                                              lcd.clear();
                                                              lcd.print("Press Button C");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print("IF device is set");
                                                              delay(2000);
                                        while(1){                                                    
                                                if(digitalRead (Push_C_depth) == HIGH)
                                                             {
                             
                                                                RPM();
                                                              lcd.clear();
                                                              lcd.print("Counts");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print(Count);
                                                              delay(2000);
                                                              break;
                                                             } 
                                                             
                                                       }             
                                                         
                                                       }                               
                                                      ///********** end of if

                                        
                                        // ************** depth CASE: 02 (Depth > 1.05 m)***********************
                                        else{
                                        if (depth >= 105 )
                                                       {
                                                              lcd.clear();
                                                              lcd.print("Depth > 105 cm");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print("Take reading at");
                                                              delay(2000);   
                                                              lcd.clear();
                                                              lcd.print("20% & 80% from ");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print("bottom which is");
                                                                            delay(2000);
                                                                             c=0;
                                                                             d=0;
                                                                             c = 0.2*depth;
                                                                             d = 0.8*depth;
                                                                             lcd.clear();
                                                                             lcd.print(c);
                                                                             lcd.print("  &  "); 
                                                                             lcd.print(d);
                                                                             lcd.print(" cm  "); 
                                                                             delay(3000);
                                                                             
                                                                             ///***********************
                                                           depth=0; 
                                                           lcd.clear();
                                                           lcd.print("Set depth ");
                                                           delay(2500); 
                                         for(int j=1; j<=2; j++){ 
                                                        if(j==1){
                                                           lcd.clear();
                                                           lcd.print("Set depth at ");
                                                           lcd.setCursor(0, 1);
                                                           lcd.print(c);
                                                           lcd.print(" from bottom");
                                                           delay(3000);  
                                                        }  
                             
                             
                                                           if(j==2){
                                                           lcd.clear();
                                                           lcd.print("Set depth at ");
                                                           lcd.setCursor(0, 1);
                                                           lcd.print(d);
                                                           lcd.print(" from bottom");
                                                           delay(3000);  
                                                        } 
                             
                                                        
                                              while(1){
                                    
                                                           
                                                           lcd.clear();
                                                           lcd.print("Depth : ");
                                                           depth = depth_sensor();
                                                           lcd.setCursor(0, 1);
                                                           lcd.print(depth);
                                                           delay(500);
                        
                                                          if(digitalRead(Push_B_depth) == HIGH)       
                                                                        {
                                                                           depth = depth;
                                                                           lcd.clear();
                                                                           lcd.print("Section depth ");
                                                                           lcd.setCursor(0, 1);
                                                                           lcd.print(depth);
                                                                           delay(2000);          
                                                                           break;
                                                                         }
                                                      }
                                                                             
                                          //********************* RPM COUNTER ******************************
                                                                             
                                                     lcd.clear();
                                                              lcd.print("Revolution ");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print("Counter");
                                                              delay(2000); 
                                                              lcd.clear();
                                                              lcd.print("Press Button C");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print("IF device is set");
                                                              delay(2000);
                                        while(1){                                                    
                                                if(digitalRead (Push_C_depth) == HIGH)
                                                             {
                             
                                                                RPM();
                                                              lcd.clear();
                                                              lcd.print("Counts");
                                                              lcd.setCursor(0, 1);
                                                              lcd.print(Count);
                                                              delay(2000);
                                                              Count = 0;
                                                              incr = 0;
                                                              break;
                                                             } 
                                                             
                                                       }             
                                                         
                                                       } 
                                                       } 
                                        }                             
                                                      ///********** end of if
                              
                              
                            }
                            //8*********** end of for loop ************************
  
  
}






 
//************************************************************************************************************************************
//           ***************************************** Subroutines************************************************************


                                        //   **************** for Ultrasonic_width_1 *******************
                                        
                  int width_sensor1() 
                                     {
                                
                                       digitalWrite (trigPin_width_1, LOW);                          // trigger high
                                        delayMicroseconds(2);
                                       digitalWrite (trigPin_width_1, HIGH);                        // trigger high
                                        delayMicroseconds(10);
                                        digitalWrite (trigPin_width_1, LOW);                        // trigger low
                                        duration_width_1 = pulseIn(echoPin_width_1, HIGH);          // duration measurment
                                         width_1=((duration_width_1)/58.2);                         // distance measurment
                                         return width_1;
                                      }

                                      // ********************** For Ultrasonic_width_2  *******************


                  int width_sensor2() 
                                     {
                                
                                       digitalWrite (trigPin_width_2, LOW);                          // trigger high
                                        delayMicroseconds(2);
                                       digitalWrite (trigPin_width_2, HIGH);                        // trigger high
                                        delayMicroseconds(10);
                                        digitalWrite (trigPin_width_2, LOW);                        // trigger low
                                        duration_width_2 = pulseIn(echoPin_width_2, HIGH);          // duration measurment
                                         width_2=((duration_width_2)/58.2);                         // distance measurment
                                         return width_2;
                                      }


                                   // ********************** For Ultrasonic_Depth  *******************


                  int depth_sensor() 
                                     {
                                
                                       digitalWrite (trigPin_depth, LOW);                          // trigger high
                                        delayMicroseconds(2);
                                       digitalWrite (trigPin_depth, HIGH);                        // trigger high
                                        delayMicroseconds(10);
                                        digitalWrite (trigPin_depth, LOW);                        // trigger low
                                        duration_depth = pulseIn(echoPin_depth, HIGH);          // duration measurment
                                         depth_sen=(duration_depth/58.2);                         // distance measurment
                                         return depth_sen;
                                      }
                                      
                                      
                                      
                                      //*********************** FoR RPM COUNTER****************************
                                      
                   void RPM()
                            {
                                 
                               while(1)
                                      {
                                               printsec();
                                               timer = second;      
                                               if(timer != ptimer)
                                                         {
                                                           incr = incr +1;
                                                          } 
                                                
                                                lcd.clear();
                                                lcd.print("Time :");
                                                lcd.print(incr);
                                                lcd.setCursor(0, 1);
                                                lcd.print("Counts");
                                                lcd.print(Count);
                                                delay(100);        
                                                
                                                if((digitalRead(Counter)) == 1)
                                                         {
                                                           Count= Count + 1;
                                                          }
                                                          
                                                 while(1)
                                                         {
                                                             
                                                             if((digitalRead(Counter)) == 1)
                                                                       {
                                                                        }
                                                                   else {
                                                                           break;
                                                                         }
                                                             }
                                                     
                                                ptimer = timer;
                                              
                                              if(incr == 40)
                                                          {
                                                              break;
                                                          }  
                                    }
                                 
                     
                         }
                                      
                                      
                                  // ************************* for width of subsection ************************
                                  
                                      
                                void width_subsection()
                                     {
                                                                     
                                                                 lcd.clear();
                                                                 lcd.print("Set device at");
                                                                   if(i== 1)
                                                                           {
                                                                            b = a; 
                                                                           }
                                                                           else
                                                                           {
                                                                           b = sub_width + b;
                                                                           }
                                                                 lcd.setCursor(0, 1);
                                                                 lcd.print("width :");
                                                                 lcd.print(b); 
                                                                 delay(3000);
                                       //  *******************************************************
                               
                                
                                                  lcd.clear();
                                                  lcd.print("Press Button A");
                                                  lcd.setCursor(0, 1);
                                                  lcd.print("if width is set");
                                                  delay(3000);
                                                  lcd.clear();
                                                  lcd.print("Channel Width ");
                                
                                while(1){
                                                   width_1=0;
                                                   width_2=0;
                                                   width=0;
                                                   lcd.clear();
                                                   lcd.print("Channel Width ");
                                                   width_2 =   width_sensor2(); 
                                                   lcd.setCursor(0, 1);
                                                   lcd.print(width_2);
              
                                                   delay(1000);
                                                   //Serial.print(width_1);
                                                  // Serial.print(width_2);
                                                   if(digitalRead(Push_A_width) == HIGH)                         /// break condition to break out of loop if Push Button is pressed
                                                               {
                                                                       width = (width_2);
                                                                       lcd.clear();
                                                                       lcd.print("Channel Width ");
                                                                       lcd.setCursor(0, 1);
                                                                       lcd.print(width);
                                                                       delay(2000);          
                                                                       break;
                                                               }
                                                    
                                              }
                                                     // ***********************************  
                                                 
                                                  
                                 }      
                                      
                                      
                                      
                                      
                                      

                                //************************** FOR RTC DS1307 *************************
                    void printDate(){
                                                                    
                                        Wire.beginTransmission(DS1307_ADDRESS);                    // Reset the register pointer
                                              
                                                byte zero = 0x00;
                                                Wire.write(zero);
                                                Wire.endTransmission();
                                              
                                                Wire.requestFrom(DS1307_ADDRESS, 7);
                                              
                                                                     second = bcdToDec(Wire.read());
                                                                     minute = bcdToDec(Wire.read());
                                                                     hour = bcdToDec(Wire.read() & 0b111111);        //24 hour time
                                                                     weekDay = bcdToDec(Wire.read());              //0-6 -> sunday - Saturday
                                                                     monthDay = bcdToDec(Wire.read());
                                                                     month = bcdToDec(Wire.read());
                                                                     year = bcdToDec(Wire.read());
                                              
                                                //print the date EG   3/1/11 23:59:59
                                                Serial.print(month);
                                                Serial.print("/");
                                                Serial.print(monthDay);
                                                Serial.print("/");
                                                Serial.print(year);
                                                Serial.print(" ");
                                                Serial.print(hour);
                                                Serial.print(":");
                                                Serial.print(minute);
                                                Serial.print(":");
                                                Serial.println(second);
                                                Serial.print("   ");
                                                Serial.println(weekDay);
                                              
                                              }
                          byte bcdToDec(byte val){
                                                    
                                               return ( (val/16*10) + (val%16) );                          // Convert binary coded decimal to normal decimal numbers
                                              }


                        //****************** SUbroutine for Counter time*************************
                        
                        void printsec(){
                                                                    
                                        Wire.beginTransmission(DS1307_ADDRESS);                    // Reset the register pointer
                                              
                                                byte zero = 0x00;
                                                Wire.write(zero);
                                                Wire.endTransmission();
                                              
                                                Wire.requestFrom(DS1307_ADDRESS, 7);
                                              
                                                                     second = bcdToDec(Wire.read());
                                                                    
                                                                     
                        }
                    






//***********************************************************************************************************************************************************************
//                  *************************************************** END OF SUBROUTINES   ******************************************************
//                               ************************************************************************************************



/*
 * LCD(pin-4) RS pin to digital pin 22      //  22
 * LCD(pin-6) Enable pin to digital pin 24  /// 23
 * LCD(pin-11) D4 pin to digital pin 26     //  24
 * LCD(pin-12) D5 pin to digital pin 28      /  25
 * LCD(pin-13) D6 pin to digital pin 30      /  26
 * LCD(pin-14) D7 pin to digital pin 32     /  27
 * LCD(pin-5) R/W pin to ground 
 (pin-15) to Vcc
 (pin-16) to ground
 (pin-1)  to grond
 (pin-2) to Vcc
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD(pin-3) VO pin (pin 3)
 */

#define anInput     A0                        //analog feed from MQ135
#define co2Zero     55                        //calibrated CO2 0 level

char Incoming_value = 0;
float mq135_reading = 0.0; 
float glucose = 0; 
                
void setup() 
{
  Serial.begin(9600);         
  pinMode(13, OUTPUT); 
  pinMode(anInput,INPUT);                     //MQ135 analog feed set for input
}

void loop()
{
  int co2now[10];                               //int array for co2 readings
  int co2raw = 0;                               //int for raw value of co2
  int co2ppm = 0;                               //int for calculated ppm
  int zzz = 0;                                  //int for averaging
  float theoritical = 0;
  float efficiency = 0; 
  float ethanol = 0;
  
  for (int x = 0;x<10;x++)  //samplpe co2 10x over 2 seconds
  {                   
    co2now[x]=analogRead(A0);
    delay(200);
  }

  for (int x = 0;x<10;x++)  //add samples together
  {                     
    zzz=zzz + co2now[x];  
  }
  
  co2raw = zzz/10;                            //divide samples by 10
  co2ppm = co2raw - co2Zero;                 //get calculated ppm

  Incoming_value = Serial.read();      
  if(Incoming_value == '1')             
    digitalWrite(13, HIGH);  
  else if(Incoming_value == '0')       
    digitalWrite(13, LOW);
  else if(Incoming_value > '1')
    glucose = Incoming_value; 

  theoritical = ( 2 * 44 * glucose ) / 46; 
  efficiency = co2ppm / theoritical; 
  ethanol = ( 94.108 * efficiency ) / 44; 
    
  Serial.print(ethanol);
  delay(400);                            
} 

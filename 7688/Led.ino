 
 
 void Off_light(int redPin, int bluePin, int greenPin)  
 {  
  analogWrite(redPin,255);  
  analogWrite(greenPin,255);
  analogWrite(bluePin,255);   
 }  

 void On_light(int redPin, int greenPin, int bluePin)
 {
  analogWrite(redPin,255);  
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);    
 } 
 
 void Bluetooth_light(int redPin, int greenPin, int bluePin)
 {
  for(int i=0; i<4; i++){
  analogWrite(redPin,255);  
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);  
  delay(100) ;
  Off_light(redPin, bluePin, greenPin);
  delay(100); 
  analogWrite(redPin,255);  
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);  
  }
 }

void Water_light(int redPin, int greenPin, int bluePin)
 {
  analogWrite(redPin,255);  
  analogWrite(greenPin,0);
  analogWrite(bluePin,255);    
 } 
 
void Replacemode_light(int redPin, int greenPin, int bluePin)
 {
  analogWrite(redPin,255);  
  analogWrite(greenPin,0);
  analogWrite(bluePin,255);    
 } 


void Readytodrink_light(int redPin, int greenPin, int bluePin)
 {
  for(int i=0; i<4; i++){
  analogWrite(redPin,255);  
  analogWrite(greenPin,0);
  analogWrite(bluePin,255);  
  delay(100) ;
  Off_light(redPin, bluePin, greenPin);
  delay(100);     
  } 
 }

 void Record_light(int redPin, int greenPin, int bluePin)
 {
  for(int i=0; i<2; i++){
  analogWrite(redPin,255);  
  analogWrite(greenPin,0);
  analogWrite(bluePin,255);  
  delay(100) ;
  Off_light(redPin, bluePin, greenPin);
  delay(100); 
  analogWrite(redPin,255);  
  analogWrite(greenPin,0);
  analogWrite(bluePin,255);    
  } 
 }

 void NotReaching_light(int redPin, int greenPin, int bluePin)
 {
  for(int i=0; i<4; i++){
  analogWrite(redPin,0);  
  analogWrite(greenPin,255);
  analogWrite(bluePin,255);  
  delay(100) ;
  Off_light(redPin, bluePin, greenPin);
  delay(100);     
  } 
 }

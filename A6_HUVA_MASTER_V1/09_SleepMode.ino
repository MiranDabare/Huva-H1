void Sleep()
{
   void(* resetFunc) (void) = 0;
   
    sleep_enable();//Enabling sleep mode
    attachInterrupt(0, wakeUp, LOW);//attaching a interrupt to pin d2
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
    digitalWrite(LED_BUILTIN,LOW);//turning LED off
    RGB_LED("OFF");
    delay(1000); //wait a second to allow the led to be turned off before going to sleep
    sleep_cpu();//activating sleep mode
      delay(1000);
    Serial.println("just woke up!");//next line of code executed after the interrupt 
    digitalWrite(LED_BUILTIN,HIGH);//turning LED on
   
}

void wakeUp(){
  Serial.println("Interrrupt Fired");//Print message to serial monitor
   sleep_disable();//Disable sleep mode
   delay(1000);
    
  detachInterrupt(0); //Removes the interrupt from pin 2;
    delay(1000);
  resetFunc();
    delay(1000);
}

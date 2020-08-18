// ============ RGB LED ===========\\

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(LED_RED_PIN, red_light_value);
  analogWrite(LED_GREEN_PIN, green_light_value);
  analogWrite(LED_BLUE_PIN, blue_light_value);
}


void RGB_LED(String LEDColour)
{
  if (LEDColour == "WHITE")
  {
    RGB_color(0, 0, 0); 
  }

  if (LEDColour == "YELLOW")
  {
    RGB_color(0, 0, 255); 
  }

  if (LEDColour == "PINK")
  {
    RGB_color(0, 255, 0); 
  }

  if (LEDColour == "CYAN")
  {
    RGB_color(255, 0, 0); 
  }

  if (LEDColour == "BLUE")
  {
    RGB_color(255, 255, 0);
  }

  if (LEDColour == "RED")
  {
    RGB_color(0, 255, 255); 
  }

  if (LEDColour == "GREEN")
  {
    RGB_color(255, 0, 255); 
  }

  if (LEDColour == "OFF")
  {
    RGB_color(255, 255, 255); 
  }

  
}

/**
 * Connect a DHT11 sensor to pin 2 by following the pinout 
 * of 'Circuit Basics' and connect the I2C bus SDA to A4 and SCL to A5.
 * The LCD display will show the temperature and humidity values read from the DHT11 sensor.
 * @author Shloimy Elbaum (https://github.com/shloimy15e)
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);  

DHT dht (DHTPIN, DHTTYPE);

void setup() {
  lcd.init();  // Initialize the LCD
  dht.begin();  // Initialize the DHT sensor
  lcd.backlight();  // Turn on backlight (if supported)
  lcd.setCursor(0, 0);  // Set cursor to first column (0) and first row (0)
  lcd.print("hello");
}

/**
 * Reads temperature and humidity from a DHT11 sensor and displays the values on an LCD.
 * This function is called repeatedly in the main loop of the program.
 * It waits 2 seconds between measurements, reads the temperature and humidity,
 * and displays the values on the LCD. If a sensor reading fails, it displays an error message.
 */
void loop()
{
  // Wait a few seconds between measurements
  delay(2000);

  float temperature = dht.readTemperature(); // Read temperature as Celsius
  float humidity = dht.readHumidity();       // Read humidity (%)

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature))
  {
    lcd.setCursor(0, 0); // Set cursor to first column (0) and first row (0)
    lcd.print("T Failed!       ");
  }
  else
  {
    lcd.setCursor(0, 0); // Set cursor to first column (0) and first row (0)
    // Display temperature
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("  C   ");
  }
  if (isnan(humidity))
  {
    lcd.setCursor(0, 1); // Set cursor to first column (0) and second row (1)
    lcd.print("H Failed!       ");
  }
  else
  {
    lcd.setCursor(0, 1); // Set cursor to first column (0) and second row (1)
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
  }
}

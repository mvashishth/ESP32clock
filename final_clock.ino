#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "time.h"
#include <NTPClient.h>
#include <WiFiUdp.h>


// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

const char *ssid     = "You SSID";
const char *password = "Your Password";

const long utcOffsetInSeconds = 19800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "in.pool.ntp.org", utcOffsetInSeconds);



#include "DHT.h"

#define DHTPIN 23     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();


    Serial.begin(115200);


  dht.begin();

    WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}



void loop(){

  timeClient.update();

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 0);
  lcd.print(daysOfTheWeek[timeClient.getDay()]);
    lcd.setCursor(0, 1);
    lcd.print(timeClient.getFormattedTime());
   // lcd.print(timeClient.getEpochTime());
  //lcd.print(timeClient.getHours());
  //lcd.print(":");
  //lcd.print(timeClient.getMinutes());
  //lcd.print(":");
  //lcd.println(timeClient.getSeconds());
  
  // set cursor to first column, first row
  lcd.setCursor(0, 2);
  // print message
    lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");  

  //lcd.print("This is line 1");
  // clears the display to print new message
  // set cursor to first column, second row
  lcd.setCursor(0,3);
  lcd.print("Temp.: ");
  lcd.print(t);

  lcd.print(" Celcius");
  //lcd.print("not World!");





  //Serial.println(timeClient.getFormattedTime()); */
  
  delay(1000);
  
}

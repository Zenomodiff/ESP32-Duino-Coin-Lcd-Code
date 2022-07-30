/*feel free to contact
 * sreeramaj53@gmail.com
 * www.youtube.com/ZenoModiff
 * last updated - time 10:31 AM - date 30 june 2022
 * Github Link :-- https://github.com/Zenomodiff/ESP32-Duino-Coin-Lcd-Code
 * This code is written for esp32 with i2c lcd display and the display is 16*2 in size 
 * 
 * LCD CONNECTIONS TO ESP32
 * 
 * ESP32     I2C LCD
 * -------------------
 * 
 * GPIO22 -- SCL
 * GPIO21 -- SDA
 * GND -- GND
 * VIN -- VCC
 * 
 */


#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the i2c address accordingly 

const char* ssid = "PASTE THE WIFI SSID";
const char* password =  "PASTE THE WIFI PASSWORD";

void apiCall(){
  
if ((WiFi.status() == WL_CONNECTED)) {
HTTPClient http;

http.begin("https://server.duinocoin.com/v3/users/Sreeramzeno");

int httpCode = http.GET();
float totalHashrate = 0.0;
float avgHashrate = 0.0;
int total_miner = 0;

if (httpCode == 200) {
 
String payload = http.getString();
const size_t capacity = JSON_ARRAY_SIZE(0) + JSON_ARRAY_SIZE(5) + JSON_ARRAY_SIZE(21) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + 5*JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(10) + JSON_OBJECT_SIZE(11) + 21*JSON_OBJECT_SIZE(14) + 6310;
        
DynamicJsonDocument doc(capacity);
DeserializationError error = deserializeJson(doc, payload);
        
if (error) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Serial Error");
return;
}
    JsonObject result = doc["result"];
    JsonObject result_balance = result["balance"];
    double result_balance_balance = result_balance["balance"];
    double result_balance_stake = result_balance["stake_amount"];
    const char *result_balance_created = result_balance["created"];
    const char *result_balance_username = result_balance["username"];
    const char *result_balance_verified = result_balance["verified"];

    for (JsonObject result_miner : result["miners"].as<JsonArray>()) {
      float result_miner_hashrate = result_miner["hashrate"];
      totalHashrate = totalHashrate + result_miner_hashrate;
      total_miner++;
    }

    avgHashrate = totalHashrate / long(total_miner);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Balance :"); 
  lcd.setCursor(10,0);
  lcd.print(result_balance_balance); 
  lcd.setCursor(0,1);
  lcd.print("Stake   :"); 
  lcd.setCursor(10,1);
  lcd.print(result_balance_stake); 
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Workers :"); 
  lcd.setCursor(10,0);
  lcd.print(total_miner); 
  lcd.setCursor(0,1);
  lcd.print("Hash    :"); 
  lcd.setCursor(10,1);
  lcd.print(totalHashrate);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading.");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading..");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading...");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading....");
  
}

 else 
 {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HTTP Error");
 }
http.end();
 }
 }

void setup() {
 
Serial.begin(115200);
lcd.begin();          
lcd.backlight();
WiFi.begin(ssid, password);
lcd.setCursor(2,0);
lcd.print("Duino Stats"); 
delay(2000);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi connected");
  lcd.setCursor(1,1);
  lcd.print(WiFi.localIP());
  delay(2000);
}
 
void loop()
{
 
apiCall();
delay(3000);

}

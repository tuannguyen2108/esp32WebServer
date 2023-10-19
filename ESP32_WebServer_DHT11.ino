#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DHT.h>
#include "html.h"


const char* ssid = "Tiem Giay 2hand";
const char* pass = "0799423557";


DHT dht(4, DHT11);
const int buzzerPin = 12; 
const int pumpPin = 14; 
const int led_1 = 5;
const int led_2 = 18;
bool isLed_1_On = false;
bool isLed_2_On = false;
bool isBuzzerOn = false;
bool isPumpOn = false;
float threshold = 35.0;
bool checkTemperature = false;
WebServer server(80);

void setup(void) {

  Serial.begin(115200);
  dht.begin();
  pinMode(led_1,OUTPUT);
  pinMode(led_2,OUTPUT);
  digitalWrite(led_1,HIGH);
  digitalWrite(led_2,HIGH);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", mainpage);
  server.on("/dataDHT",get_dataDHT);
  server.on("/toggleD1",toggle_led1);
  server.on("/toggleD2",toggle_led2);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  float temperature = readDHTTemperature();
  float humidity = readDHTHumidity();
  checkBuzzer(temperature);
  checkPump(temperature);
  delay(1);//allow the cpu to switch to other tasks
}
void mainpage(){
  String s = FPSTR(MainPage);
  server.send(200,"text/html",s);
}

void toggle_led1(){
  if(isLed_1_On){
    digitalWrite(led_1,HIGH);
    isLed_1_On = false;
  }else{
    digitalWrite(led_1,LOW);
    isLed_1_On = true;
  }
  server.send(200,"text/html","TOGGLE LED 1");
}

void toggle_led2(){
  if(isLed_2_On){
    digitalWrite(led_2,HIGH);
    isLed_2_On = false;
  }else{
    digitalWrite(led_2,LOW);
    isLed_2_On = true;
  }
  server.send(200,"text/html","TOGGLE LED 2");
}
// void off_D1(){
//   digitalWrite(led_1,HIGH);
//   webServer.send(200,"text/html","CHÂN D1 ĐÃ OFF");
// }
// void on_D2(){
//   digitalWrite(led_2,LOW);
//   webServer.send(200,"text/html","CHÂN D2 ĐÃ ON");
// }
// void off_D2(){
//   digitalWrite(led_2,HIGH);
//   webServer.send(200,"text/html","CHÂN D2 ĐÃ OFF");
// }

float readDHTTemperature() {
  float t = dht.readTemperature();
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println("°C");
    return t;
  }
}

float readDHTHumidity() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println("%");
    return h;
  }
}

void checkBuzzer(float temperature) {
  if (temperature > threshold) {
    tone(buzzerPin, 1000);  // Bật còi
    isBuzzerOn = true;
  } else {
    noTone(buzzerPin); // Tắt còi
    isBuzzerOn = false;
  }
}

void checkPump(float temperature) {
  if (temperature > threshold) {
    digitalWrite(pumpPin, HIGH);
    isPumpOn = true;
  // server.send(200, "text/html", "ON"); 
  } else {
    digitalWrite(pumpPin, LOW);
    isPumpOn = false;
  // server.send(200, "text/html", "OFF"); 
  }
}

String get_status_pump(){
  if (isPumpOn) {
  return "ON"; 
  } else {
  return "OFF";
  }
}

String get_status_buzzer(){
  if (isPumpOn) {
  return "ON";
  } else {
  return "OFF";
  }
}


void get_dataDHT(){
  float temperature = readDHTTemperature(); // Đọc nhiệt độ từ cảm biến DHT
  float Humidity = readDHTHumidity(); // Đọc nhiệt độ từ cảm biến DHT
  String buzzer = get_status_buzzer();
  String pump = get_status_pump();
  String temperatureStr = String(temperature);
  String HumidityStr = String(Humidity);
  String s = "{\"Temperature\": \""+ temperatureStr +"\",\"Humidity\": \""+ HumidityStr +"\",\"Pump\": \""+ pump +"\",\"Buzzer\": \""+ buzzer +"\"}";
  server.send(200, "text/html", s); // Gửi nhiệt độ dưới dạng chuỗi

}



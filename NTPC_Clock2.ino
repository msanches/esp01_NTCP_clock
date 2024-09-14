#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "preencher com o SSID da rede"; 
const char* password = "preencher com a senha da rede"; 

WiFiUDP udp;
NTPClient ntp(udp, "b.ntp.br", -3 * 3600, 60000);  // mude o fuso horário de acordo com a região onde você está

#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* SLC=*/5, /* SDA=*/6, /* reset=*/U8X8_PIN_NONE);  

const char DEGREE_SYMBOL[] = { 0xB0, '\0' };  //Símbolo de graus º

String hora;  //armazena as horas
String formattedDate;
String dateStamp, year, month, date;
char dateBuffer[] = "";
char* monthArray[12] = { "Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez" };
char daysOfTheWeek[7][12] = { "Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado" };

#include "DHT.h"           // Include DHT library
#define DHTPIN 5           // DHT11 data pin is connected to ESP8266 PIN GPIO1 (TXD) MÓDULO 12F PIN 5
#define DHTTYPE DHT11      // DHT11 sensor is used
DHT dht(DHTPIN, DHTTYPE);  // Configure DHT library

int humidity, temp;  // Values read from sensor

void setup() {

  Serial.begin(9600);  // Serial connection from ESP-01 via 3.3v console cable
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("\n\r \n\rTentando conectar");

  // Wait for connection
  Serial.println("Conectando ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connectado a rede: ");
  Serial.println(ssid);
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  //Inicializa o ntp client
  ntp.begin();
  ntp.forceUpdate();
  //Inicializa o LCD
  u8g2.begin();
  u8g2.enableUTF8Print();
  //Inicializa o sensor DHT11
  dht.begin();
}

void loop() {
  // Read humidity
  humidity = dht.readHumidity();
  //Read temperature in degree Celsius
  temp = dht.readTemperature();
  // Check if any reads failed and exit early (to try again)
  if (isnan(humidity) || isnan(temp)) {
    //humidity = 65;
    //temp = 25;
    Serial.println("Erro");
    return;
  } else {
    Serial.print(humidity, temp);
  }

  hora = ntp.getFormattedTime();
  formattedDate = ntp.getFormattedDate();

  year = formattedDate.substring(0, 4);
  month = formattedDate.substring(5, 7);
  month = monthArray[month.toInt() - 1];
  date = formattedDate.substring(8, 10);
  date = String(date.toInt());
  dateStamp = date + "/" + month + "/" + year;
  dateStamp.toCharArray(dateBuffer, dateStamp.length() + 1);

  u8g2.firstPage();
  do {
    //keep this the same as it pages through the data generating the screen
    // u8g2_font_7x13_m_symbols | u8g2_font_profont12_mr | u8g2_font_6x13_mf
    u8g2.setFont(u8g2_font_6x13_mf);
    u8g2.drawStr(0, 10, daysOfTheWeek[ntp.getDay()]);
    u8g2.drawStr(60, 10, dateStamp.c_str());
    u8g2.setFont(u8g2_font_profont29_mn);
    u8g2.drawStr(0, 38, hora.c_str());
    u8g2.setFont(u8g2_font_streamline_weather_t);
    u8g2.drawStr(0, 65, "6");
    // u8g2_font_ncenB10_tf | u8g2_font_profont12_mr
    u8g2.setFont(u8g2_font_ncenB10_tf);
    u8g2.drawStr(23, 63, String(temp).c_str());
    u8g2.drawUTF8(42, 63, DEGREE_SYMBOL);
    u8g2.drawStr(50, 63, "C");
    u8g2.setFont(u8g2_font_ncenB10_tf);
    u8g2.drawStr(80, 63, String(humidity).c_str());
    u8g2.drawStr(100, 63, "%");
  } while (u8g2.nextPage());
  Serial.println(hora);
  delay(1000);
}

// ESP modulu Thingspeak.com sitesine sıcaklik gönderecek
#include <ESP8266WiFi.h>
#include "ThingSpeak.h" 
//************************************************************
const char *ssid = "************";      // baglanilacak olan wifi aginin adi  
const char *password = "*********";      // baglanilacak olan wifi aginin sifresi

#define SECRET_CH_ID xxxxx            // Secret channel ID si
const char *SECRET_WRITE_APIKEY = "xxxxxxxxxxxxxxxxx";  // write api key

float sicaklik=0.0, nem=0.0;

WiFiClient  wifi_istemci;
//************************************************************
void setup() {
  Serial.begin(9600);                   //seri portu baslat
  delay(1500);                          // 1500 ms = 1.5sn
  Serial.println("Wifi agına baglanıyor");
  
  WiFi.mode(WIFI_STA);                  // istasyon modunda çalış
  WiFi.begin(ssid, password);           // SSID si yukarıda belirtilmiş olan wifi a bağlan
  
  while (WiFi.status() != WL_CONNECTED) // baglanti kuruldu mu?
  {                                     // kurulmadiysa kurulana kaddar 
    delay(500);                         // 500 ms bekle
    Serial.print(".");                  // ekrana . koy    
  }
  
  Serial.println("");
  Serial.println("Wifi erisim noktasina baglanildi");

  Serial.print("Alinan IP adresi: ");
  Serial.println(WiFi.localIP());       // wifi agindan alinan IP adresini yazdir.

  ThingSpeak.begin(wifi_istemci);  // Initialize ThingSpeak
}
//************************************************************
void loop() 
{
 sicaklik=24.8; nem=50.0;
 ThingSpeak.setField(1,sicaklik);
 ThingSpeak.setField(2,nem);
 ThingSpeak.setField(3,45);

 int x = ThingSpeak.writeFields(SECRET_CH_ID, SECRET_WRITE_APIKEY);    // alan 1 e sicaklik yaz
  if(x == 200)
    Serial.println("Kanala veri yazildi!");
  else
    Serial.println("Kanala yazma basarisiz. HTTP error code " + String(x));
  
  delay(18000);     // thingspeak sitesi 15sn de bir güncelleme yapıyor o yüzden 18sn bekle
}

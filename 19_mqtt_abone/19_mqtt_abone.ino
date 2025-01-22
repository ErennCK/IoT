// MQTT abone örnek uygulaması
//****************************************************************
#include <ESP8266WiFi.h>
#include <MQTTClient.h>

const char *agin_adi = "xxxxxxxx";        // baglanilan wifi aginin adi
const char *sifre = "xxxxxx";             // baglanilan wifi aginin sifresi,min 8 karakter

WiFiClient wifi_istemci;                  // wifi istemci nesnesi
MQTTClient mqtt_istemci;                  // mqtt istemci nesnesi
//****************************************************************
void setup() 
{
  Serial.begin(9600);                           // seri portu başlat 
  delay(200);                                   // 200 ms bekle
  Serial.println("Wifi agina baglaniyoruz");  

  WiFi.mode(WIFI_STA);                          // istasyon modunda calis
  WiFi.begin(agin_adi, sifre);                  // wifi agina baglan

  //------- Wifi ağına bağlanıncaya kadar beklenilen kısım ------------
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500);                                 // Bu arada her 500 ms de bir seri ekrana yan yana noktalar yazdırılarak
    Serial.print(".");                          //görsellik sağlanıyor.
  }
  //-------------------------------------------------------------------
  
  Serial.println("");                           //Bir alt satıra geçiliyor.
  Serial.println("Bağlantı sağlandı...");       //seri ekrana bağlantının kurulduğu bilgisi gönderiliyor.

  Serial.print("Alınan IP addresi: ");          // kablosuz ağdan alınan IP adresi
  Serial.println(WiFi.localIP());               // kablosuz ağdan alınan IP adresi

  mqtt_istemci.begin("xxxxxxxxxxxxxxxxxxxxx", wifi_istemci);   // mqtt istemciyi başlat, ilk parametre web veya IP adresi
  mqtt_istemci.onMessage(mesaj_geldi);          // mesaj geldiğinde gidilecek fonksiyon
}
//****************************************************************
void loop() 
{
  mqtt_istemci.loop();      // broker a msj göndermek için gerekli olan satır
  
  if (!mqtt_istemci.connected())  // broker a bağlandı mı?
    baglan();                     // bağlanmamış, baglan()

  mqtt_istemci.subscribe("xxxxxx"); //xxxxx konusuna abone ol
  delay(1000);
}
//****************************************************************
void baglan()
{
   while (!mqtt_istemci.connect("xxxx", "yyyy", "zzzz"))    // 1. parametre gözükecek adınız, 2. parametre proje adı, 3. token
   {
    Serial.print(",");
    delay(1000);
  }
}
//****************************************************************
void mesaj_geldi(String &konu, String &veri) {
  Serial.println(konu + ": " + veri);     // gelen veri ile konuyu ekrana yazdır
}

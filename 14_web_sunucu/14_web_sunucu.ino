// ESP modlununu erisim noktasi olarak ayarla ve uzerinde WEB sunucu calistir
// ag_adi ve şifreyi belirleyiniz
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *agin_adi = "xxxxxxxxxxxx";// olusturulan wifi aginin adi
const char *sifre = "xxxxxxxx";     // olusturulan wifi aginin sifresi,min 8 karakter

ESP8266WebServer sunucu(80);        // sunucu nesnensini olusturup, 80 portunu kullan
//************************************************************
void setup() {
  Serial.begin(9600);               // seri portu baslat
  delay(2000);                      // 2sn bekleme
  Serial.println("Erisim noktasi baslatiliyor...");
  WiFi.softAP(agin_adi, sifre);      // soft access point i baslat

  Serial.print("AP IP address: ");  // acces point in IP adresini goster
  Serial.println(WiFi.softAPIP());  // acces point in IP adresini goster
  
  sunucu.on("/", anasayfa_fonk);          // 192.168.x.x/ adresi tiklaninca anasyfa foksiyonunu calistir
  sunucu.on("/iletisim", iletisim_fonk);  // 192.168.x.x/iletisim adresi tiklaninca iletisim_fonk foksiyonunu calistir                                    
  
  sunucu.begin();                   // sunucuyu baslat
  Serial.println("WEB sunucusu basladi");
}
//************************************************************
void loop() {
  sunucu.handleClient();            // sunucuya baglanan istemcileri karsila
}
//************************************************************
void anasayfa_fonk() 
{ // anasayfa tiklaninca Baglandiniz yazisi gonderiliyor                
  sunucu.send(200, "text/html", "<h1>Baglandiniz</h1>");
}
//************************************************************
void iletisim_fonk() 
{ // 192.168.x.x/iletisim adresi tiklaninca numara gonderiliyor                
  sunucu.send(200, "text/html", "<h1>Tlf:0274 2222222</h1>");
}

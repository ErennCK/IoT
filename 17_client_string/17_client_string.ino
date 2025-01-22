//Nodemcu agin_adi ile var olan bir aga baglaniyor. Bu ag ile erişebilecegi checkip.dyndns.org sunucusuna 
// baglanip oradan web sayfasını http protokolü ile istiyor, gelen veride IP adresini filtreliyor
#include <ESP8266WiFi.h>

const char *agin_adi = "xxxxxxxxx";				  // baglanilan wifi aginin adi
const char *sifre = "xxxxxxxxx";     				// baglanilan wifi aginin sifresi,min 8 karakter

const char* web_adresi = "checkip.dyndns.org";		    // baglanilacak web sunucu adresi veya IP adresi
const uint16_t port = 80;							      // baglanilacak sunucu portu

String uzanti="/";					       // baglanilacak olan web sayfasinin uzantisi 
WiFiClient istemci;                        // istemci nesnesini oluştur
//****************************************************************
void setup() 
{
  Serial.begin(9600);   						            // seri portu başlat 
  delay(200);                                   // 200 ms bekle
  Serial.println("Wifi agina baglaniyoruz");	

  WiFi.mode(WIFI_STA);							            // istasyon modunda calis
  WiFi.begin(agin_adi, sifre);					        // wifi agina baglan

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
}
//*******************************************************
void loop() 
{
  //----------------- sunucuya bağlanma -------------------- 
  if (!istemci.connect(web_adresi, port)) {
    Serial.println("Sunucuya baglanma hatasi");
    delay(5000);
    return;
  }
  Serial.println("WEB sunucusuna baglandi");
  delay(2000);
  
  //--------------- sunucudan sayfa isteme -----------------
  String http_req="";
  http_req+="GET ";
  http_req+=uzanti;
  http_req+=" HTTP/1.1\r\n";
  http_req+="Host: ";
  http_req+=web_adresi;
  http_req+="\r\n";
  http_req+="Connection: close\r\n";
  /*
  GET / HTTP/1.1
  Host: www......com
  Connection: close
  */
  istemci.println(http_req);
  //------------------ isteme sonu -----------------------
  
  //-------- 5 sn lik zaman döngüsü kur ve istek geldi mi diye kontrol et ------
  // çalışma zamanı milisaniye cinsinden tutan millis() fonksiyonundan süre al, başlangıc zamanı
  unsigned long onceki_zaman = millis();    
  while (istemci.available() == 0) {
    if (millis() - onceki_zaman > 5000) {   
      Serial.println("Baglanti hatasi");
      istemci.stop();
      delay(2000);
      return;
    }
  }
    //-------------- veri gelmis satır satır oku ekrana yazdır --------------------
  while (istemci.available()) 
  {
    String satir=istemci.readStringUntil('\r');
    //Serial.println(satir);      // bu satır ilk önce tek başına olacak, seri portta gelen veriye bakacaz, sonra yorum yapacaz

    //------------ IP adresini filtreleme kısmı -------------------
    if(satir.indexOf("Address: ")!=-1)
    {
      int baslangic=satir.indexOf("Address: ");
      int bitis=satir.indexOf("</body>");
      
      String yazi="Address: ";
      int uzunluk=yazi.length();
      String ip_adresim=satir.substring(baslangic+uzunluk,bitis);

      /* ..... yukarıdaki 3 satır yerine bu şekilde de olabilir .....
       * String ip_adresim=satir.substring(baslangic+9,bitis);
      */

      Serial.println(ip_adresim);
    }
  }
  Serial.println("-------------------------");
  istemci.stop();
  delay(2000);  
}

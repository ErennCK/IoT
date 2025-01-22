byte pinler[7]={D7,D6,D5,D4,D3,D2,D1};		// seven segment pinleri
//                  0  , 1  , 2  ,  3 ,  4 ,  5 , 6  , 7  , 8  ,  9
byte degerler[10]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};
byte sayac=0;
//******************************************
void setup() {
  for(int i=0;i<7;i++)
    pinMode(pinler[i],OUTPUT);		// seven segmente gidien pinler çıkış
}
//******************************************
void loop() 
{
   goster(sayac);
   sayac++;
   if(sayac>9)		// sayac 9 dan buyuk olunca sıfırlamak için
    sayac=0;
   delay(1000);  
}
//*****************************************
void goster(byte gelen_sayac)
{
  byte sonuc=0;
  for(int i=0;i<7;i++)
  {
    sonuc= degerler[gelen_sayac] & (B10000000 >> i);		// maske sayısını (10000000) i kadar sağa kaydır, sayı ile and'le

    if(sonuc!=0)
      digitalWrite(pinler[i],HIGH);
    else
      digitalWrite(pinler[i],LOW);
  }
  
}

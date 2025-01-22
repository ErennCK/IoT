// D8 e bağlı butona basılınca D0 daki ledi yakan program
//********************************************************************
#define buton_pin D8			// D8 portunu buton_pin olarak tanımla
//********************************************************************
byte pinler[4]={D1,D2,D3,D4};   // yarım yanan ledleri söndürmek için
//********************************************************************
void setup() {
  // put your setup code here, to run once:
  pinMode(D0,OUTPUT);           // D0 daki ledi yakmak için çıkış olarak ayarla
  pinMode(buton_pin, INPUT);    // D8 portunu giriş yap
  digitalWrite(D0, LOW);        // ledi söndür default açılış
 
  for(byte i=0;i<4;i++)         // yarım yanan ledleri söndürmek için
  {  
    pinMode(pinler[i],OUTPUT);
    digitalWrite(pinler[i],LOW);
  }
}
//********************************************************************
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(buton_pin)==HIGH)		// butona basıldı mı?
    digitalWrite(D0,HIGH);      // butona basıldıysa Ledi yak
  else
    digitalWrite(D0,LOW);       // butona basılmadıysa Ledi söndür

  delay(250);                   // 250 ms buton arkları geçmesi için gecikme  
}

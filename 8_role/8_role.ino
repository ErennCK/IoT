#define relay_pin D6
#define buton_pin D8
//-----------------------------------------
void setup() {
  pinMode(relay_pin, OUTPUT);	// röle pinini çıkış yap
  pinMode(buton_pin, INPUT);	// buton pinini giriş yap
}
//-----------------------------------------
void loop() {
   if(digitalRead(buton_pin)==HIGH)		// butona basıldı mı?
    digitalWrite(relay_pin, HIGH);		// basıldı röleyi çektir
   else
    digitalWrite(relay_pin, LOW);		// basılmadı röleyi bıraktır
   delay(250);							// buton arklarının sönmesi için 250 ms bekle
}

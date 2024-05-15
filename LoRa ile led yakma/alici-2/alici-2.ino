//ALICI2

#include "LoRa_E220.h"          // LoRa_E220 kütüphanesi dahil ediliyor
#include <SoftwareSerial.h>     // SoftwareSerial kütüphanesi dahil ediliyor
SoftwareSerial mySerial(2, 3);  // SoftwareSerial nesnesi oluşturuluyor, RX pin 2, TX pin 3 olarak ayarlanıyor
LoRa_E220 E220(&mySerial);      // LoRa_E220 nesnesi oluşturuluyor, SoftwareSerial nesnesi parametre olarak iletiliyor

#define M0 7    // M0 pinini 7 numaralı pine atama
#define M1 6    // M1 pinini 6 numaralı pine atama
#define LED_PIN 13 // LED'in bağlı olduğu pin

struct veriler {    // veriler adında bir yapı tanımlanıyor
  int    deger1;    // deger1 adında bir tamsayı tanımlanıyor
  int    deger2;    // deger2 adında bir tamsayı tanımlanıyor
  int    deger3;    // deger3 adında bir tamsayı tanımlanıyor
} data;             // data adında bir veriler yapı örneği oluşturuluyor
 
void setup() {
  pinMode(M0, OUTPUT);  // M0 pinini çıkış olarak ayarla
  pinMode(M1, OUTPUT);  // M1 pinini çıkış olarak ayarla
  digitalWrite(M0, LOW); // M0 pinini düşük (LOW) seviyeye ayarla
  digitalWrite(M1, LOW); // M1 pinini düşük (LOW) seviyeye ayarla
  Serial.begin(9600);  // Seri iletişim başlatılıyor, hız 9600 baud
  E220.begin();        // LoRa_E220 nesnesi başlatılıyor
  pinMode(LED_PIN, OUTPUT); // LED pinini çıkış olarak ayarla
  delay(500);          // 500 milisaniye bekle
}

void loop() {
  while (E220.available() > 1) { // LoRa modülünden veri alınabildiği sürece döngüye gir
  
    // Gelen mesaj okunuyor
    ResponseStructContainer rsc = E220.receiveMessage(sizeof(veriler));
    struct veriler data = (veriler) rsc.data; // Gelen veri, veriler yapısına dönüştürülüyor
    Serial.println("Gelen Messaj: "); // Seri port üzerine bilgi yazdırılıyor
    Serial.println(data.deger1); // Gelen verinin deger1 elemanı yazdırılıyor
    delay(500);
    Serial.println(data.deger2); // Gelen verinin deger2 elemanı yazdırılıyor
    delay(500);
    Serial.println(data.deger3); // Gelen verinin deger3 elemanı yazdırılıyor
    delay(500);
    rsc.close(); // Alınan mesajın işlemi tamamlandı, kapatılıyor

    digitalWrite(LED_PIN, data.deger1); // LED'i yak
    delay(1000); // 1 saniye bekle
    digitalWrite(LED_PIN, data.deger2); // LED'i söndür
    delay(1000); // 1 saniye bekle
    digitalWrite(LED_PIN, data.deger3); // LED'i yak
    delay(1000); // 1 saniye bekle
  }
}

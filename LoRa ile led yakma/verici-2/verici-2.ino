/// VERİCİ2

#include "LoRa_E220.h"          // LoRa_E220 kütüphanesi dahil ediliyor
#include <SoftwareSerial.h>     // SoftwareSerial kütüphanesi dahil ediliyor
SoftwareSerial mySerial(2, 3);  // SoftwareSerial nesnesi oluşturuluyor, RX pin 2, TX pin 3 olarak ayarlanıyor
LoRa_E220 E220(&mySerial);      // LoRa_E220 nesnesi oluşturuluyor, SoftwareSerial nesnesi parametre olarak iletiliyor

#define M0 7    // M0 pinini 7 numaralı pine atama
#define M1 6    // M1 pinini 6 numaralı pine atama

struct veriler {    // veriler adında bir yapı tanımlanıyor
  int    deger1;    // deger1 adında bir tamsayı tanımlanıyor
  int    deger2;    // deger2 adında bir tamsayı tanımlanıyor
} data;             // data adında bir veriler yapı örneği oluşturuluyor

void setup() {
  pinMode(M0, OUTPUT);  // M0 pinini çıkış olarak ayarla
  pinMode(M1, OUTPUT);  // M1 pinini çıkış olarak ayarla
  digitalWrite(M0, LOW); // M0 pinini düşük (LOW) seviyeye ayarla
  digitalWrite(M1, LOW); // M1 pinini düşük (LOW) seviyeye ayarla

  Serial.begin(9600);  // Seri iletişim başlatılıyor, hız 9600 baud
  E220.begin();        // LoRa_E220 nesnesi başlatılıyor
  delay(500);          // 500 milisaniye bekle
}

void loop() {
  data.deger1 = 0;   // data yapısının deger1 elemanına 0 değeri atanıyor
  data.deger2 = 1;   // data yapısının deger2 elemanına 1 değeri atanıyor
   
  // E220.sendFixedMessage() fonksiyonuyla veri gönderiliyor, sonuç ResponseStatus tipinde bir değişkene atanıyor
  ResponseStatus rs = E220.sendFixedMessage(0, 0, 1, &data, sizeof(veriler));
  
  // Gönderim sonucunun açıklaması seri port üzerinden yazdırılıyor
  Serial.println(rs.getResponseDescription());

  delay(2000);  // 2 saniye bekle
}

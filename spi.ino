#include <SPI.h>

#define SS_SD 4  // Slave Select untuk SD card
#define SS_TFT 10 // Slave Select untuk layar TFT

void setup() {
    SPI.begin(); // Inisialisasi SPI sebagai master
    pinMode(SS_SD,  );
    pinMode(SS_TFT, OUTPUT);

    digitalWrite(SS_SD, HIGH); // Nonaktifkan SD card
    digitalWrite(SS_TFT, HIGH); // Nonaktifkan layar TFT
    Serial.begin(9600);
}

void loop() {
    // Berkomunikasi dengan SD card
    digitalWrite(SS_SD, LOW); // Pilih SD card
    SPI.transfer(0x58); // Contoh perintah ke SD card
    digitalWrite(SS_SD, HIGH); // Nonaktifkan SD card

    // Berkomunikasi dengan layar TFT 
    digitalWrite(SS_TFT, LOW); // Pilih layar TFT
    SPI.transfer(0x42); // Contoh perintah ke layar TFT
    digitalWrite(SS_TFT, HIGH); // Nonaktifkan layar TFT

    delay(1000); // Delay 1 detik
}

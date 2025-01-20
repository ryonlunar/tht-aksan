#include <Wire.h>

void setup() {
    Wire.begin(); // Menginisialisasi I2C sebagai master
    Serial.begin(9600);
}

void loop() {
    // Berkomunikasi dengan sensor suhu (MPU6050)
    Wire.beginTransmission(0x68); // Alamat slave sensor
    Wire.write(0x3B); // Contoh register yang dibaca
    Wire.endTransmission();
    
    Wire.requestFrom(0x68, 2); // Meminta 2 byte data dari slave
    int temperature = Wire.read() << 8 | Wire.read(); // Membaca data suhu
    Serial.print("Temperature: ");
    Serial.println(temperature);

    // Berkomunikasi dengan RTC (DS3231)
    Wire.beginTransmission(0x57); // Alamat slave RTC
    Wire.write(0x00); // Memulai membaca dari register 0x00
    Wire.endTransmission();

    Wire.requestFrom(0x57, 3); // Meminta data waktu (jam, menit, detik)
    int seconds = Wire.read();
    int minutes = Wire.read();
    int hours = Wire.read();
    Serial.print("Time: ");
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.println(seconds);

    delay(1000); // Delay 1 detik
}
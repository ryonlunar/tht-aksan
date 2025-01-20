#include <avr/io.h>
#include <Arduino.h>

const int pwmFrequency = 1000;  // Frekuensi PWM dalam Hz (1 kHz)
const int dutyCycle = 50;       // Duty cycle dalam persen (50%)
unsigned long period;           // Periode PWM dalam mikrodetik
unsigned long onTime;           // Waktu ON dalam mikrodetik
unsigned long offTime;          // Waktu OFF dalam mikrodetik
unsigned long lastTime = 0;     // Waktu terakhir perubahan status
bool pwmState = false;          // Status PWM (ON atau OFF)

void setup() {
  Serial.begin(9600);  // Inisialisasi Serial Monitor

  // Hitung periode, waktu ON, dan waktu OFF
  period = 1000000 / pwmFrequency;          // Periode dalam mikrodetik
  onTime = period * dutyCycle / 100;        // Waktu ON dalam mikrodetik
  offTime = period - onTime;                // Waktu OFF dalam mikrodetik

  Serial.println("Simulasi PWM dimulai:");
  Serial.print("Frekuensi: ");
  Serial.print(pwmFrequency);
  Serial.println(" Hz");
  Serial.print("Duty Cycle: ");
  Serial.print(dutyCycle);
  Serial.println(" %");
}

void loop() {
  unsigned long currentTime = micros();  // Ambil waktu sekarang

  if (pwmState && (currentTime - lastTime >= onTime)) {
    // Beralih ke OFF setelah waktu ON selesai
    pwmState = false;
    lastTime = currentTime;
    Serial.println("PWM: OFF");
  } else if (!pwmState && (currentTime - lastTime >= offTime)) {
    // Beralih ke ON setelah waktu OFF selesai
    pwmState = true;
    lastTime = currentTime;
    Serial.println("PWM: ON");
  }
}
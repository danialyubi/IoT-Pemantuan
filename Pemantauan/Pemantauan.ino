#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4      // Pin data sensor DHT22 dihubungkan ke pin 4
#define DHTTYPE DHT22 // Tipe sensor DHT yang digunakan (DHT22)
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);
int buzzerPin = 15;
int ledPin = 15;                // Deklarasi variabel input pin LED
int inputPin = 14;               // Deklarasi variabel input pin Sensor PIR
int pirState = LOW;             // Pada saat memulai, Sensor PIR dimulai dari LOW
int val = 0;                    // Deklarasi variabel untuk membaca status pin

void setup() {
  pinMode(ledPin, OUTPUT);      // Deklarasi LED sebagai Output
  pinMode(inputPin, INPUT);     // Deklarasi Sensor PIR sebagai Input
  pinMode(buzzerPin, OUTPUT);   
  Serial.begin(9600);
  LCD.init();
  LCD.backlight();
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  tone(buzzerPin, 100, 1000);
  LCD.setCursor(1,0);
  LCD.print("  Pemantuan keamanan  ");
  LCD.setCursor(1,1);
  LCD.print("  Gudang  ");
  delay (500);
  LCD.clear();

  dht.begin();  // Inisialisasi sensor DHT22
}

void loop() {
  val = digitalRead(inputPin);  // Membaca nilai input
  if (val == HIGH) {            // Jika Input HIGH, maka :
    digitalWrite(ledPin, HIGH); // Menyalakan LED
    digitalWrite(buzzerPin, HIGH); // Menyalakan buzzer
    if (pirState == LOW) {
       // Jika, input HIGH maka akan LCD akan mengeluarkan output "TERDETEKSI GERAKAN"
      LCD.clear();
      LCD.setCursor(0,0);
      LCD.print("   Ada Gerakan");
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);  // LED tidak menyala
    digitalWrite(buzzerPin, LOW); // Buzzer mati
    if (pirState == HIGH) {
      // Jika, input LOW maka akan LCD akan mengeluarkan output "TIDAK TERDETEKSI GERAKAN"
      LCD.clear();
      LCD.setCursor(0,0);
      LCD.print("Tidak ada Gerakan");
      pirState = LOW;
    }
  }

  // Membaca suhu dan kelembaban dari sensor DHT22
  float humidity = dht.readHumidity();       // Baca kelembaban
  float temperature = dht.readTemperature(); // Baca suhu dalam derajat Celsius
  
  // Menampilkan suhu dan kelembaban di layar LCD
  LCD.setCursor(0,1);
  LCD.print("Humidity: ");
  LCD.print(humidity);
  LCD.print("%     Temp:");
  LCD.print(temperature);
  LCD.print("C ");
  
  delay(2000);  // Delay 2 detik sebelum membaca data lagi
}
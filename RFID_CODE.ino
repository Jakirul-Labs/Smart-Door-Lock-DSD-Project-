#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RFID Reader 1 (Entry)
#define RST_PIN_1 16//15
#define SS_PIN_1 4//2

// RFID Reader 2 (Exit)
#define RST_PIN_2 15//16
#define SS_PIN_2 2//4

#define RELAY_PIN 25
#define BUZZER_PIN 26

// Wi-Fi credentials
const char* ssid = "Jakirul";
const char* password = "00998877";

// Google Apps Script URL
// Your google sheed link
const char* scriptURL = "https://script.google.com/macros/s/AKfycbyv5NRyZ_z3h5EZJE1VcFLMFjJzvzygh7JirOvgVnOY29UKvlKLSYz-2VjsqnEXAJ0i/exec";

// Create RFID instances
MFRC522 rfid1(SS_PIN_1, RST_PIN_1);
MFRC522 rfid2(SS_PIN_2, RST_PIN_2);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Cardholder structure
struct CardHolder {
  String uid;
  String name;
  String id;
  String batch;
};

CardHolder holders[] = {
  {"63 62 81 16", "Jakirul", "1065", "Batch59"},
  {"C3 CB 21 15", "Jarin", "1055", "Batch59"},
  {"43 F3 E7 14", "Sumaiya", "1086", "Batch59"},
  {"C3 C8 0F 15", "Rakibul", "1059", "Batch59"},
  {"E3 69 1F 16", "Shaiek", "1087", "Batch59"},
};

void setup() {
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.setCursor(0, 1);
  lcd.print("WiFi Connected");

  // Initialize RFID readers
  SPI.begin();
  rfid1.PCD_Init();
  rfid2.PCD_Init();

  // Set pin modes
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Turn off initially
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);
}

// Convert UID to string
String getUID(MFRC522& rfid) {
  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uidStr += "0";
    uidStr += String(rfid.uid.uidByte[i], HEX);
    if (i != rfid.uid.size - 1) uidStr += " ";
  }
  uidStr.toUpperCase();
  return uidStr;
}

// Find cardholder
CardHolder* getCardHolder(String uid) {
  for (CardHolder& holder : holders) {
    if (holder.uid == uid) {
      return &holder;
    }
  }
  return nullptr;
}

// Log to Google Sheets
void logToGoogleSheets(String name, String id, String batch, String type) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(scriptURL) + "?name=" + name + "&id=" + id + "&batch=" + batch + "&type=" + type;

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Logged to Google Sheets: " + type);
    } else {
      Serial.println("HTTP Error: " + String(httpCode));
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

// Handle RFID card scan
void handleCard(MFRC522& rfid, String type) {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  String uid = getUID(rfid);
  Serial.println("Detected UID: " + uid);

  CardHolder* holder = getCardHolder(uid);

  if (holder != nullptr) {
    // Known card
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(holder->name);
    lcd.setCursor(0, 1);
    lcd.print(type);

    // Unlock relay (which controls the solenoid)
    digitalWrite(RELAY_PIN, LOW);  // Corrected from SOLENOID_PIN to RELAY_PIN
    tone(BUZZER_PIN, 100); // beep
    delay(1000);
    digitalWrite(RELAY_PIN, HIGH);   // Corrected from SOLENOID_PIN to RELAY_PIN
    noTone(BUZZER_PIN);

    // Log data
    logToGoogleSheets(holder->name, holder->id, holder->batch, type);
  } else {
    // Unknown card
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unknown Card");
    tone(BUZZER_PIN, 100);
    delay(1000);
    noTone(BUZZER_PIN);
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);
}

void loop() {
  handleCard(rfid1, "Entry");
  handleCard(rfid2, "Exit");
}
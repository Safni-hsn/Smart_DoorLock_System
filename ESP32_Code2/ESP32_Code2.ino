#define BLYNK_TEMPLATE_ID "TMPL6eCrDXuVZ"
#define BLYNK_TEMPLATE_NAME "Door Lock"
#define BLYNK_AUTH_TOKEN "QLqn43Gv9ScJuZTpj3FZpgfBYa6C20jA"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

const char *ssid = "Dialog 4G 538";
const char *password = "7B3Df4e1";

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust address and size if needed
Servo myServo;
const int pirPin = 4;    // Adjust pin number as per your setup
const int servoPin = 15; // Adjust pin number as per your setup
const int passwordLength = 4;
char enteredPassword[passwordLength + 1];
char correctPassword[passwordLength + 1] = "1234"; // Make this non-const to allow updates
char newPassword[passwordLength + 1];
byte currentLength = 0;
bool movementDetected = false;
unsigned long pirDebounceTime = 0;
const unsigned long pirDebounceDelay = 2000; // 2 seconds debounce delay

int incorrectTries = 0;
const int maxIncorrectTries = 3;
bool isLocked = false;
bool doorOpen = false;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {14, 27, 26, 25};
byte colPins[COLS] = {33, 32, 13, 12};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void askForPassword()
{
  lcd.clear();
  lcd.print("Enter Keycode:");
  currentLength = 0;
}

void checkPassword()
{
  if (strcmp(enteredPassword, correctPassword) == 0)
  {
    lcd.clear();
    lcd.print("Access Granted");
    Blynk.logEvent("access_granted", "Access Granted"); // Send push notification
    myServo.write(90);                                  // Adjust servo open position
    Blynk.virtualWrite(V1, "Door Status: Open");        // Update label to Open
    doorOpen = true;                                    // Set door status to open
    delay(5000);
    lcd.clear();
    lcd.print("System Ready");
    movementDetected = false; // Reset movement detection
    incorrectTries = 0;       // Reset incorrect tries
  }
  else
  {
    lcd.clear();
    lcd.print("Access Denied");
    Blynk.logEvent("access_denied", "Access Denied"); // Send push notification
    incorrectTries++;
    if (incorrectTries >= maxIncorrectTries)
    {
      isLocked = true;
      Blynk.logEvent("system_locked", "System Locked due to multiple incorrect attempts.");
      lcd.clear();
      lcd.print("System Locked");
      Blynk.virtualWrite(V1, "Door Status: Locked");
    }
    else
    {
      delay(3000);
      askForPassword(); // Ask for password again
    }
  }
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  if (pinValue == 1)
  {
    isLocked = false;
    incorrectTries = 0;
    lcd.clear();
    lcd.print("System Reset");
    delay(2000);
    lcd.clear();
    lcd.print("System Ready");
    Blynk.virtualWrite(V1, "Door Status: Closed");
    Blynk.virtualWrite(V2, 0); // Reset the switch/button state
  }
}

BLYNK_WRITE(V3)
{
  String blynkPassword = param.asStr();
  if (blynkPassword.length() == passwordLength)
  {
    blynkPassword.toCharArray(enteredPassword, passwordLength + 1);
    checkPassword();
  }
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt();
  if (pinValue == 1 && doorOpen)
  {
    myServo.write(0); // Close the door
    doorOpen = false;
    lcd.clear();
    lcd.print("Door Closed");
    Blynk.virtualWrite(V1, "Door Status: Closed"); // Update label to Closed
    delay(2000);
    lcd.clear();
    lcd.print("System Ready");
    Blynk.virtualWrite(V4, 0); // Reset the button state
  }
}

BLYNK_WRITE(V5)
{
  String blynkNewPassword = param.asStr();
  if (blynkNewPassword.length() == passwordLength)
  {
    blynkNewPassword.toCharArray(newPassword, passwordLength + 1);
    strcpy(correctPassword, newPassword); // Update the correct password
    lcd.clear();
    lcd.print("Password Changed");
    delay(2000);
    lcd.clear();
    lcd.print("System Ready");
  }
  else
  {
    lcd.clear();
    lcd.print("Invalid Password");
    delay(2000);
    lcd.clear();
    lcd.print("System Ready");
  }
}

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  lcd.init();
  lcd.backlight();
  lcd.print("Connecting...");

  unsigned long wifiStartTime = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    if (millis() - wifiStartTime >= 10000)
    { // 10 seconds timeout
      Serial.println("WiFi connection failed");
      lcd.clear();
      lcd.print("WiFi failed");
      break;
    }
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected");
    lcd.clear();
    lcd.print("WiFi connected");
  }

  myServo.attach(servoPin);
  myServo.write(0); // Ensure the door is closed initially
  pinMode(pirPin, INPUT);
  lcd.clear();
  lcd.print("System Ready");
  Blynk.virtualWrite(V1, "Door Status: Closed"); // Initialize label status to Closed
}

void loop()
{
  Blynk.run(); // Run Blynk

  if (isLocked)
  {
    lcd.clear();
    lcd.print("System Locked");
    delay(2000);
    return;
  }

  if (digitalRead(pirPin) == HIGH && millis() - pirDebounceTime > pirDebounceDelay)
  {
    pirDebounceTime = millis();
    movementDetected = true;
    Serial.println("Movement detected, ask for keycode");
    Blynk.logEvent("pir_sensor", "Movement detected, please enter the keycode."); // Send push notification
    askForPassword();
    delay(2000);
  }

  if (movementDetected || doorOpen)
  {
    char key = keypad.getKey();
    if (key)
    {
      if (key == '#')
      {
        if (doorOpen)
        {
          myServo.write(0); // Close the door
          doorOpen = false;
          lcd.clear();
          lcd.print("Door Closed");
          Blynk.virtualWrite(V1, "Door Status: Closed"); // Update label to Closed
          delay(2000);
          lcd.clear();
          lcd.print("System Ready");
        }
      }
      else
      {
        lcd.setCursor(currentLength, 1);
        lcd.print(key);
        enteredPassword[currentLength] = key;
        currentLength++;

        if (currentLength == passwordLength)
        {
          enteredPassword[currentLength] = '\0';
          checkPassword();
        }
      }
    }
  }
}

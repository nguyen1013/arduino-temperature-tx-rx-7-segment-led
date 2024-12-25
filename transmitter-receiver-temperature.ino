#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void seg(float number);

void setup() {
  // Initialize software serial at 1200 baud
  mySerial.begin(1200);
  // Initialize hardware serial
  Serial.begin(9600);

  // Set the direction of PORTD and PORTB pins for output
  DDRD = 0xF0;  // Set pins D7-D4 as outputs
  DDRB = 0x0F;  // Set pins B3-B0 as outputs
  
  // Set the pin used for software serial input
  pinMode(4, INPUT); // Assuming pin 4 is used for software serial input
}

void loop() {
  float temp = 0;
  if (mySerial.available() > 0) { // Check for data
    int a = mySerial.read();
    
    if (a == 'T') {  // Temperature data is coming next
      temp = mySerial.parseFloat(); // Parse the floating-point temperature value
      Serial.println(temp); // Print the temperature value to the Serial monitor
      seg(temp); // Display the temperature on the 7-segment display
    }    
  } 
}

void seg(float number) {
  int i = int(number);

  if (i < 10) { // One-digit value
    PORTD = 0;   // Clear PORTD
    PORTB = i;   // Set PORTB with the one-digit value
  }

  if (i >= 10) { // Two-digit value
    PORTD = (i % 10) << 4; // Shift to the higher 4 bits of PORTD
    PORTB = (i / 10);      // Set the tens digit on the lower 4 bits of PORTB
  }
}

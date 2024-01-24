#include <IRremote.h> //Library to control the IR remote

// Define IR remote control codes for different actions
int stop = 765;
int forward = 25245;
int backward = -22441;
int right_turn = -15811;
int left_turn = 8925;


int RECV_PIN = 11;        // Define the input pin on Arduino for the IR receiver
IRrecv irrecv(RECV_PIN);  // 
decode_results results;   //

void setup() {
  Serial.begin(9600);
  
  // Define pin modes
  pinMode(4, OUTPUT);   // Motor control pin
  pinMode(2, OUTPUT);   // Motor control pin
  pinMode(11, INPUT);   // IR receiver input pin

  // Start the IR receiver
  irrecv.enableIRIn();
}

void loop() {
  // Check if an IR signal is received
  if (irrecv.decode(&results)) {
    Serial.println(results.value);  // Print the received IR code in the serial monitor
    int x = (results.value);        // Store the received IR code in variable x
    Serial.println(x);              // Print the value of x in the serial monitor

    irrecv.resume(); // Receive the next value

    // Check the received IR code and take appropriate action
    if (forward == x) {
      digitalWrite(4, HIGH);        // Set motor control pins for forward movement
      analogWrite(5, 100);          // Set motor speed
      digitalWrite(2, HIGH);
      analogWrite(9, 65);
      Serial.println("forward");    // Shows when it's activated
    }
    if (backward == x) {
      digitalWrite(4, LOW);         // Set motor control pins for backward movement
      analogWrite(5, 100);          // Set motor speed
      digitalWrite(2, LOW);
      analogWrite(9, 65);
      Serial.println("backward");
    }
    if (right_turn == x) {
      digitalWrite(4, LOW);         // Set motor control pins for turning right
      analogWrite(5, 90);           // Set motor speed
      digitalWrite(2, HIGH);
      analogWrite(9, 80);
      Serial.println("right_turn"); // Shows when it's activated
    }
    if (left_turn == x) {
      digitalWrite(4, HIGH);        // Set motor control pins for turning left
      analogWrite(5, 90);           // Set motor speed
      digitalWrite(2, LOW);
      analogWrite(9, 80);
      Serial.println("left_turn");  // Shows when it's activated
    }

    if (stop == x) {
      analogWrite(5, 0);            // Stop the motors
      analogWrite(9, 0);
      Serial.println("stop");       // Shows when it's activated
    }


    
    delay(100); // Delay to avoid processing the same IR code multiple times
  }
}

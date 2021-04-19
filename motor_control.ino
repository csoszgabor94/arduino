String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

int enable = 11;
int dir = 12;
int vel = 13;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  Serial.println("motorControl");
  inputString.reserve(200);
  pinMode(enable, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(vel, OUTPUT);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    if(inputString[0] == 'r' || inputString[0] == 'l')
    {
      digitalWrite(enable, HIGH);
      if(inputString[0] == 'l') 
      {
        digitalWrite(dir, HIGH);
      }
      else 
      {
        digitalWrite(dir, LOW);
      }
      inputString.remove(0, 1);
      for(int i = 0; i < inputString.toInt(); i++)
      {
        digitalWrite(vel, HIGH);
        delay(10);
        digitalWrite(vel, LOW);
        delay(10);
      }
      digitalWrite(enable, LOW);
    }
    else Serial.println("Wrong command");
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

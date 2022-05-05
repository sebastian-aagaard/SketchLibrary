#define MAX_BUF (64)
char serialBuffer[MAX_BUF + 1]; // Serial buffer
int sofar = 0;  // how much is in the buffer

static int pul = 10;
static int dir = 9;
static int enb = 8;

//these two values
static int stepprmm = 1000; // decides distance
volatile int stepdelay = 1000; //speed


volatile int layerheight = 0.025;//
volatile int steps = 0;


void setup() {
  // put your setup code here, to run once:

  pinMode(pul, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(enb, OUTPUT);

  Serial.begin(115200);  // open coms
  delay(1000);

  digitalWrite(enb, HIGH);
  delay(1000);

  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:

  //delayMicroseconds(1000);
  readSerial();

  //  digitalWrite(dir, HIGH);
  //  delay(10);
  //  for (int i = 0; i <= 1000; i++) {
  //    digitalWrite(pul, HIGH);
  //    delayMicroseconds(stepdelay);
  //
  //    digitalWrite(pul, LOW);
  //    delayMicroseconds(stepdelay);
  //  }
  //  delay(20);
  //
  //  digitalWrite(dir, LOW);
  //
  //
  //  for (int i = 0; i <= 1000; i++) {
  //    digitalWrite(pul, HIGH);
  //    delayMicroseconds(stepdelay);
  //
  //    digitalWrite(pul, LOW);
  //    delayMicroseconds(stepdelay);
  //  }
}

float parseNumber(char code, float val) {
  char *ptr = serialBuffer; // start at the beginning of buffer
  while ((long)ptr > 1 && (*ptr) && (long)ptr < (long)serialBuffer + sofar) { // walk to the end
    if (*ptr == code) { // if you find code on your walk,
      return atof(ptr + 1); // convert the digits that follow into a float and return it
    }
    ptr = strchr(ptr, ' ') + 1; // take a step from here to the letter after the next space
  }
  return val;  // end reached, nothing found, return default val.
}

void processCommand() {
  /**
    Read the input buffer and find any recognized commands.  One G command per line.
  */

  int cmd = parseNumber('G', -1);
  switch (cmd) {
    case -1: ; break;
    case 1: {// Set mirror position in mm X and Y
        moveZaxis(parseNumber('Z', layerheight));
        break;
      }
    default: {
        Serial.println("Hmm - we don't seem to have that functionality yet :(");
        Serial.println("-- Input will be ignored --");
        break;
      }
  }
}

void readSerial() {
  while (Serial.available() > 0) { // if something is available
    char c = Serial.read(); // get it
    Serial.print(c);  // repeat it back so I know you got the message
    if (sofar < MAX_BUF - 1) serialBuffer[sofar++] = c; // store it
    if (c == '\n') {

      // entire message received
      serialBuffer[sofar] = 0; // end the buffer so string functions work right
      processCommand();
      sofar = 0; // clear input buffer

      Serial.print("ok");
    }
  }

}

void moveZaxis(float _layerheight) {

  steps = abs(_layerheight * stepprmm);
  Serial.println(steps);
  Serial.print("Moving: ");
  Serial.println(_layerheight);

  if (_layerheight > 0) {

    digitalWrite(dir, LOW);
    delayMicroseconds(400);

  } else if (_layerheight < 0) {

    digitalWrite(dir, HIGH);
    delayMicroseconds(400);

  }



  for (int i = 0; i <= steps; i++) {

    digitalWrite(pul, HIGH);
    delayMicroseconds(stepdelay);

    digitalWrite(pul, LOW);
    delayMicroseconds(stepdelay);

  }

}

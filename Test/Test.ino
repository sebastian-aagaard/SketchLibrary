void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("start");

  uint32_t *p;

  uint16_t that = 2000;

  Serial.println(that, BIN);
  Serial.println(that);
  uint32_t Ch1 = (((uint32_t)that << 1) | 0x20000ul) & 0x3fffeul;
  uint32_t Ch2 = (((uint32_t)that << 1) | 0x20000ul) & 0x3fffeul;

  Serial.println(Ch1, BIN);
  Serial.println("");

  const uint16_t Sync1[4] = { 0xd2c3, 0x9687, 0x5a4b, 0x1e0f  };
  const uint16_t Sync0[4] = { 0xf0e1, 0xb4a5, 0x7869, 0x3c2d  };

  //  Serial.println(Sync1[0], BIN);
  //  Serial.println(Sync1[1], BIN);
  //  Serial.println(Sync1[2], BIN);
  //  Serial.println(Sync1[3], BIN);
  //  Serial.println(" ");
  //  Serial.println(Sync0[0], BIN);
  //  Serial.println(Sync0[1], BIN);
  //  Serial.println(Sync0[2], BIN);
  //  Serial.println(Sync0[3], BIN);

  uint8_t parity1 = 0;
  uint8_t parity2 = 0;

  //checksCh1 and Ch2 for 1's
  for (int i = 0; i < 20; i++) {
    if (Ch1 & (1 << i)) parity1++;
    if (Ch2 & (1 << i)) parity2++;
  }
  
  Serial.println("");
  Serial.println(Ch1, BIN);

  if (parity1 & 1) Ch1 |= 1;
  if (parity2 & 1) Ch2 |= 1;


  Serial.println(Ch1, BIN);
  Serial.println("");

for (int i = 19; i >= 0; i--) {
    int j = 0;
    uint32_t d;
    //selecting the sync channen to store in d
    if (Ch1 & (1 << i)) j = 1;// 1
    if (Ch2 & (1 << i)) j |= 2; // 10
                                // thus j = 00 01 10 11
    d = Sync1[j]; //store in sync1 if 11 d = 0001111000001111
                                    //00 d = 1101001011000011
                                    // 01 =  1001011010000111
                                    // 10 =  0101101001001011

    i--;
    j = 0;

    if (Ch1 & (1 << i)) j = 1;
    if (Ch2 & (1 << i)) j |= 2; 
    if (i != 0) d |= (uint32_t)Sync1[j] << 16; else d |= (uint32_t)Sync0[j] << 16;
    //Serial.print("sync1_ second: ");
    //Serial.println(d, BIN);

    Serial.println("i= ");
    Serial.println(i);
    Serial.println(d,BIN);
    //*p++ = d;

  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

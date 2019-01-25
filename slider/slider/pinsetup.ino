void pinsetup() {
  pinMode(XLIMIT, INPUT_PULLUP);
  pinMode(YLIMIT, INPUT_PULLUP);
  pinMode(ZLIMIT, INPUT_PULLUP);

  pinMode(ENABLE,OUTPUT);
  digitalWrite(ENABLE,LOW);

}


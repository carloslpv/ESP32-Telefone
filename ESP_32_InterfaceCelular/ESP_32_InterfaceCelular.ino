void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  delay(3000);
  Serial.println("Teste ligacao");
  Serial.println("ATD01549991756759;\n");
  updateSerial();
  delay(20000);
  Serial.println("AT+CMGF=1\n");
  updateSerial();
  Serial.println("AT+CMGS=\"+5549991756759\"");
  updateSerial();
  Serial.println("Teste GPRS"); //text content
  updateSerial();
  Serial.write(26);
  updateSerial();
  delay(2000);
}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (Serial2.available())
  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}

void loop() {
  Serial.println("Teste comunicação");
  Serial.println("AT\n");
  updateSerial();
  delay(2000);
}

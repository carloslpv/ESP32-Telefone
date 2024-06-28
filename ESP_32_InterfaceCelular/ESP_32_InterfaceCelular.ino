#include <EEPROM.h>

#define EEPROM_SIZE 1000

typedef struct {
  int id;
  char numero[12];
  char operadora[3];
} Telefone;

typedef struct {
  int idTelefone;
  char mensagem[30];
} Mensagem;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  // Limpar EEPROM
  clearEEPROM();
  Serial.println("EEPROM limpa.");

  // Teste inicial para gravar e ler dados
  Telefone tel1 = {1, "1234567890", "15"};
  Telefone tel2 = {2, "0987654321", "41"};
  Mensagem msg = {1, "Hello, this is a test message."};

  writeTelefone(0, tel1);
  writeMensagem(sizeof(Telefone), msg);
  writeTelefone(sizeof(Telefone) + sizeof(Mensagem), tel2);

  Serial.println("Dados escritos na EEPROM.");

  Telefone readTel1, readTel2;
  Mensagem readMsg;

  readTelefone(0, readTel1);
  readMensagem(sizeof(Telefone), readMsg);
  readTelefone(sizeof(Telefone) + sizeof(Mensagem), readTel2);

  Serial.println("Leitura de dados da EEPROM:");
  printTelefone(readTel1);
  printMensagem(readMsg);
  printTelefone(readTel2);
}

void loop() {
  // Adicione aqui o código para alterar dados conforme necessário
}

void writeTelefone(int address, Telefone tel) {
  EEPROM.put(address, tel);
  EEPROM.commit();
}

void writeMensagem(int address, Mensagem msg) {
  EEPROM.put(address, msg);
  EEPROM.commit();
}

void readTelefone(int address, Telefone &tel) {
  EEPROM.get(address, tel);
}

void readMensagem(int address, Mensagem &msg) {
  EEPROM.get(address, msg);
}

void printTelefone(Telefone tel) {
  Serial.print("ID: ");
  Serial.println(tel.id);
  Serial.print("Número: ");
  Serial.println(tel.numero);
  Serial.print("Operadora: ");
  Serial.println(tel.operadora);
}

void printMensagem(Mensagem msg) {
  Serial.print("ID Telefone: ");
  Serial.println(msg.idTelefone);
  Serial.print("Mensagem: ");
  Serial.println(msg.mensagem);
}

void clearEEPROM() {
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}
#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512 // Tamanho da EEPROM da ESP32

// Definição das estruturas
typedef struct {
  char numero[12];
  char nome[50];
  char operadora[3];
} Telefone;

typedef struct {
  char numero[10];
  char mensagem[300];
} Mensagem;

// Funções de EEPROM
void EEPROM_write(int address, byte data) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.write(address, data);
  EEPROM.commit();
  EEPROM.end();
}

byte EEPROM_read(int address) {
  EEPROM.begin(EEPROM_SIZE);
  byte data = EEPROM.read(address);
  EEPROM.end();
  return data;
}

// Funções para Telefones
void cadastraTelefone(const char* numero, const char* nome, const char* operadora, int index) {
  Telefone telefone;
  
  strcpy(telefone.numero, numero);
  strcpy(telefone.nome, nome);
  strcpy(telefone.operadora, operadora);
  int addr = sizeof(Telefone) * index;
  
  EEPROM.put(addr,telefone);
  /*Serial.printf("CADASTRO REALIZADO\n");
  Serial.printf("Endereco: %d\n", addr);
  Serial.printf("Numero: %s\n", telefone.numero);
  Serial.printf("Nome: %s\n", telefone.nome);
  Serial.printf("Operadora: %s\n", telefone.operadora);*/
}

void listaTelefones() {
  int totalTelefones = EEPROM_SIZE / sizeof(Telefone);
  EEPROM
  Serial.println("Listagem de Telefones:");
  for (int i = 0; i < totalTelefones; i++) {
    Telefone telefone;
    int addr = sizeof(Telefone) * i;
    EEPROM.get(addr, telefone);
    
    if (telefone.numero[0] != '\0') {
      Serial.print("Número: ");
      Serial.println(telefone.numero);
      Serial.print("Nome: ");
      Serial.println(telefone.nome);
      Serial.print("Operadora: ");
      Serial.println(telefone.operadora);
      Serial.println("-------------------------");
    }
  }
}

void alteraTelefone(const char* numero, const char* nome, const char* operadora, int index) {
  Telefone telefone;
  strncpy(telefone.numero, numero, sizeof(telefone.numero));
  strncpy(telefone.nome, nome, sizeof(telefone.nome));
  strncpy(telefone.operadora, operadora, sizeof(telefone.operadora));

  int addr = sizeof(Telefone) * index;
  EEPROM.put(addr, telefone);
}

void excluiTelefone(int index) {
  Telefone telefone;
  telefone.numero[0] = '\0';
  
  int addr = sizeof(Telefone) * index;
  EEPROM.put(addr, telefone);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Inicialização da EEPROM
  EEPROM.begin(EEPROM_SIZE);

  // Exemplo de uso inicial:
  //cadastraTelefone("988655252", "Jonathan", "49", 0);
  //cadastraTelefone("987654321", "Maria", "51", 1);

  // Lista os telefones cadastrados
  Serial.println("Telefones cadastrados:");
  listaTelefones();
  
  // Altera um telefone
  alteraTelefone("4911111111", "João", "49", 0);
  Serial.println("Telefones após alteração:");
  listaTelefones();
  /*
  // Exclui um telefone
  excluiTelefone(1);
  Serial.println("Telefones após exclusão:");
  listaTelefones();*/

  // Encerramento da EEPROM
  EEPROM.end();
}

void loop() {
  // Exemplo de loop vazio
  delay(1000);
}

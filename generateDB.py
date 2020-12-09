import sys
import random, string

def record_generator():
    key_size = random.randint(1, 4094)
    value_size = random.randint(1, (4094 - key_size))
    key = ''.join(random.choices(string.ascii_letters + string.digits, k=key_size))
    value = ''.join(random.choices(string.ascii_letters + string.digits, k=value_size))
    return {"key": key, "value": value}

class record:
    # Valor constante da vírgula convertida para binário
    id_sep = bytearray(",", "ascii")
    def __init__(self, identifier, value, isActive):
        self.identifier = identifier
        self.value = value
        self.isActive = isActive
    def toBytes(self):
        # Tamanho das strings + a vírgula
        iSize = len(self.identifier)+len(self.value)+1
        # Conversão do tamanho pra binário
        sz = iSize.to_bytes(4, "little")
        # Bit de atividade do registro
        active_bt = bytes([1]) if self.isActive else bytes([0])
        # Conversão do identificador pra binário
        id_bt = bytearray(self.identifier, "ascii")
        # Conversão do valor para binário
        id_val = bytearray(self.value, "ascii")
        # Retorna a concatenação desses valores!
        return sz + active_bt + id_bt + record.id_sep + id_val

if len(sys.argv) < 2:
    print("Falta a quantidade de registros")

if len(sys.argv) < 3:
    print("Falta o caminho de saida")

n_records = int(sys.argv[1])

records = []

# records = [record("ed2", "facil", True), record("paa", "deboa", True), record("tc", "suave", False), record("cd", "jafoi", True)]
# records = [record("ed2", "nota100", True)]

for _ in range(n_records):
    generated = record_generator()
    records.append(record(generated['key'], generated['value'], random.choice([True, False])))

# Escreve em out.dat
with open(sys.argv[2], "wb") as outputFile:
    for record in records:
       outputFile.write(record.toBytes())


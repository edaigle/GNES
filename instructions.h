#include <stdint.h>

typedef enum AddressingMode {
    Immediate,
    Absolute,
    XIndexedAbsolute,
    YIndexedAbsolute,
    ZeroPage,
    XIndexedZeroPage,
    XIndexedZeroPageIndirect,
    ZeroPageIndirectYIndexed
} AddressingMode;

typedef struct Machine {
    uint8_t accumulator;
    uint8_t registerX;
    uint8_t registerY;
    uint8_t status;
    uint16_t programCounter;
    uint8_t memory[0xFFFF];
} Machine;

void dex(Machine *m);
void dey(Machine *m);
void lda(Machine *m, unsigned char *instruction, AddressingMode mode);
void tax(Machine *m);
void tay(Machine *m);

void updateZeroFlag(Machine *m);
void updateNegativeFlag(Machine *m);

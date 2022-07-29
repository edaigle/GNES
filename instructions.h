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

typedef struct CPU_6502 {
    uint8_t accumulator;
    uint8_t registerX;
    uint8_t registerY;
    uint8_t status;
    uint16_t programCounter;
} CPU_6502;

static uint8_t memory[0xFFFF]; //TOFIX: why static?

void dex(CPU_6502 *cpu);
void dey(CPU_6502 *cpu);
void lda(CPU_6502 *cpu, unsigned char *instruction, AddressingMode mode);

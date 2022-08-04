#include <stdint.h>

#define STACK_BOTTOM 0x0100

typedef enum AddressingMode {
    Accumulator,
    Immediate,
    Absolute,
    XIndexedAbsolute,
    YIndexedAbsolute,
    ZeroPage,
    XIndexedZeroPage,
    YIndexedZeroPage,
    XIndexedZeroPageIndirect,
    ZeroPageIndirectYIndexed
} AddressingMode;

typedef enum ShiftDirection {
    Left,
    Right
} ShiftDirection;

typedef struct Machine {
    uint8_t accumulator;
    uint8_t registerX;
    uint8_t registerY;
    uint8_t status;
    uint16_t programCounter;

    uint8_t memory[0xFFFF];

    uint8_t stackPointer;
} Machine;

void dex(Machine *m);
void dey(Machine *m);

void lda(Machine *m, unsigned char *instruction, AddressingMode mode);
void ldx(Machine *m, unsigned char *instruction, AddressingMode mode);
void ldy(Machine *m, unsigned char *instruction, AddressingMode mode);

void store(Machine *m, unsigned char *instruction, unsigned char *reg, AddressingMode mode);
void transfer(Machine *m, unsigned char *from, unsigned char *to, int updateFlags);
void push(Machine *m, unsigned char *src);
void pull(Machine *m, unsigned char *dest);
void shift(Machine *m, unsigned char *instruction, AddressingMode mode, ShiftDirection dir);
void rotate(Machine *m, unsigned char *instruction, AddressingMode mode, ShiftDirection dir);

void and(Machine *m, unsigned char *instruction, AddressingMode mode);
void bit(Machine *m, unsigned char *instruction, AddressingMode mode);
void eor(Machine *m, unsigned char *instruction, AddressingMode mode);
void ora(Machine *m, unsigned char *instruction, AddressingMode mode);

void clc(Machine *m);
void cld(Machine *m);
void cli(Machine *m);
void clv(Machine *m);
void sec(Machine *m);
void sed(Machine *m);
void sei(Machine *m);

unsigned char fetchData(Machine *m, unsigned char *instruction, AddressingMode mode);
unsigned char storeData(Machine *m, unsigned char *instruction, unsigned char *reg, AddressingMode mode);

void updateZeroFlag(Machine *m, uint8_t result);
void updateNegativeFlag(Machine *m, uint8_t result);

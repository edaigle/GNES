#include "instructions.h"

void dex(Machine *m) {
    m->registerX--;
    updateZeroFlag(m->registerX);
    updateNegativeFlag(m->registerX);
}

void dey(Machine *m) {
    m->registerY--;
    updateZeroFlag(m->registerY);
    updateNegativeFlag(m->registerY);
}

void lda(Machine *m, unsigned char *instruction, AddressingMode mode) {
    switch (mode) {
        case Immediate: m->accumulator = instruction[1]; break;
        case Absolute: m->accumulator = m->memory[instruction[2]<<8 | instruction[1]];
        case XIndexedAbsolute: break;
        case YIndexedAbsolute: break;
        case ZeroPage: break;
        case XIndexedZeroPage: break;
        case XIndexedZeroPageIndirect: break;
        case ZeroPageIndirectYIndexed: break;
    }
    updateZeroFlag(m->accumulator);
    updateNegativeFlag(m->accumulator);
}

void tax(Machine *m) {
    m->registerX = m->accumulator;
    updateZeroFlag(m->registerX);
    updateNegativeFlag(m->registerX);
}

void tay(Machine *m) {
    m->registerY = m->accumulator;
    updateZeroFlag(m->registerY);
    updateNegativeFlag(m->registerY);
}

// TODO: move these to utils?
void updateZeroFlag(Machine *m, uint8_t result) {
    if (result == 0) {
        m->status = m->status | 0b00000010;
    } else {
        m->status = m->status & 0b11111101;
    }
}

void updateNegativeFlag(Machine *m, uint8_t result) {
    if ((result & 0b10000000) != 0b00000000) {
        m->status = m->status | 0b10000000;
    } else {
        m->status = m->status & 0b01111111;
    }
}
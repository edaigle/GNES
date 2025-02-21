#include <stdio.h>
#include <stdlib.h>

#include "instructions.h"
Machine m = {0, 0, 0};

int execute(unsigned char *rom, int programCounter) {
    unsigned char *opcode = &rom[programCounter];
    int oplength = 1;

    switch (*opcode) {
        case 0x00: printf("BRK"); break;
        case 0x01: printf("(ORA $%02x, X)", opcode[1]); oplength = 2; break; 
        case 0x05: printf("ORA $%02x", opcode[1]); oplength = 2; break;
        case 0x06: printf("ASL $%02x", opcode[1]); oplength = 2; break;
        case 0x08: push(&m, &m.status); break;
        case 0x09: printf("ORA #$%02x", opcode[1]); oplength = 2; break;
        case 0x0A: printf("ASL A"); break;
        case 0x0D: printf("ORA $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x0E: printf("ASL $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x10: printf("BPL $%02x", opcode[1]); oplength = 2; break;
        case 0x11: printf("ORA $%02x, X", opcode[1]); oplength = 2; break;
        case 0x15: printf("ORA $%02x, X", opcode[1]); oplength = 2; break;
        case 0x16: printf("ASL $%02x, X", opcode[1]); oplength = 2; break;
        case 0x18: clc(&m); break;
        case 0x19: printf("ORA $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x1D: printf("ORA $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x1E: printf("ASL $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x20: printf("JSR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x21: printf("(AND $%02x, X)", opcode[1]); oplength = 2; break;
        case 0x24: printf("BIT $%02x", opcode[1]); oplength = 2; break;
        case 0x25: printf("AND $%02x", opcode[1]); oplength = 2; break;
        case 0x26: printf("ROL $%02x", opcode[1]); oplength = 2; break;
        case 0x28: printf("PLP"); break;
        case 0x29: printf("AND #$%02x", opcode[1]); oplength = 2; break;
        case 0x2A: printf("ROL A"); break;
        case 0x2C: printf("BIT $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x2D: printf("AND $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x2E: printf("ROL $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x30: printf("BMI $%02x", opcode[1]); oplength = 2; break;
        case 0x31: printf("AND ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0x35: printf("AND $%02x, X", opcode[1]); oplength = 2; break;
        case 0x36: printf("ROL $%02x, X", opcode[1]); oplength = 2; break;
        case 0x38: sec(&m); break;
        case 0x39: printf("AND $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x3D: printf("AND $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x3E: printf("ROL $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x40: printf("RTI"); break;
        case 0x41: printf("EOR ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0x45: printf("EOR $%02x", opcode[1]); oplength = 2; break;
        case 0x46: printf("LSR $%02x", opcode[1]); oplength = 2; break;
        case 0x48: push(&m, &m.accumulator); break;
        case 0x49: printf("EOR #$%02x", opcode[1]); oplength = 2; break;
        case 0x4A: printf("LSR A"); break;
        case 0x4C: printf("JMP $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x4D: printf("EOR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x4E: printf("LSR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x50: printf("BVC $%02x", opcode[1]); oplength = 2; break;
        case 0x51: printf("EOR ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0x55: printf("EOR $%02x, X", opcode[1]); oplength = 2; break;
        case 0x56: printf("LSR $%02x, X", opcode[1]); oplength = 2; break;
        case 0x58: cli(&m); break;
        case 0x59: printf("EOR $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x5D: printf("EOR $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x5E: printf("LSR $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x60: printf("RTS"); break;
        case 0x61: printf("ADC ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0x65: printf("ADD $%02x", opcode[1]); oplength = 2; break;
        case 0x66: printf("ROR $%02x", opcode[1]); oplength = 2; break;
        case 0x68: printf("PLA"); break;
        case 0x69: printf("ADC #$%02x", opcode[1]); oplength = 2; break;
        case 0x6A: printf("ROR A"); break;
        case 0x6C: printf("JMP ($%02x%02x)", opcode[2], opcode[1]); oplength = 3; break;
        case 0x6D: printf("ADC $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x6E: printf("ROR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x70: printf("BVS $%02x", opcode[1]); oplength = 2; break;
        case 0x71: printf("ADC ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0x75: printf("ADC $%02x, X", opcode[1]); oplength = 2; break;
        case 0x76: printf("ROR $%02x, X", opcode[1]); oplength = 2; break;
        case 0x78: sei(&m); break;
        case 0x79: printf("ADC $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x7D: printf("ADC $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x7E: printf("ROR $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x81: store(&m, opcode, m.accumulator, XIndexedZeroPageIndirect); oplength = 2; break;
        case 0x84: store(&m, opcode, m.registerY, ZeroPage); oplength = 2; break;
        case 0x85: store(&m, opcode, m.accumulator, ZeroPage); oplength = 2; break;
        case 0x86: store(&m, opcode, m.registerX, ZeroPage); oplength = 2; break;
        case 0x88: printf("DEY"); dey(&m, opcode); break;
        case 0x8A: transfer(&m, &m.registerX, &m.accumulator); break;
        case 0x8C: store(&m, opcode, m.registerY, Absolute); oplength = 3; break;
        case 0x8D: store(&m, opcode, m.accumulator, Absolute); oplength = 3; break;
        case 0x8E: store(&m, opcode, m.registerX, Absolute); oplength = 3; break;
        case 0x90: bcc(&m, opcode); oplength = 2; break;
        case 0x91: store(&m, opcode, m.accumulator, ZeroPageIndirectYIndexed); oplength = 2; break;
        case 0x94: store(&m, opcode, m.registerY, XIndexedZeroPage); oplength = 2; break;
        case 0x95: store(&m, opcode, m.accumulator, XIndexedZeroPage); oplength = 2; break;
        case 0x96: store(&m, opcode, m.registerX, YIndexedZeroPage); oplength = 2; break;
        case 0x98: transfer(&m, &m.registerY, &m.accumulator, 1); break;
        case 0x99: store(&m, opcode, m.accumulator, YIndexedAbsolute); oplength = 3; break;
        case 0x9A: transfer(&m, &m.registerX, &m.stackPointer, 0); break;
        case 0x9D: store(&m, opcode, m.accumulator, XIndexedAbsolute); oplength = 3; break;
        case 0xA0: ldy(&m, opcode, Immediate); oplength = 2; break;
        case 0xA1: printf("LDA ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0xA2: ldx(&m, opcode, Immediate); oplength = 2; break;
        case 0xA4: ldy(&m, opcode, ZeroPage); oplength = 2; break;
        case 0xA5: printf("LDA $%02x", opcode[1]); oplength = 2; break;
        case 0xA6: ldx(&m, opcode, ZeroPage); oplength = 2; break;
        case 0xA8: printf("TAY"); transfer(&m, &m.accumulator, &m.registerY, 1); break;
        case 0xA9: lda(&m, opcode, Immediate);/*printf("LDA #$%02x", opcode[1]);*/ oplength = 2; break;
        case 0xAA: printf("TAX"); transfer(&m, &m.accumulator, &m.registerX, 1); break;
        case 0xAC: ldy(&m, opcode, Absolute); oplength = 3; break;
        case 0xAD: printf("LTA $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xAE: ldx(&m, opcode, Absolute); oplength = 3; break;
        case 0xB0: printf("BCS $%02x", opcode[1]); oplength = 2; break;
        case 0xB1: printf("LDA ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0xB4: ldy(&m, opcode, XIndexedZeroPage); oplength = 2; break;
        case 0xB5: printf("LDA $%02x, X", opcode[1]); oplength = 2; break;
        case 0xB6: ldx(&m, opcode, YIndexedZeroPage); oplength = 2; break;
        case 0xB8: clv(&m); break;
        case 0xB9: printf("LDA $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0xBA: transfer(&m, &m.stackPointer, &m.registerX, 1); break;
        case 0xBC: ldy(&m, opcode, XIndexedAbsolute); oplength = 3; break;
        case 0xBD: printf("LTA $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xBE: ldx(&m, opcode, YIndexedAbsolute); oplength = 3; break;
        case 0xC0: printf("CPY #$%02x", opcode[1]); oplength = 2; break;
        case 0xC1: printf("CMP ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0xC4: printf("CPY $%02x", opcode[1]); oplength = 2; break;
        case 0xC5: printf("CMP $%02x", opcode[1]); oplength = 2; break;
        case 0xC6: printf("DEC $%02x", opcode[1]); oplength = 2; break;
        case 0xC8: printf("INY"); break;
        case 0xC9: printf("CMP #$%02x", opcode[1]); oplength = 2; break;
        case 0xCA: printf("DEX"); dex(&m, opcode); break;
        case 0xCC: printf("CPY $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xCD: printf("CMP $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xCE: printf("DEC $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xD0: printf("BNE $%02x", opcode[1]); oplength = 2; break;
        case 0xD1: printf("LDX ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0xD5: printf("CMP $%02x, X", opcode[1]); oplength = 2; break;
        case 0xD6: printf("DEC $%02x, X", opcode[1]); oplength = 2; break;
        case 0xD8: cld(&m); break;
        case 0xD9: printf("CMP $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0xDD: printf("CMP $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xDE: printf("DEC $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xE0: printf("CPX #$%02x", opcode[1]); oplength = 2; break;
        case 0xE1: printf("SBC ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0xE4: printf("CPX $%02x", opcode[1]); oplength = 2; break;
        case 0xE5: printf("SBC $%02x", opcode[1]); oplength = 2; break;
        case 0xE6: printf("INC $%02x", opcode[1]); oplength = 2; break;
        case 0xE8: printf("INX"); break;
        case 0xE9: printf("SBC #$%02x", opcode[1]); oplength = 2; break;
        case 0xEA: printf("NOP"); break;
        case 0xEC: printf("CPX $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xED: printf("SBC $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xEE: printf("INC $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xF0: printf("BEQ $%02x", opcode[1]); oplength = 2; break;// case ...: TODO
        case 0xF1: printf("SBC ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0xF5: printf("SBC $%02x, X", opcode[1]); oplength = 2; break;
        case 0xF6: printf("INC $%02x, X", opcode[1]); oplength = 2; break;
        case 0xF8: sed(&m); break;
        case 0xF9: printf("SBC $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0xFD: printf("SBC $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xFE: printf("INC $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
    }
    
    return oplength;
}

int main(void) {
    return 0;
}
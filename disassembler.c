int Disassemble6502Op(unsigned char *codebuffer, int pc)
{
    unsigned char *opcode = &codebuffer[pc];
    int oplength = 1;

    printf("%04x: ", )
    switch (*opcode) {
        case 0x00: printf("BRK"); break;
        case 0x01: printf("(ORA $%02x, X)", opcode[1]); oplength = 2; break;
        case 0x05: printf("ORA $%02x", opcode[1]); oplength = 2; break;
        case 0x06: printf("ASL $%02x", opcode[1]); oplength = 2; break;
        case 0x08: printf("PHP"); break;
        case 0x09: printf("ORA #$%02x", opcode[1]); oplength = 2; break;
        case 0x0A: printf("ASL A"); break;
        case 0x0D: printf("ORA $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x0E: printf("ASL $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x10: printf("BPL $%02x", opcode[1]); oplength = 2; break;
        case 0x11: printf("ORA $%02x, X", opcode[1]); oplength = 2; break;
        case 0x15: printf("ORA $%02x, X", opcode[1]); oplength = 2; break;
        case 0x16: printf("ASL $%02x, X", opcode[1]); oplength = 2; break;
        case 0x18: printf("CLC"); break;
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
        // case ...: TODO
    }
}

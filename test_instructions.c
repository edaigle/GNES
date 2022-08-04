#include <check.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "instructions.h"

START_TEST(test_lda_immediate_data)
{
    Machine m = {0, 0, 0};
    unsigned char instruction[3] = {0x9a, 0x05, 0x00};

    lda(&m, &instruction[0], Immediate);

    ck_assert_int_eq(m.accumulator, 0x05);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0);

    // TODO: add negative case
}
END_TEST

START_TEST(test_lda_zeroflag_data)
{
    Machine m = {0, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction[2] = {0x9a, 0x05};

    lda(&m, &instruction[0], Immediate);

    ck_assert_int_eq(m.accumulator, 0x05);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0);

    // TODO: add negative case
}
END_TEST

START_TEST(test_lda_zero_flag)
{
    Machine m = {0, 0, 0};
    unsigned char instruction[3] = {0x9a, 0x00, 0x00};

    lda(&m, &instruction[0], Immediate);

    ck_assert_int_eq(m.accumulator, 0x00);
    ck_assert_int_eq(m.status & 0b00000010, 0b10);
}
END_TEST

START_TEST(test_ldx)
{
    Machine m1 = {0, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction1[2] = {0xA2, 0x05};
    ldx(&m1, &instruction1[0], Immediate);
    ck_assert_int_eq(m1.registerX, 0x05);

    Machine m2 = {0, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}, 0xFF};
    unsigned char instruction2[2] = {0xAE, 0x02};
    ldx(&m2, &instruction2[0], Absolute);
    ck_assert_int_eq(m2.registerX, 0xDB);

    Machine m3 = {0, 0, 0x2, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction3[2] = {0xBE, 0x02};
    ldx(&m3, &instruction3[0], YIndexedAbsolute);
    ck_assert_int_eq(m3.registerX, 0xF0);

    Machine m4 = {0, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction4[2] = {0xA6, 0x01};
    ldx(&m4, &instruction4[0], ZeroPage);
    ck_assert_int_eq(m4.registerX, 0xEA);

    Machine m5 = {0, 0, 0x2, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction5[2] = {0xB6, 0x02};
    ldx(&m5, &instruction5[0], YIndexedZeroPage);
    ck_assert_int_eq(m5.registerX, 0xF0);

}
END_TEST

START_TEST(test_ldy)
{
    Machine m1 = {0, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction1[2] = {0xA2, 0x05};
    ldy(&m1, &instruction1[0], Immediate);
    ck_assert_int_eq(m1.registerY, 0x05);

    Machine m2 = {0, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}, 0xFF};
    unsigned char instruction2[2] = {0xAE, 0x02};
    ldy(&m2, &instruction2[0], Absolute);
    ck_assert_int_eq(m2.registerY, 0xDB);

    Machine m3 = {0, 0x2, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction3[2] = {0xBE, 0x02};
    ldy(&m3, &instruction3[0], XIndexedAbsolute);
    ck_assert_int_eq(m3.registerY, 0xF0);

    Machine m4 = {0, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction4[2] = {0xA6, 0x01};
    ldy(&m4, &instruction4[0], ZeroPage);
    ck_assert_int_eq(m4.registerY, 0xEA);

    Machine m5 = {0, 0x2, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction5[2] = {0xB6, 0x02};
    ldy(&m5, &instruction5[0], XIndexedZeroPage);
    ck_assert_int_eq(m5.registerY, 0xF0);

}
END_TEST

START_TEST(test_sta)
{
    Machine m1 = {0xFA, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction1[2] = {0x8D, 0x03};
    store(&m1, &instruction1[0], &m1.accumulator, Immediate);
    ck_assert_int_eq(m1.memory[0x03], 0xFA);

    Machine m2 = {0xFA, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction2[3] = {0x8D, 0xAA, 0x60};
    store(&m2, &instruction2[0], &m2.accumulator, Absolute);
    ck_assert_int_eq(m2.memory[0x60AA], 0xFA);

    Machine m3 = {0xFA, 0x2, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction3[3] = {0x9D, 0xAA, 0x60};
    store(&m3, &instruction3[0], &m3.accumulator, XIndexedAbsolute);
    ck_assert_int_eq(m3.memory[0x60AC], 0xFA);

    Machine m4 = {0xFA, 0, 0x2, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction4[3] = {0x99, 0xAA, 0x60};
    store(&m4, &instruction4[0], &m4.accumulator, YIndexedAbsolute);
    ck_assert_int_eq(m4.memory[0x60AC], 0xFA);

    // TODO: last two modes

}
END_TEST

START_TEST(test_stx)
{
    Machine m1 = {0, 0xFA, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction1[2] = {0x8D, 0x03};
    store(&m1, &instruction1[0], &m1.registerX, Immediate);
    ck_assert_int_eq(m1.memory[0x03], 0xFA);

    Machine m2 = {0, 0xFA, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction2[3] = {0x8D, 0xAA, 0x60};
    store(&m2, &instruction2[0], &m2.registerX, Absolute);
    ck_assert_int_eq(m2.memory[0x60AA], 0xFA);

    Machine m3 = {0x0, 0xFA, 0x2, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction3[3] = {0x9D, 0xAA, 0x60};
    store(&m3, &instruction3[0], &m3.registerX, YIndexedAbsolute);
    ck_assert_int_eq(m3.memory[0x60AC], 0xFA);

    // TODO: last two modes

}
END_TEST

START_TEST(test_sty)
{
    Machine m1 = {0, 0, 0xFA, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction1[2] = {0x8D, 0x03};
    store(&m1, &instruction1[0], &m1.registerY, Immediate);
    ck_assert_int_eq(m1.memory[0x03], 0xFA);

    Machine m2 = {0, 0, 0xFA, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction2[3] = {0x8D, 0xAA, 0x60};
    store(&m2, &instruction2[0], &m2.registerY, Absolute);
    ck_assert_int_eq(m2.memory[0x60AA], 0xFA);

    Machine m3 = {0x0, 0x2, 0xFA, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}};
    unsigned char instruction3[3] = {0x9D, 0xAA, 0x60};
    store(&m3, &instruction3[0], &m3.registerY, XIndexedAbsolute);
    ck_assert_int_eq(m3.memory[0x60AC], 0xFA);

    // TODO: last two modes

}
END_TEST

START_TEST(test_dex_pos)
{
    Machine m = {0, 2, 0, 0, 0};

    dex(&m);

    ck_assert_int_eq(m.registerX, 0x1);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0);

    // TODO: add negative case
}
END_TEST

START_TEST(test_dex_pos_zero_flag)
{
    Machine m = {0, 1, 0, 0, 0};

    dex(&m);

    ck_assert_int_eq(m.registerX, 0);
    ck_assert((m.status & 0b00000010) == 0b10);
    ck_assert((m.status & 0b10000000) == 0);
}
END_TEST

START_TEST(test_dey_pos)
{
    Machine m = {0, 0, 2, 0, 0};

    dey(&m);

    ck_assert_int_eq(m.registerY, 0x1);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0);

    // TODO: add negative case
}
END_TEST

START_TEST(test_dey_pos_zero_flag)
{
    Machine m = {0, 1, 0, 0, 0};

    dex(&m);

    ck_assert_int_eq(m.registerY, 0);
    ck_assert((m.status & 0b00000010) == 0b10);
    ck_assert((m.status & 0b10000000) == 0);
}
END_TEST

START_TEST(test_tax_pos)
{
    Machine m = {2, 0, 0, 0, 0, 0};

    transfer(&m, &m.accumulator, &m.registerX, 1);

    ck_assert_int_eq(m.registerX, 0x2);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0);

}
END_TEST

START_TEST(test_tax_neg)
{
    Machine m = {0xff, 0, 0, 0, 0, 0};

    transfer(&m, &m.accumulator, &m.registerX, 1);

    ck_assert_int_eq(m.registerX, 0xff);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0b10000000);

}
END_TEST

START_TEST(test_tax_zero_flag)
{
    Machine m = {0, 1, 0, 0, 0, 0};

    transfer(&m, &m.accumulator, &m.registerX, 1);

    ck_assert_int_eq(m.registerX, 0);
    ck_assert((m.status & 0b00000010) == 0b10);
    ck_assert((m.status & 0b10000000) == 0);
}
END_TEST

START_TEST(test_tay_pos)
{
    Machine m = {2, 0, 0, 0, 0, 0};

    transfer(&m, &m.accumulator, &m.registerY, 1);

    ck_assert_int_eq(m.registerY, 0x2);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0);

}
END_TEST

START_TEST(test_tay_neg)
{
    Machine m = {0xff, 0, 0, 0, 0, 0};

    transfer(&m, &m.accumulator, &m.registerY, 1);

    ck_assert_int_eq(m.registerY, 0xff);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0b10000000);

}
END_TEST

START_TEST(test_tay_zero_flag)
{
    Machine m = {0, 0, 2, 0, 0, 0};

    transfer(&m, &m.accumulator, &m.registerY, 1);

    ck_assert_int_eq(m.registerY, 0);
    ck_assert((m.status & 0b00000010) == 0b10);
    ck_assert((m.status & 0b10000000) == 0);
}
END_TEST

START_TEST(test_push)
{
    Machine m1 = {0xDE, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}, 0xFF};
    push(&m1, &m1.accumulator);
    ck_assert_int_eq(m1.stackPointer, 0xFE);
    ck_assert_int_eq(m1.memory[0x0100 | (m1.stackPointer+1)], 0xDE);

    Machine m2 = {0xDE, 0, 0, 6, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}, 0x01};
    push(&m2, &m2.status);
    ck_assert_int_eq(m2.stackPointer, 0x00);
    ck_assert_int_eq(m2.memory[0x0100 | (m2.stackPointer+1)], 0x6);
}

START_TEST(test_pull)
{
    Machine m1 = {0xDE, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}, 0xFF};
    push(&m1, &m1.accumulator);
    ck_assert_int_eq(m1.stackPointer, 0xFE);
    ck_assert_int_eq(m1.memory[0x0100 | (m1.stackPointer+1)], 0xDE);
    m1.accumulator = 0xFA;
    pull(&m1, &m1.accumulator);
    ck_assert_int_eq(m1.stackPointer, 0xFF);
    ck_assert_int_eq(m1.accumulator, 0xDE);

    Machine m2 = {0xDE, 0, 0, 6, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}, 0x01};
    push(&m2, &m2.status);
    ck_assert_int_eq(m2.stackPointer, 0x00);
    ck_assert_int_eq(m2.memory[0x0100 | (m2.stackPointer+1)], 0x6);
    m2.status = 0x8;
    pull(&m2, &m2.status);
    ck_assert_int_eq(m2.stackPointer, 0x01);
    ck_assert_int_eq(m2.status, 0x6);
}

START_TEST(test_asl)
{
    Machine m1 = {0x2, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}, 0xFF};
    unsigned char instruction1[3] = {0x0a, 0x05, 0x00};
    shift(&m1, &instruction1[0], Accumulator, Left);
    ck_assert_int_eq(m1.accumulator, 0x04);

    Machine m2 = {0x2, 0, 0, 0, 0, {0xDE, 0b0100, 0xDB, 0xEE, 0xF0}, 0xFF};
    unsigned char instruction2[3] = {0x0a, 0x01, 0x00};
    shift(&m2, &instruction2[0], Absolute, Left);
    ck_assert_int_eq(m2.memory[0x0001], 0b1000);

    Machine m3 = {0x2, 0x3, 0, 0, 0, {0xDE, 0x04, 0xDB, 0xEE, 0x08}, 0xFF};
    unsigned char instruction3[3] = {0x0a, 0x01, 0x00};
    shift(&m3, &instruction3[0], XIndexedAbsolute, Left);
    ck_assert_int_eq(m3.memory[0x0004], 0x10);

    Machine m4 = {0x2, 0x3, 0, 0, 0, {0xDE, 0xDE, 0x04, 0xEE, 0x08}, 0xFF};
    unsigned char instruction4[3] = {0x0a, 0x02, 0x00};
    shift(&m4, &instruction4[0], ZeroPage, Left);
    ck_assert_int_eq(m4.memory[0x0002], 0x08);

    Machine m5 = {0x2, 0x2, 0, 0, 0, {0xDE, 0xDE, 0x04, 0xEE, 0x08}, 0xFF};
    unsigned char instruction5[3] = {0x0a, 0x02, 0x00};
    shift(&m5, &instruction5[0], XIndexedZeroPage, Left);
    ck_assert_int_eq(m5.memory[0x0004], 0x10);
}

START_TEST(test_lsr)
{
    Machine m1 = {0x4, 0, 0, 0, 0, {0xDE, 0xEA, 0xDB, 0xEE, 0xF0}, 0xFF};
    unsigned char instruction1[3] = {0x0a, 0x05, 0x00};
    shift(&m1, &instruction1[0], Accumulator, Right);
    ck_assert_int_eq(m1.accumulator, 0x02);
    ck_assert_int_eq(m1.status & 0b10000011, 0);

    Machine m2 = {0x2, 0, 0, 0, 0, {0xDE, 0x08, 0xDB, 0xEE, 0xF0}, 0xFF};
    unsigned char instruction2[3] = {0x0a, 0x01, 0x00};
    shift(&m2, &instruction2[0], Absolute, Right);
    ck_assert_int_eq(m2.memory[0x0001], 0x04);
    ck_assert_int_eq(m2.status & 0b10000011, 0);

    Machine m3 = {0x2, 0x3, 0, 0, 0, {0xDE, 0x04, 0xDB, 0xEE, 0x09}, 0xFF};
    unsigned char instruction3[3] = {0x0a, 0x01, 0x00};
    shift(&m3, &instruction3[0], XIndexedAbsolute, Right);
    ck_assert_int_eq(m3.memory[0x0004], 0x04);
    ck_assert_int_eq(m3.status & 0b10000011, 1);

    Machine m4 = {0x2, 0x3, 0, 0, 0, {0xDE, 0xDE, 0x01, 0xEE, 0x08}, 0xFF};
    unsigned char instruction4[3] = {0x0a, 0x02, 0x00};
    shift(&m4, &instruction4[0], ZeroPage, Right);
    ck_assert_int_eq(m4.memory[0x0002], 0);
    ck_assert_int_eq(m4.status & 0b10000010, 2);

    Machine m5 = {0x2, 0x2, 0, 0, 0, {0xDE, 0xDE, 0x04, 0xEE, 0x08}, 0xFF};
    unsigned char instruction5[3] = {0x0a, 0x02, 0x00};
    shift(&m5, &instruction5[0], XIndexedZeroPage, Right);
    ck_assert_int_eq(m5.memory[0x0004], 0x04);
    ck_assert_int_eq(m1.status & 0b10000011, 0);
}

// TODO: some missing tests. AND, BIT, EOR, ORA

Suite *instructions(void)
{
    Suite *s;
    TCase *tc_load, *tc_store, *tc_dec, *tc_tax, *tc_push_pull, *tc_shift;

    s = suite_create("Instructions");
    
    tc_load = tcase_create("Loading");
    tcase_add_test(tc_load, test_lda_immediate_data);
    tcase_add_test(tc_load, test_lda_zero_flag);
    tcase_add_test(tc_load, test_ldx);
    tcase_add_test(tc_load, test_ldy);
    suite_add_tcase(s, tc_load);

    tc_store = tcase_create("Storing");
    tcase_add_test(tc_store, test_sta);
    tcase_add_test(tc_store, test_stx);
    tcase_add_test(tc_store, test_sty);
    suite_add_tcase(s, tc_store);

    tc_dec = tcase_create("DEX+DEY");
    tcase_add_test(tc_dec, test_dex_pos);
    tcase_add_test(tc_dec, test_dex_pos_zero_flag);
    tcase_add_test(tc_dec, test_dey_pos);
    tcase_add_test(tc_dec, test_dey_pos_zero_flag);
    
    suite_add_tcase(s, tc_dec);

    tc_tax = tcase_create("TAX+TAY");
    tcase_add_test(tc_tax, test_tax_pos);
    tcase_add_test(tc_tax, test_tax_zero_flag);
    tcase_add_test(tc_tax, test_tax_neg);
    tcase_add_test(tc_tax, test_tay_pos);
    tcase_add_test(tc_tax, test_tay_zero_flag);
    tcase_add_test(tc_tax, test_tay_neg);

    suite_add_tcase(s, tc_tax);

    tc_push_pull = tcase_create("Push+Pull");
    tcase_add_test(tc_push_pull, test_push);
    tcase_add_test(tc_push_pull, test_pull);
    suite_add_tcase(s, tc_push_pull);

    tc_shift = tcase_create("Shift");
    tcase_add_test(tc_shift, test_asl);
    tcase_add_test(tc_shift, test_lsr);
    suite_add_tcase(s, tc_shift);

    return s;
}

int main(void) {
    int failed_count = 0;
    Suite *s = instructions();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    failed_count = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (failed_count == 0) {
        printf("All tests passed!\n");
    } else {
        printf("%d tests failed.\n", failed_count); 
    }

    return 0;
}
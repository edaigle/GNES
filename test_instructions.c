#include <check.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "instructions.h"

START_TEST(test_lda_immediate_data)
{
    CPU_6502 cpu = {0, 0, 0};
    unsigned char instruction[3] = {0x9a, 0x05, 0x00};

    lda(&cpu, &instruction[0], Immediate);

    ck_assert_int_eq(cpu.accumulator, 0x05);
    ck_assert((cpu.status & 0b00000010) == 0);
    ck_assert((cpu.status & 0b10000000) == 0);

    // TODO: add negative case
}
END_TEST

START_TEST(test_lda_zero_flag)
{
    CPU_6502 cpu = {0, 0, 0};
    unsigned char instruction[3] = {0x9a, 0x00, 0x00};

    lda(&cpu, &instruction[0], Immediate);

    ck_assert_int_eq(cpu.accumulator, 0x00);
    ck_assert_int_eq(cpu.status & 0b00000010, 0b10);
}
END_TEST

START_TEST(test_dex_pos)
{
    CPU_6502 cpu = {0, 2, 0, 0, 0};

    dex(&cpu);

    ck_assert_int_eq(cpu.registerX, 0x1);
    ck_assert((cpu.status & 0b00000010) == 0);
    ck_assert((cpu.status & 0b10000000) == 0);

    // TODO: add negative case
}
END_TEST

START_TEST(test_dex_pos_zero_flag)
{
    CPU_6502 cpu = {0, 1, 0, 0, 0};

    dex(&cpu);

    ck_assert_int_eq(cpu.registerX, 0);
    ck_assert((cpu.status & 0b00000010) == 0b10);
    ck_assert((cpu.status & 0b10000000) == 0);
}
END_TEST

START_TEST(test_dey_pos)
{
    CPU_6502 cpu = {0, 0, 2, 0, 0};

    dey(&cpu);

    ck_assert_int_eq(cpu.registerY, 0x1);
    ck_assert((cpu.status & 0b00000010) == 0);
    ck_assert((cpu.status & 0b10000000) == 0);

    // TODO: add negative case
}
END_TEST

START_TEST(test_dey_pos_zero_flag)
{
    CPU_6502 cpu = {0, 1, 0, 0, 0};

    dex(&cpu);

    ck_assert_int_eq(cpu.registerY, 0);
    ck_assert((cpu.status & 0b00000010) == 0b10);
    ck_assert((cpu.status & 0b10000000) == 0);
}
END_TEST

Suite *lda_suite(void)
{
    Suite *s;
    TCase *tc_lda, *tc_dec;

    s = suite_create("Instructions");
    
    tc_lda = tcase_create("LDA");
    tcase_add_test(tc_lda, test_lda_immediate_data);
    tcase_add_test(tc_lda, test_lda_zero_flag);

    tc_dec = tcase_create("DEX+DEY");
    tcase_add_test(tc_dec, test_dex_pos);
    tcase_add_test(tc_dec, test_dex_pos_zero_flag);
    tcase_add_test(tc_dec, test_dey_pos);
    tcase_add_test(tc_dec, test_dey_pos_zero_flag);
    
    suite_add_tcase(s, tc_dec);

    return s;
}

int main(void) {
    int failed_count = 0;
    Suite *s = lda_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    failed_count = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (failed_count == 0) {
        printf("All tests passed!\n");
    } else {
        printf("%d tests failed.\n", failed_count); 
    }

    return 0;
}
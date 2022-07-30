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

    tax(&m);

    ck_assert_int_eq(m.registerX, 0x2);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0);

}
END_TEST

START_TEST(test_tax_neg)
{
    Machine m = {0xff, 0, 0, 0, 0, 0};

    tax(&m);

    ck_assert_int_eq(m.registerX, 0xff);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0b10000000);

}
END_TEST

START_TEST(test_tax_zero_flag)
{
    Machine m = {0, 1, 0, 0, 0, 0};

    tax(&m);

    ck_assert_int_eq(m.registerX, 0);
    ck_assert((m.status & 0b00000010) == 0b10);
    ck_assert((m.status & 0b10000000) == 0);
}
END_TEST

START_TEST(test_tay_pos)
{
    Machine m = {2, 0, 0, 0, 0, 0};

    tay(&m);

    ck_assert_int_eq(m.registerY, 0x2);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0);

}
END_TEST

START_TEST(test_tay_neg)
{
    Machine m = {0xff, 0, 0, 0, 0, 0};

    tay(&m);

    ck_assert_int_eq(m.registerY, 0xff);
    ck_assert((m.status & 0b00000010) == 0);
    ck_assert((m.status & 0b10000000) == 0b10000000);

}
END_TEST

START_TEST(test_tay_zero_flag)
{
    Machine m = {0, 0, 2, 0, 0, 0};

    tay(&m);

    ck_assert_int_eq(m.registerY, 0);
    ck_assert((m.status & 0b00000010) == 0b10);
    ck_assert((m.status & 0b10000000) == 0);
}
END_TEST

Suite *lda_suite(void)
{
    Suite *s;
    TCase *tc_lda, *tc_dec, *tc_tax;

    s = suite_create("Instructions");
    
    tc_lda = tcase_create("LDA");
    tcase_add_test(tc_lda, test_lda_immediate_data);
    tcase_add_test(tc_lda, test_lda_zero_flag);

    suite_add_tcase(s, tc_lda);

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
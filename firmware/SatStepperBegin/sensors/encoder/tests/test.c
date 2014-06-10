/**
 * Organization:    The Green Box
 * Project name:    Satellite stepper drive
 *
 * @file            encoder.c
 * @brief           Encoder logic test module
 *
 */

const int _TEST_STEP_NUM = 255;
const unsigned int PERIOD = 4;

unsigned char true_queue_a[] = {0, 1, 1, 0};
unsigned char true_queue_b[] = {0, 0, 1, 1};

#ifdef SAT_STEPPER___TEST

#include <stdio.h>
#include "gray_code_decoder.h"

int main(int argn, char** args) {
    fprintf(stderr, "unit test of encoder module\n");
    fprintf(stderr, "use it with x86 gcc\n");

    int counter = 0;
    unsigned char prev_a = 0;
    unsigned char prev_b = 0;
    // forward moving
    for ( int step = 0; step <= _TEST_STEP_NUM; ++step) {
        int norm_step = step % PERIOD;
        counter += greyCodeStepDecoder(prev_a, prev_b, true_queue_a[norm_step], true_queue_b[norm_step]);
        prev_a = true_queue_a[norm_step];
        prev_b = true_queue_b[norm_step];
    }

    if (counter != _TEST_STEP_NUM) {
        fprintf(stderr, "Forward moving test failed\n");
        fprintf(stderr, "%d != %d\n", counter, _TEST_STEP_NUM);
        return 1;
    }
    else {
        fprintf(stderr, "%d == %d\n", counter, _TEST_STEP_NUM);
        fprintf(stderr, "Forward moving test passed\n");
    }
    counter = 0;
    prev_a = 0;
    prev_b = 0;
    // backward moving
    for ( int step = _TEST_STEP_NUM; step > 0; --step) {
        int norm_step = step % PERIOD;
        counter += greyCodeStepDecoder(prev_a, prev_b, true_queue_a[norm_step], true_queue_b[norm_step]);
        prev_a = true_queue_a[norm_step];
        prev_b = true_queue_b[norm_step];
    }
    if (counter != -_TEST_STEP_NUM) {
        fprintf(stderr, "Backward moving test failed\n");
        fprintf(stderr, "%d != %d\n", counter, _TEST_STEP_NUM);
        return 1;
    }
    else {
        fprintf(stderr, "%d == %d\n", counter, -_TEST_STEP_NUM);
        fprintf(stderr, "Backward moving test passed\n");
    }

    return 0;
}
#endif

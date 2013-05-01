/* ========================================================
 * Organization: The green box 
 *   
 * Project name: Satellite stepper drive
 * File name: control_algo.c
 * Description: module for setting algo type and sending
 * A and B phase states for next step 
 * ========================================================
 */

//step by step phase state arrays for different algorythms
static int one_phase_algo_A[ONE_TWO_PHASE_STEPS_NUMBER]  = { 1 , 0 , -1 ,  0 };
static int one_phase_algo_B[ONE_TWO_PHASE_STEPS_NUMBER]  = { 0 , 1 ,  0 , -1 };

static int two_phase_algo_A[ONE_TWO_PHASE_STEPS_NUMBER]  = { 1 , -1 , -1 ,  1 };
static int two_phase_algo_B[ONE_TWO_PHASE_STEPS_NUMBER]  = { 1 ,  1 , -1 , -1 };

static int half_phase_algo_A[HALF_PHASE_STEPS_NUMBER] = { 1 , 1 , 0 , -1 , -1 , -1,   0 ,  1 };
static int half_phase_algo_B[HALF_PHASE_STEPS_NUMBER] = { 0 , 1 , 1 ,  1 ,  0 , -1 , -1 , -1 };

struct algo_type
{
    int* phase_A;
    int* phase_B;
    int algo_steps_number;
};

static struct algo_type one_phase_parametrs, two_phase_parametrs, half_phase_parametrs;

//const structure variables init
one_phase_parametrs.phase_A = one_phase_algo_A;
one_phase_parametrs.phase_B = one_phase_algo_B;
one_phase_parametrs.algo_steps_number = ONE_TWO_PHASE_STEPS_NUMBER;

two_phase_parametrs.phase_A = two_phase_algo_A;
two_phase_parametrs.phase_B = two_phase_algo_B;
two_phase_parametrs.algo_steps_number = ONE_TWO_PHASE_STEPS_NUMBER;

half_phase_parametrs.phase_A = half_phase_algo_A;
half_phase_parametrs.phase_B = half_phase_algo_B;
half_phase_parametrs.algo_steps_number = HALF_PHASE_STEPS_NUMBER;

static struct algo_type* p_current_algo_struct = NULL;
static int next_step = 0;

int set_algo_type(int algo_type_code)
{
    switch (algo_type_code) 
    {
        case ONE_PHASE_CODE:
            p_current_algo_struct = &one_phase_parametrs;
            break;
        case TWO_PHASE_CODE: 
            p_current_algo_struct = &two_phase_parametrs;
            break;
        case HALF_PHASE_CODE:
            p_current_algo_struct = &half_phase_parametrs;
            break;
        default:
            return 1;
    }
    return 0;
}


int get_next_step(int* phase_A, int* phase_B)
{
    if (p_current_algo_struct == NULL)
    {
        return 1;
    }
    *phase_A = p_current_algo_struct->phase_A[next_step];
    *phase_B = p_current_algo_struct->phase_B[next_step];
    if (++next_step < p_current_algo_struct->algo_steps_number)
    {
        next_step = 0;
    }
    return 0;
}
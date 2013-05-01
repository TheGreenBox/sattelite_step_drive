#define ONE_TWO_PHASE_STEP_NUMBER   4
#define HALF_PHASE_STEP_NUMBER      4
#define NUMBER_OF_ALGOS             3
#define INVALID                     0
#define ONE_PHASE                   1
#define TWO_PHASE                   2
#define HALF_PHASE                  3

//step by step phase state arrays for different algorythms
static int one_phase_algo_A[]  = { 1 , 0 , -1 , 0 };
static int one_phase_algo_B[]  = { 0 , 1 , 0 , -1 };

static int two_phase_algo_A[]  = { 1 , -1 , -1 , 1 };
static int two_phase_algo_B[]  = { 1 , 1 , -1 , -1 };

static int half_phase_algo_A[] = { 1 , 1 , 0 , -1 , -1 , -1, 0 , 1 };
static int half_phase_algo_B[] = { 0 , 1 , 1 , 1 , 0 , -1 , -1 , -1 };

struct algo_type
{
    int* phase_A;
    int* phase_B;
    int algo_steps_number;
};

struct algo_type one_phase_parametrs, two_phase_parametrs, half_phase_parametrs;

//const structure variables init
one_phase_parametrs.phase_A = one_phase_algo_A;
one_phase_parametrs.phase_B = one_phase_algo_B;
one_phase_parametrs.algo_steps_number = 4;

two_phase_parametrs.phase_A = two_phase_algo_A;
two_phase_parametrs.phase_B = two_phase_algo_B;
two_phase_parametrs.algo_steps_number = 4;

half_phase_parametrs.phase_A = half_phase_algo_A;
half_phase_parametrs.phase_B = half_phase_algo_B;
half_phase_parametrs.algo_steps_number = 8;

struct algo_type* phase_parametrs[NUMBER_OF_ALGOS] = {&one_phase_parametrs, &two_phase_parametrs, &half_phase_parametrs};

int* set_algo_type(int algo_type_code)
{
    if ( algo_type_code > 3 || algo_type_code < 1 )
    {
        printf("There is no algorythm type with this code\n");
        return;
    }
    return int* struct_pointer = phase_parametrs[i];
}
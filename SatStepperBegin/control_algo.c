#define INVALID     0
#define ONE_PHASE   1
#define TWO_PHASE   2
#define HALF_PHASE  3

//step by step phase state arrays for different algorythms
int one_phase_algo_A[]  = { 1 , 0 , -1 , 0 };
int one_phase_algo_B[]  = { 0 , 1 , 0 , -1 };

int two_phase_algo_A[]  = { 1 , -1 , -1 , 1 }
int two_phase_algo_B[]  = { 1 , 1 , -1 , -1 }

int half_phase_algo_A[] = { 1 , 1 , 0 , -1 , -1 , -1, 0 , 1 }
int half_phase_algo_B[] = { 0 , 1 , 1 , 1 , 0 , -1 , -1 , -1 }

struct algo_type 
{
    int* phase_A;
    int* phase_B;
    int algo_steps_number;
};

struct algo_type one_phase_parametrs, two_phase_parametrs, half_phase_parametrs;

one_phase_parametrs.phase_A = &one_phase_algo_A[0];
one_phase_parametrs.phase_B = &one_phase_algo_B[0];
one_phase_parametrs.algo_steps_number = 4;

two_phase_parametrs.phase_A = &two_phase_algo_A[0];
two_phase_parametrs.phase_B = &two_phase_algo_B[0];
two_phase_parametrs.algo_steps_number = 4;

half_phase_parametrs.phase_A = &half_phase_algo_A[0]
half_phase_parametrs.phase_B = &half_phase_algo_B[0]
half_phase_parametrs.algo_steps_number = 8;


void main()
{

}
#include "pid.h"

struct PID_struct_type {float K_p; float K_i; float K_d; float Time_step; float Max_control_input; float error_sum; float previous_error;};

struct PID_struct_type PID;


//Init PID
void pid_init(float k_p, float k_i, float k_d, float time_step, float max_control_input) {
    PID.K_p = k_p;
    PID.K_i = k_i;
    PID.K_d = k_d;
    PID.Time_step = time_step;
    PID.Max_control_input = max_control_input;
    PID.error_sum = 0;
    PID.previous_error = 0;
}

//Regulator
float pid_regulator(float reference, float current_value) {
	
	float reference_float = (float)reference;
	
    float error  = reference - current_value;
    PID.error_sum += error;

    float p_gain = PID.K_p * error;
    float i_gain = PID.K_i * PID.error_sum;
    float d_gain = PID.K_d * (error - PID.previous_error)/PID.Time_step;

    //updating previous error
    PID.previous_error = error;

    float control_input = p_gain + i_gain + d_gain;

    //enabling saturation so the controller doesn't go crazy
    if (control_input > PID.Max_control_input) 
    {
        control_input = PID.Max_control_input;
    }
    else if (control_input < -PID.Max_control_input) 
    {
        control_input = -PID.Max_control_input;
    }
    
    return control_input;

}
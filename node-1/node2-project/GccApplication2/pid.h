#ifndef PID_H_
#define PID_H_



struct PID_struct_type {float K_p; float K_i; float K_d; float Time_step; float Max_control_input; float error_sum; float previous_error;};
	
struct PID_struct_type PID;


void pid_init(float k_p, float k_i, float k_d, float time_step, int max_control_input);
float pid_regulator(float reference, float current_value);


#endif /* PID_H_ */
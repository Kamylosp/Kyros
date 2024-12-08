#ifndef PID_H
#define PID_H

typedef struct {
    float Kp;
    float Ki;
    float Kd;

    float setpoint;
    float input;
    float integral_sum;
    float error_prev;

    float max;
    float min;
} PIDController;

void PID_setup(PIDController* controller, float kp, float ki, float kd, float setpoint, float max, float min);
float PID_action(PIDController* controller, float error);

#endif /* PID_H */

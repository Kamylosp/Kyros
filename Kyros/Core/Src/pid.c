#include "miros.h"
#include "pid.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE

float PERIOD_TOF_SENSOR = 0.05;     // em segundos

void PID_setup(PIDController* controller, float kp, float ki, float kd, float setpoint, float max, float min) {
    Q_ASSERT(controller);

    controller->Kp = kp;
    controller->Ki = ki;
    controller->Kd = kd;
    controller->setpoint = setpoint;
    controller->input = 0.0;
    controller->integral_sum = 0.0;
    controller->error_prev = 0.0;
    controller->max = max;
    controller->min = min;
}

float PID_action(PIDController* controller, float error) {
    Q_ASSERT(controller);

    controller->integral_sum = controller->integral_sum + (error * PERIOD_TOF_SENSOR);
    float derivative_term = (error - controller->error_prev) / PERIOD_TOF_SENSOR;

    controller->error_prev = error;

    float comp_p = (controller->Kp * error);
    float comp_i = (controller->Ki * controller->integral_sum);
    float comp_d = (controller->Kd * derivative_term);
    
    float output = comp_p + comp_i + comp_d;

    if (output > controller->max) {
      output = controller->max;
    }
    if (output < controller->min) {
      output = controller->min;
    }

    return output;
}

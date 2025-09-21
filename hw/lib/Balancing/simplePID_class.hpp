
class PIDController {
private:
    double Kp, Ki, Kd;
    double previousError, integral;

public:
    PIDController(double p, double i, double d) : Kp(p), Ki(i), Kd(d), previousError(0), integral(0) {}

    double calculateControlSignal(double setpoint, double measuredValue) {
        double error = setpoint - measuredValue;
        integral += error;
        double derivative = error - previousError;
        double output = Kp * error + Ki * integral + Kd * derivative;
        previousError = error;
        return output;
    }
};
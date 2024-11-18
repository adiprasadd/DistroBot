#pragma config(Sensor, S2,     left_colour,    sensorEV3_Color)
#pragma config(Sensor, S3,     right_colour,   sensorEV3_Color)
#pragma config(Motor,  motorC,          left_motor,    tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          right_motor,   tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	float kp = 0.15;
	float kd = 0.01;
	float ki = 0.00001;
	float last_error = 0, error = 0, derivative = 0, integral = 0, correction = 0, base_speed = -25;
	nMotorEncoder[motorC] = 0;
	while(abs(nMotorEncoder[motorC]) < 1500) {
		error = getColorReflected(S3) - getColorReflected(S2);
		datalogAddValue(1, error);
		integral += error;
		derivative = error - last_error;
		correction = kp * error + ki * integral + kd * derivative;

		motor[motorC] = base_speed + correction;
		motor[motorD] = base_speed - correction;
		last_error = error;

	}


}

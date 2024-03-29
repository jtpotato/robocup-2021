#pragma config(Sensor, S1,     leftSensor,     sensorEV3_Color)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while (true) {
		float leftSensorValue = getColorReflected(leftSensor); //Left sensor value
		float rightSensorValue = getColorReflected(rightSensor); //Right sensor value

		//Tweaking the values
		leftSensorValue = leftSensorValue/2;
		rightSensorValue = rightSensorValue/2;
		//Green
		if (leftSensorValue < 25) {
			if (getColorName(leftSensor) == colorGreen || getColorName(rightSensor) == colorBlue) {
				playSound(soundBlip);
				moveMotorTarget(rightMotor, 420, 100);
			}
		}
		else if (rightSensorValue < 25) {
			if (getColorName(rightSensor) == colorGreen || getColorName(rightSensor) == colorBlue) {
				moveMotorTarget(rightMotor, 420, 100);
			}
		}

		//Main line following
		else {
			if (leftSensorValue < 20) {
				leftSensorValue = -100;
				rightSensorValue = 100;
			}
			if (rightSensorValue < 20) {
				rightSensorValue = -100;
				leftSensorValue = 100;
			}

			setMotorSpeed(leftMotor, leftSensorValue); //Set leftMotor speed
			setMotorSpeed(rightMotor, rightSensorValue); //Set leftMotor speed

		}
	}
}

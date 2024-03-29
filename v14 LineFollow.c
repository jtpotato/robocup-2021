#pragma config(Sensor, S1,     leftSensor,     sensorEV3_Color)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float leftSensorValue;
float rightSensorValue;

float leftMotorSpeed;
float rightMotorSpeed;

//Line following
void lineFollow() { //function
	//Tweaking the values
	leftMotorSpeed = leftSensorValue-30;
	rightMotorSpeed = rightSensorValue-30;

	//If the robot veers too far off course, we turn aggressively
	if (leftSensorValue < 20) { //emergency value
		leftMotorSpeed = -80;
		rightMotorSpeed = 80;
	}
	if (rightSensorValue < 20) {
		rightMotorSpeed = -80;
		leftMotorSpeed = 80;
	}

	setMotorSpeed(leftMotor, leftMotorSpeed); //Set leftMotor speed
	setMotorSpeed(rightMotor, rightMotorSpeed); //Set rightMotor speed
}

//Green, for right sensor
void rightSensorGreen() {
	if (getColorName(rightSensor) == colorGreen) {
		//Check if its really green
		setMotorSpeed(leftMotor, 10);
		setMotorSpeed(rightMotor, 10);
		sleep(50);
		if (getColorName(rightSensor) == colorGreen) {
			playSound(soundBlip);
			//turn
			moveMotorTarget(leftMotor, 360, 80);
			sleep(400);
		}
	}
}

//Green, for left sensor
void leftSensorGreen() {
	if (getColorName(leftSensor) == colorGreen) {
		//Check if its really green
		setMotorSpeed(leftMotor, 10);
		setMotorSpeed(rightMotor, 10);
		sleep(50);
		if (getColorName(leftSensor) == colorGreen) {
			playSound(soundBlip);
			//turn
			moveMotorTarget(rightMotor, 360, 80);
			sleep(400);
		}
		else {
		}
	}
}

void doubleGreen() {
	if (getColorName(leftSensor) == colorGreen || getColorName(leftSensor) == colorBlue || getColorName(leftSensor) == colorNone) {
		if (getColorName(rightSensor) == colorGreen || getColorName(rightSensor) == colorBlue || getColorName(leftSensor) == colorNone) {
			////Check if its really green
			//setMotorSpeed(leftMotor, 10);
			//setMotorSpeed(rightMotor, 10);
			//sleep(50);
			if (getColorName(leftSensor) == colorGreen || getColorName(leftSensor) == colorBlue || getColorName(leftSensor) == colorNone) {
				if (getColorName(leftSensor) == colorGreen || getColorName(leftSensor) == colorBlue || getColorName(leftSensor) == colorNone) {

					//Chemical Spill

					playSound(soundBeepBeep);
					setMotorSpeed(leftMotor, 45);
					setMotorSpeed(rightMotor, 45);
					sleep(1000);

					//Spin telemetry
					int motorBSpinDistance;
					int motorCSpinDistance;
					resetMotorEncoder(leftMotor);
					resetMotorEncoder(rightMotor);

					//Seekin
					while (getUSDistance(S4) > 25) {
						setMotorSpeed(leftMotor, 10);
						setMotorSpeed(rightMotor, -10);
					}
					motorBSpinDistance = getMotorEncoder(leftMotor);
					motorCSpinDistance = getMotorEncoder(rightMotor);

					//Backup telemetry
					int motorBBackupDistance;
					int motorCBackupDistance;
					resetMotorEncoder(leftMotor);
					resetMotorEncoder(rightMotor);

					//Backup, open claw
					setMotorSpeed(motorA, -33);
					setMotorSpeed(leftMotor, -30);
					setMotorSpeed(rightMotor, -30);
					sleep(300);

					//Continue backing up to get distance right.
					while (getUSDistance(S4) < 20) {
						setMotorSpeed(leftMotor, -69.42);
						setMotorSpeed(rightMotor, -69.42);
					}
					motorBBackupDistance = getMotorEncoder(leftMotor);
					motorCBackupDistance = getMotorEncoder(rightMotor);

					//Flip around
					moveMotorTarget(leftMotor, 340, 20);
					moveMotorTarget(rightMotor, 340, -20);
					sleep(2000);

					//Run backwards
					playSound(soundDownwardTones);
					setMotorSpeed(leftMotor, 0); //yh idk motor functions are asynchronous and weird ig
					setMotorSpeed(rightMotor, 0);
					sleep(1);
					setMotorSpeed(leftMotor, -33);
					setMotorSpeed(rightMotor, -33);
					sleep(1334);

					//Close claw
					setMotorSpeed(motorA, 120);
					sleep(433);

					//Run back in
					setMotorSpeed(leftMotor, 20);
					setMotorSpeed(rightMotor, 20);
					setMotorSpeed(motorA, 120);
					sleep(666);

					//Demonstrate control
					//Left
					setMotorSpeed(leftMotor, -15);
					setMotorSpeed(rightMotor, 15);
					setMotorSpeed(motorA, 120);
					sleep(500);
					//Right
					setMotorSpeed(leftMotor, 15);
					setMotorSpeed(rightMotor, -15);
					setMotorSpeed(motorA, 120);
					sleep(500);

					setMotorSpeed(leftMotor, 0);
					setMotorSpeed(rightMotor, 0);
					setMotorSpeed(motorA, 0);
					sleep(1000);
					playSound(soundBeepBeep);

					setMotorSpeed(leftMotor, 0);
					setMotorSpeed(rightMotor, 0);
					setMotorSpeed(motorA, -30);
					sleep(2000);

					//Forward a bit
					moveMotorTarget(leftMotor, 75, 10);
					moveMotorTarget(rightMotor, 75, 10);
					sleep(1000);

					//Push out
					setMotorSpeed(motorA, 120);
					sleep(1000);

					//Release, and run back at the same time
					/*moveMotorTarget(leftMotor, 720, 20);
					moveMotorTarget(rightMotor, 720, 20);
					sleep(1000);*/

					//Move to start
					setMotorSpeed(leftMotor, 0);
					setMotorSpeed(rightMotor, 0);
					sleep(1);
					setMotorSpeed(leftMotor, 40);
					setMotorSpeed(rightMotor, 40);
					sleep(1334); //1334
					//Backed up
					/*moveMotorTarget(leftMotor, motorBBackupDistance, 20);
					moveMotorTarget(rightMotor, motorCBackupDistance, 20);
					sleep(2000);*/

					//Spin to face the start
					moveMotorTarget(leftMotor, motorBSpinDistance, -20); //We solemnly swear this is spinning the opposite direction.
					moveMotorTarget(rightMotor, motorBSpinDistance, 20);
					sleep(5000);

					//RUN TO THE LINEEE

					while (true) {
						setMotorSpeed(leftMotor, 20);
						setMotorSpeed(rightMotor, 20);

						if (getColorName(leftSensor) == colorBlack || getColorName(rightSensor) == colorBlack) {
							//This for some reason won't compile if we put it in the while loop
							break;
						}
					}
				}
			}
		}
	}
	else {
		playSound(soundException);
		string tmp = getColorHue(leftSensor);
		displayBigTextLine(1, tmp);
		sleep(1000);
		stopAllTasks();
	}
}

//Main process.
task main()
{
	setMotorSpeed(motorA, 120);
	sleep(200);
	while (true) {
		leftSensorValue = getColorReflected(leftSensor); //Left sensor value
		rightSensorValue = getColorReflected(rightSensor); //Right sensor value

		//Display Values
		/*string leftValueString = leftSensorValue;
		string rightValueString = rightSensorValue;
		strcat(leftValueString, " ");
		strcat(leftValueString, rightValueString);
		string stringToDisplay = leftValueString;
		displayBigTextLine(1, stringToDisplay);*/

		//Green:
		if (leftSensorValue < 30) {
			leftSensorGreen();
		}
		if (rightSensorValue < 30) {
			rightSensorGreen();
		}
		if (leftSensorValue > 90) {
			if (rightSensorValue > 90) {
				setMotorSpeed(leftMotor, 10);
				setMotorSpeed(rightMotor, 10);
				sleep(500);
				doubleGreen();
			}
		}

		//Water tower thing idk what this is called
		if (getUSDistance(S4) < 5) {
			//Turn right
			moveMotorTarget(leftMotor, 180, 20);
			moveMotorTarget(rightMotor, 180, -20);
			sleep(3000);
			//Curve
			setMotorSpeed(leftMotor, 20);
			setMotorSpeed(rightMotor, 40);
			sleep(3000);
			//Turn right to meet the line
			moveMotorTarget(leftMotor, 180, 20);
			moveMotorTarget(rightMotor, 180, -20);
			sleep(3000);
		}

		lineFollow();
	} //end of while loop
} //end of task main

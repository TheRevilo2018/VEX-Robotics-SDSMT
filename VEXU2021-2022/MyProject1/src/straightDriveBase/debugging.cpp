#include "drive.h"

using namespace std;

/*void FourWheelDrive::checkGyro()
{
	int count = 0;
	double pitch = 0;
  Brain.Screen.setCursor(5, 0);
  Brain.Screen.print("Starting Gyro Checks");

	lcd::set_text(6, strerror(errno));

	delay(LOOP_DELAY);
	pitch = inertialSensor->get_pitch();

	lcd::set_text(7, strerror(errno));

	while( pitch != infinity())
	{
		lcd::set_text(2, "status:" + to_string(inertialSensor->get_status()));
		lcd::set_text(3, strerror(errno));
		pitch = inertialSensor->get_pitch();
		lcd::set_text(1, "pitch: " + to_string(pitch));
		lcd::set_text(6, "num pitch sensor loops: " + to_string(count));
		lcd::set_text(4, "status:" + to_string(inertialSensor->get_status()));
		lcd::set_text(5, strerror(errno));
		delay(LOOP_DELAY);
		count++;
	}


	lcd::set_text(5, "pitch sensor loops done");
}

void FourWheelDrive::addStream(std::stringstream &gyroStream, float lastSpeed)
{
	float speed = getAllSpeed();

	gyroStream << inertialSensor->get_status()
			<< ", " << (speed - lastSpeed)
			<< ", " << speed
			<< ", " << inertialSensor->get_accel().x
			<< ", " << inertialSensor->get_accel().y
			<< ", " << inertialSensor->get_accel().z
			<< ", " << inertialSensor->get_pitch()
			<< ", " << inertialSensor->get_yaw()
			<< ", " << inertialSensor->get_gyro_rate().x
			<< ", " << inertialSensor->get_gyro_rate().y
			<< ", " << inertialSensor->get_gyro_rate().z
			<< ", " << leftMotors->front().get_current_draw()
			<< ", " << leftMotors->front().get_power()
			<< "\n";
}

void FourWheelDrive::correctGyroCalibration(float accel, float jerk)
{
	const int stationary = 100;
	const int moving = 350;
	float speed = 0;
	float intercept = 0;
	float mod = 0;
	float totalMod = 0;
	float lastSpeed = 0;

	float pitch;
	float accelMeter;
	std::stringstream gyroStream;

	//gyroStream << "Stationary, pitch, x, y, z\n";

	//for(int i = 0; i < stationary; i++)
	//{
		//addStream(gyroStream);
		//delay(LOOP_DELAY);
	//}
	intercept = intercept / stationary;
	lcd::set_text(2, "intercept: " + to_string(intercept));
	lcd::set_text(0, "accel: " + to_string(accel));

	gyroStream << "status, ecode accel, speed, xAccel, yAccel, zAccel, " <<
					"pitch, yaw, gyro_x, gyro_y, gyro_z, motor current draw, motor power\n";


	for( int i = 0; i < moving; i++)
	{
		speed += accel;
		accel += jerk;
		setMotors(speed);
		delay(LOOP_DELAY);

		pitch = inertialSensor->get_pitch();
		accelMeter = inertialSensor->get_accel().x;

		addStream(gyroStream, lastSpeed);
		lastSpeed = getAllSpeed();

		mod = (-pitch - intercept) / accelMeter;
		totalMod += mod;

		lcd::set_text(3, "mod: " + to_string(pitch) + " i: " + to_string(i));

	}
	mod = totalMod / moving;
	setMotors(0);
	lcd::set_text(3, "mod: " + to_string(pitch));

	delay(1000);

	ofstream usd_file_write("/usd/slope.csv", ofstream::out);
	if(usd_file_write.is_open())
	{
		lcd::set_text(5, "file opened");
		usd_file_write << gyroStream.str();
		usd_file_write.close();
	}
	else
	{
		lcd::set_text(5, "file failed to open");
	}


	lcd::set_text(7, "finished output");
}*/

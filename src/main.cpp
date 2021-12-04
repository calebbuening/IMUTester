#include "main.h"

bool running = false;
int phase = 0;
float count = 0;
int startTime = 0;

okapi::IMU imu(3);

bool rightButtonPressed = false;
bool leftButtonPressed = false;
bool centerButtonPressed = false;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	while(!pros::lcd::is_initialized()) pros::delay(20);
	pros::lcd::print(0, "THE GREAT IMU TESTER");
	pros::lcd::print(1, "--------------------");
	pros::lcd::print(2, "Press the left button to start");
	pros::lcd::print(7, "START");
}

void opcontrol() {
	while (true) {
		if(phase == 0){
			startTime = pros::millis();
			phase++;
			leftButtonPressed = false;
			pros::lcd::clear_line(2);
		}
		if(phase == 1){
			pros::lcd::print(1, "Rotation:%f\n", imu.get());
			if(pros::millis() - startTime > 60000) phase = 2;
		}
		if(phase == 2){
			pros::lcd::print(1, "Rot/Min: %4.2f", imu.get());
			pros::lcd::print(7, "RESTART");
			while(pros::lcd::read_buttons() != 4){
				pros::delay(5);
			}
			phase = 0;
		}
		pros::delay(5);
	}
}

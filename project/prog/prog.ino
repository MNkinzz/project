#include "prog.hpp"
#include "robot.hpp"

static Robot *robot;

void setup() {
    // setup robot
    robot = Robot::makeRobot();
}

void loop() {
    // run robot
    robot->loop();
}

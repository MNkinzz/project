#include "robot.hpp"
#include "bt.hpp"

Robot *Robot::makeRobot() {
    Robot *r;

    // create robot singletone
    r = new Robot();

    // setup serial
    Serial.begin(baud_rate_);

    // setup line sensors
    r->line_sensor_ = new Zumo32U4LineSensors();
    // use {SENSOR_DOWN1, SENSOR_DOWN3, SENSOR_DOWN5}
    r->line_sensor_->initThreeSensors();

    // setup proximity sensors
    r->proximity_sensor_ = new Zumo32U4ProximitySensors();
    // use left, front, right sensors
    r->proximity_sensor_->initThreeSensors();

    // reset encoders
    r->getCountsAndResetLeft();
    r->getCountsAndResetRight();

    // setup motors
    r->setSpeeds(0, 0);

    // setup localization
    // TODO

    // setup AI
    r->bt_ = BehaviorTree::makeBehaviorTree(r);

    // reset status
    r->calibrateSensors();
    r->reset_manual();

    return r;
}

void Robot::reset_manual() {
    // stop robot
    setSpeeds(0, 0);

    // clear encoder
    getCountsAndResetLeft();
    getCountsAndResetRight();
    l_cnt_ = 0;
    r_cnt_ = 0;
}

void Robot::reset_semi() {
    reset_manual();
}

void Robot::reset_auto() {
    reset_manual();
}


void Robot::loop() {
    switch (mode_) {
        case operation_mode::manual:
            manual_loop();
            break;
        case operation_mode::semi:
            semi_loop();
            break;
        case operation_mode::full:
            auto_loop();
            break;
        default:
            break;
    }
}

void Robot::manual_loop() {
    if (Serial.available() > 0) {
        String cmd;
        cmd = Serial.readString();
        cmd.trim();
        switch (cmd.charAt(0)) {
            case 'g':
                // goto
                switch (cmd.charAt(1)) {
                    case 'w':
                        // gw: forward
                        setSpeeds(100, 100);
                        break;
                    case 's':
                        // gs: backward
                        setSpeeds(-100, -100);
                        break;
                    case 'a':
                        // ga: turn left
                        setSpeeds(0, 100);
                        break;
                    case 'd':
                        // gd: turn right
                        setSpeeds(100, 0);
                        break;
                    case 't':
                        // gt: stop
                        setSpeeds(0, 0);
                        break;
                    default:
                        // invalid commmand
                        break;
                }
                break;
            case 's':
                // s: stop
                setSpeeds(0, 0);
                break;
            // case 'q':
            //     // q: query
            //     switch (cmd.charAt(1)) {
            //         case 'm':
            //             // qm: query mode
            //             String resp = "m:" + String(static_cast<int>(mode_)) + "\r\n";
            //             Serial.write(resp.c_str(), resp.length());
            //             break;
            //     }
            //     break;
            default:
                // invalid commmand
                break;
        }
    }
}

void Robot::semi_loop() {

}

void Robot::auto_loop() {

}


// utility functions

void Robot::setLeftSpeed(int16_t l_speed) {
    l_speed_ = l_speed;
    Zumo32U4Motors::setLeftSpeed(l_speed_);
}

void Robot::setRightSpeed(int16_t r_speed) {
    r_speed_ = r_speed;
    Zumo32U4Motors::setRightSpeed(r_speed_);
}

void Robot::setSpeeds(int16_t l_speed, int16_t r_speed) {
    l_speed_ = l_speed;
    r_speed_ = r_speed;
    Zumo32U4Motors::setSpeeds(l_speed_, r_speed_);
}

int16_t Robot::getLeftCounts() const {
    return l_cnt_;
}

int16_t Robot::getRightCounts() const {
    return r_cnt_;
}

int16_t Robot::getCountsLeft() {
    l_cnt_ = Zumo32U4Encoders::getCountsLeft();
    return l_cnt_;
}

int16_t Robot::getCountsRight() {
    r_cnt_ = Zumo32U4Encoders::getCountsRight();
    return r_cnt_;
}

int16_t Robot::getCountsAndResetLeft() {
    l_cnt_ = Zumo32U4Encoders::getCountsAndResetLeft();
    return l_cnt_;
}

int16_t Robot::getCountsAndResetRight() {
    r_cnt_ = Zumo32U4Encoders::getCountsAndResetRight();
    return r_cnt_;
}

int32_t Robot::x() const {
    return x_;
}

int32_t Robot::y() const {
    return y_;
}

const int32_t *Robot::map_dim() const {
    return map_dim_;
}

const int32_t *Robot::map() const {
    return map_;
}

void Robot::setOperationMode(uint16_t mode_index) {
    if (mode_index == static_cast<uint16_t>(mode_)) {
        return;
    }
    switch (mode_index) {
        case 0:
            mode_ = operation_mode::manual;
            reset_manual();
            break;
        case 1:
            mode_ = operation_mode::semi;
            reset_semi();
            break;
        case 2:
            mode_ = operation_mode::full;
            reset_auto();
            break;
        default:
            break;
    }
}

void Robot::calibrateSensors() {
    // this code is based on LineFollower.ino
    delay(1000);
    for (uint16_t i = 0; i < 120; ++i) {
        if (i > 30 && i <= 90) {
            setSpeeds(-200, 200);
        } else {
            setSpeeds(200, -200);
        }
        line_sensor_->calibrate();
    }
    setSpeeds(0, 0);
}

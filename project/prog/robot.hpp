#pragma once

#include "prog.hpp"

class BehaviorTree;

class Robot {
// interface
public:
    static Robot *makeRobot();
    void loop(void);

// handler
public:
    void reset_manual();
    void reset_semi();
    void reset_auto();

    void manual_loop();
    void semi_loop();
    void auto_loop();

// sensors
public:
    void calibrateSensors();

private:
    Zumo32U4LineSensors *line_sensor_ = nullptr;
    Zumo32U4ProximitySensors *proximity_sensor_ = nullptr;

    static constexpr int16_t num_line_sensors = 3;
    unsigned int line_sensor_reading_[num_line_sensors];

// actuators
public:
    void setLeftSpeed(int16_t l_speed);
    void setRightSpeed(int16_t r_speed);
    void setSpeeds(int16_t l_speed, int16_t r_speed);

    int16_t getLeftCounts() const;
    int16_t getRightCounts() const;

    int16_t getCountsLeft();
    int16_t getCountsAndResetLeft();
    int16_t getCountsRight();
    int16_t getCountsAndResetRight();

private:
    int16_t l_speed_ = 0;
    int16_t r_speed_ = 0;

    int32_t l_cnt_ = 0;
    int32_t r_cnt_ = 0;

// control
public:


private:


// localization
public:
    // robot position in map
    int32_t x() const;
    int32_t y() const;
    // robot direction using discretized angle
    int32_t theta() const;
    // map_dim[0] = height
    // map_dim[1] = width
    const int32_t *map_dim() const;
    const int32_t *map() const;

private:
    int32_t x_ = 0;
    int32_t y_ = 0;
    int32_t theta_ = 0;
    int32_t *map_dim_ = nullptr;
    int32_t *map_ = nullptr;


// AI
public:
    enum class operation_mode {
        manual, semi, full
    };
    operation_mode mode_ = operation_mode::manual;
    void setOperationMode(uint16_t mode_index);

private:
    BehaviorTree *bt_;

// communication
public:

private:
    static constexpr unsigned long baud_rate_ = 115200UL;

// helper
private:
    Robot() = default;
};

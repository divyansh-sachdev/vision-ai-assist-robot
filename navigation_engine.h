#ifndef NAVIGATION_ENGINE_H
#define NAVIGATION_ENGINE_H

#include <Arduino.h>

struct MotorCommand {
    int leftSpeed;
    int rightSpeed;
    bool obstacleHalt;
};

inline MotorCommand computeSteering(int targetOffsetX, int distanceCm) {
    MotorCommand cmd = {0, 0, false};
    if (distanceCm < 20) {
        cmd.obstacleHalt = true;
        return cmd;
    }

    int baseSpeed = 160;
    int turnDelta = targetOffsetX / 4;

    cmd.leftSpeed  = constrain(baseSpeed + turnDelta, -255, 255);
    cmd.rightSpeed = constrain(baseSpeed - turnDelta, -255, 255);
    return cmd;
}

#endif

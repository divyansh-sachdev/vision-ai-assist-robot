/**
 * VisionAI Assist Robot — Autonomous Mobile Assistant
 * Author: Divyansh Sachdev
 */

#include <Arduino.h>
#include "config.example.h"
#include "navigation_engine.h"

void setup() {
    Serial.begin(115200);
    pinMode(MOTOR_L_PWM, OUTPUT);
    pinMode(MOTOR_L_DIR, OUTPUT);
    pinMode(MOTOR_R_PWM, OUTPUT);
    pinMode(MOTOR_R_DIR, OUTPUT);

    Serial.println("==================================================");
    Serial.println("  VisionAI Assist Robot — Mobile Robotic Platform");
    Serial.println("==================================================");
    Serial.println("[INFO] Differential drive kinematics online.");
    Serial.println("[STATUS] Robot ready for visual autonomous guidance.");
}

void loop() {
    // Simulated visual target tracking (person offset X, distance in cm)
    int targetX = 15;
    int distance = 45;

    MotorCommand cmd = computeSteering(targetX, distance);

    if (cmd.obstacleHalt) {
        Serial.println("[NAV] Obstacle proximity halt triggered!");
    } else {
        Serial.printf("[NAV] Tracking target: Left Motor: %d | Right Motor: %d\n",
                      cmd.leftSpeed, cmd.rightSpeed);
    }

    delay(200);
}

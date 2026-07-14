# VisionAI Assist Robot

Autonomous differential-drive robotic companion equipped with computer vision target tracking, obstacle avoidance sensor fusion, and natural voice interaction. Designed to follow a user, navigate indoor environments, and carry lightweight payloads.

## System Architecture

- **Visual Following Loop**: Computes bounding box centroid displacement from an overhead camera and executes real-time proportional steering.
- **Proximity Sensor Ring**: Dual ultrasonic sensors and ToF laser rangefinder provide 360-degree safety envelope.
- **Motor Control**: Differential drive PWM velocity mixing implemented on ESP32 running FreeRTOS tasks.

## Pinout Configuration

| Function | Pin | Interface |
| --- | --- | --- |
| Left Motor PWM | GPIO 25 | PWM |
| Left Motor DIR | GPIO 26 | Digital Out |
| Right Motor PWM| GPIO 27 | PWM |
| Right Motor DIR| GPIO 14 | Digital Out |
| Ultrasonic Trig| GPIO 18 | Digital Out |
| Ultrasonic Echo| GPIO 19 | Interrupt In |

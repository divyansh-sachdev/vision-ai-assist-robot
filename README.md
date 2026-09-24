<div align="center">

# VisionAI Assist Robot

**Differential-drive companion robot with visual target tracking and proportional steering**

![Domain](https://img.shields.io/badge/Domain-Reactive_Navigation-00F3FF?style=for-the-badge) ![Platform](https://img.shields.io/badge/Platform-ESP32-9D00FF?style=for-the-badge) ![Control](https://img.shields.io/badge/Control-Proportional-0066FF?style=for-the-badge)

![ESP32](https://img.shields.io/badge/ESP32-0D1117?style=flat-square&logo=espressif&logoColor=white) ![Arduino](https://img.shields.io/badge/Arduino-0D1117?style=flat-square&logo=arduino&logoColor=white) ![C++](https://img.shields.io/badge/C++-0D1117?style=flat-square&logo=cplusplus&logoColor=white) ![Computer_Vision](https://img.shields.io/badge/Computer_Vision-0D1117?style=flat-square) ![Ultrasonic](https://img.shields.io/badge/Ultrasonic-0D1117?style=flat-square) ![Differential_Drive](https://img.shields.io/badge/Differential_Drive-0D1117?style=flat-square)

</div>

---

## Overview

An autonomous differential-drive robot that follows a person, avoids obstacles and carries light
payloads indoors.

The control approach is deliberately reactive rather than map-based. Instead of building a SLAM map,
the robot closes a tight loop on one scalar — how far the tracked target's centroid sits from the
frame centre — and converts that error directly into a steering differential. It is a classic visual
servoing loop, and for an indoor follow-me task it is both far cheaper computationally and more robust
than localisation.

## Domain &amp; Techniques

| Layer | Implementation |
| :--- | :--- |
| **Visual Tracking** | Bounding-box centroid displacement from frame centre gives a single signed error term, `targetOffsetX` |
| **Proportional Steering** | `computeSteering()` converts that error into a turn delta (error / 4) applied differentially — left speed + delta, right speed &minus; delta |
| **Output Clamping** | Both wheel commands constrained to &plusmn;255 so a large tracking error can never saturate into an uncontrolled spin |
| **Obstacle Override** | Ultrasonic range below 20&nbsp;cm raises `obstacleHalt` and zeroes both motors — the safety check preempts the tracking loop entirely |
| **Drive** | PWM + DIR differential velocity mixing to the motor driver |

## Pipeline

```
camera --> target bounding box --> centroid offset from frame centre (targetOffsetX)
                                                |
ultrasonic --> distance --[ < 20 cm ]--> HALT --+  (safety preempts tracking)
                                                |
                                         turn delta = offset / 4
                                                |
                          left = base + delta   |   right = base - delta
                                                |
                                     constrain to +/- 255
                                                |
                                                v
                                    PWM + DIR --> motor driver
```

## Pinout

| Function | Pin | Interface |
| --- | --- | --- |
| Left Motor PWM | GPIO 25 | PWM |
| Left Motor DIR | GPIO 26 | Digital Out |
| Right Motor PWM| GPIO 27 | PWM |
| Right Motor DIR| GPIO 14 | Digital Out |
| Ultrasonic Trig| GPIO 18 | Digital Out |
| Ultrasonic Echo| GPIO 19 | Interrupt In |

## Repository Layout

| Path | Purpose |
| :--- | :--- |
| `VisionAIAssistRobot.ino` | Main firmware — sensor loop, tracking input, motor dispatch |
| `navigation_engine.h` | `computeSteering()` — proportional control law and obstacle override |
| `config.example.h` | Base speed and safety distance — copy to `config.h` |

## Project Status

**Implemented:** proportional visual servoing with output clamping, ultrasonic obstacle override that
preempts the tracking loop, differential drive mixing.

**Roadmap:** the proportional term alone produces steady-state lag on a moving target — adding
derivative damping (full PD control) is the natural refinement. Beyond that: a ToF rangefinder to
complement the ultrasonic ring at close range, and on-board person detection so the robot acquires its
own target rather than receiving a precomputed offset.

---

<div align="center">
  <sub>
    Part of the <b>AI + Robotics</b> engineering portfolio of
    <a href="https://github.com/divyansh-sachdev">Divyansh Sachdev</a><br>
    90+ national &amp; international competition wins &middot; IIT / NIT / IIIT podiums
  </sub>
</div>

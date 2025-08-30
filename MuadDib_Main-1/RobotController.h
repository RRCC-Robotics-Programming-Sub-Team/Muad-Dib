#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

class RobotController {
public:  
void setupMotors();  
void moveForward();  
void moveBackward();  
void turnLeft();  
void turnRight();  
void stopMotors();  
void avoidObstacle();};

#endif


/* ─────────────────────────────────────────────────────────────────────────────
   RRCC Space Grant Robotics — Muad-Dib

   CREDITS
   Lead Programmer: Bradley T. Harz
   Team:            Merwin Mendoza, Melissa Heng

   © 2025 RRCC Space Grant Robotics Team.
   License (code): Apache-2.0 — see LICENSE
   License (docs/images in repo): CC BY 4.0 — see LICENSE-docs
   ──────────────────────────────────────────────────────────────────────────── */

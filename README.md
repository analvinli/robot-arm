# 3-DOF Robot Arm with SG90 Servos

This project implements a **3-degree-of-freedom (3-DOF)** robot arm controlled with SG90 servos.
It uses **Inverse Kinematics** to calculate joint angles for a desired end effector position.

---

## Required Hardware
- ATmega328P
- 3 x SG90 micro servos
- Power supply suitable for 3 servos
- Base and 100mm Links (mine are 3d printed, see included STL files)

**CAD/3D Files:**  
- [STL files for 3D printing](./stl/)  

## Servo Configuration

- **Servo 1 (Base rotation):** rotates the arm left/right along the horizontal plane.  
- **Servo 2 (Shoulder joint):** moves the arm up/down, connecting the base to the first link. 
- **Servo 3 (Elbow joint):** controls the second link, adjusting the arm’s reach and vertical position.  

**See the full assembly** [here](./stl/arm_full_assembly.stl)

## Usage
1. **Calibrate your SG90 servos**
   - Pulse width range can vary between individual servos. Adjust min/max pulse lengths accordingly.

2. **Calculate joint angles**
   - Pass the desired `(x,y,z)` coordinates into the following functions:
     - `calc_S1(x, y, z)` → calculates servo 1 angle 
     - `calc_S2(x, y, z)` → calculates servo 2 angle  
     - `calc_S3(x, y, z)` → calculates servo 3 angle 

3. **Set servo positions**
  - Move each servo to the calculated angles to position the arm with `servo_set_position`

---

## Notes
- Ensure your servo power supply can handle all servos simultaneously. Insufficient power may cause reduced speed or unstable pose.
- My IK equations assume link length is 100mm. Adjust equations if your dimesnions differ

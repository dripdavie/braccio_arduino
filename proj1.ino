#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

/* Config to face 90 degrees straigth:
* Base = 25
* Shoulder = 90
* Elbow = 85
* Wrist = 90
* Wrist rot = 100
*/



int delay_b;
int Vbase;
int Vshoulder;
int Velbow;
int Vwrist_ver;
int Vwrist_rot;
int Vgripper;

// Default positin which is vertical facing 90 degrees
struct default_pos {
  int delay_b = 20;
  int base = 25;
  int shoulder = 90;
  int elbow = 85;
  int wrist_ver = 90;
  int wrist_rot = 100;
  int gripper = 180;
};

default_pos def;

void Vertical() {
  Vbase = 25;
  Vshoulder = 90;
  Velbow = 85;
  Vwrist_ver = 90;
  Vwrist_rot = 100;
  Vgripper = 180;
  Braccio.ServoMovement(def.delay_b, def.base, def.shoulder, def.elbow, def.wrist_ver, def.wrist_rot, def.gripper);
}

void PrepareForGrabFront() {
  Vbase = 25;
  Vshoulder = 83;
  Velbow = 0;
  Vwrist_ver = 0;
  Vwrist_rot = 100;
  Vgripper = 0;

  Braccio.ServoMovement(delay_b, Vbase, Vshoulder, Velbow, Vwrist_ver, Vwrist_rot, Vgripper);
}

void Grab() {
  Vgripper = 180;
  Braccio.ServoMovement(delay_b, Vbase, Vshoulder, Velbow, Vwrist_ver, Vwrist_rot, Vgripper);
}

void Release() {
  Vgripper = 0;
  Braccio.ServoMovement(delay_b, Vbase, Vshoulder, Velbow, Vwrist_ver, Vwrist_rot, Vgripper);
}

void PutBack(int sponge_num) {
  Vbase = 15;
  Vshoulder = 95;
  Velbow = 170 - sponge_num * 12;
  Vwrist_ver = 180;
  Vwrist_rot = 100;
  Braccio.ServoMovement(delay_b, Vbase, Vshoulder, Velbow, Vwrist_ver, Vwrist_rot, Vgripper);

  Release();
}

void RotateToRigth() {
  Vbase = 120;
  Braccio.ServoMovement(delay_b, Vbase, Vshoulder, Velbow, Vwrist_ver, Vwrist_rot, Vgripper);
}
void PrepareForGrabRigth() {
  RotateToRigth();
  Vshoulder = 83;
  Velbow = 0;
  Vwrist_ver = 0;
  Vwrist_rot = 100;
  Vgripper = 0;

  Braccio.ServoMovement(delay_b, Vbase, Vshoulder, Velbow, Vwrist_ver, Vwrist_rot, Vgripper);
}

void RotateToLeft() {
  Vbase = 120;
  Braccio.ServoMovement(delay_b, Vbase, Vshoulder, Velbow, Vwrist_ver, Vwrist_rot, Vgripper);
}

void PrepareForGrabLeft() {
  RotateToLeft();
  Vshoulder = 83;
  Velbow = 180;
  Vwrist_ver = 180;
  Vwrist_rot = 100;
  Vgripper = 0;

  Braccio.ServoMovement(delay_b, Vbase, Vshoulder, Velbow, Vwrist_ver, Vwrist_rot, Vgripper);
}
void setup() {
  // put your setup code here, to run once:
  Braccio.begin(-70);
  Vertical();
}

void loop() {
  PrepareForGrabFront();
  Grab();
  PutBack(0);
  Vertical();
  PrepareForGrabRigth();
  Grab();
  Vertical();
  PutBack(1);
  Vertical();
  PrepareForGrabLeft();
  Grab();
  Vertical();
  PutBack(2);
  exit(0);
}

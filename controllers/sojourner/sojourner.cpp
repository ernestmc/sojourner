/*
 * Copyright 1996-2021 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Description:  A controller for the Sojourner robot developped for an EiVd
 *               diploma project of Nicolas Uebelhart.
 *               Converted to C++ by Ernesto Corbellini
 */

#include <iostream>
#include <vector>

#include "robot-sdk-cpp/include/inorbit/inorbit.hpp"

#include <webots/Keyboard.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/GPS.hpp>
#include <webots/InertialUnit.hpp>
#include <webots/LightSensor.hpp>

#define TIME_STEP 64
#define VELOCITY 0.6
#define INORBIT_HOST "localhost"
#define INORBIT_PORT 6000

using namespace std;
using namespace webots;

class Sojourner : public Robot {
public:
  Sojourner();
  void move_4_wheels(double v);
  void move_6_wheels(double v);
  void turn_wheels_right();
  void turn_wheels_left();
  void wheels_straight();
  void turn_around(double v);
  vector<double> getPosition();
  vector<double> getOrientation();
  double getLight();
  
private:
  enum {
    back_left_bogie,
    front_left_bogie,
    front_left_arm,
    back_left_arm,
    front_left_wheel,
    middle_left_wheel,
    back_left_wheel,
    back_right_bogie,
    front_right_bogie,
    front_right_arm,
    back_right_arm,
    front_right_wheel,
    middle_right_wheel,
    back_right_wheel,
    JOINTS_MAX
  };
  Motor* motor[JOINTS_MAX];
  GPS* gps;
  InertialUnit* orientation;
  LightSensor* lightSensor;
};

Sojourner::Sojourner() {
  gps = getGPS("gps");
  orientation = getInertialUnit("inertial unit");
  lightSensor = getLightSensor("light sensor");
  motor[back_left_bogie] = getMotor("BackLeftBogie");
  motor[front_left_bogie] = getMotor("FrontLeftBogie");
  motor[front_left_arm] = getMotor("FrontLeftArm");
  motor[back_left_arm] = getMotor("BackLeftArm");
  motor[front_left_wheel] = getMotor("FrontLeftWheel");
  motor[middle_left_wheel] = getMotor("MiddleLeftWheel");
  motor[back_left_wheel] = getMotor("BackLeftWheel");
  motor[back_right_bogie] = getMotor("BackRightBogie");
  motor[front_right_bogie] = getMotor("FrontRightBogie");
  motor[front_right_arm] = getMotor("FrontRightArm");
  motor[back_right_arm] = getMotor("BackRightArm");
  motor[front_right_wheel] = getMotor("FrontRightWheel");
  motor[middle_right_wheel] = getMotor("MiddleRightWheel");
  motor[back_right_wheel] = getMotor("BackRightWheel");

  motor[front_left_wheel]->setPosition(INFINITY);
  motor[middle_left_wheel]->setPosition(INFINITY);
  motor[back_left_wheel]->setPosition(INFINITY);
  motor[front_right_wheel]->setPosition(INFINITY);
  motor[middle_right_wheel]->setPosition(INFINITY);
  motor[back_right_wheel]->setPosition(INFINITY);
  
  batterySensorEnable(TIME_STEP);
  gps->enable(TIME_STEP);
  orientation->enable(TIME_STEP);
  lightSensor->enable(TIME_STEP);
}

void Sojourner::move_4_wheels(double v) {
  motor[front_left_wheel]->setVelocity(v * VELOCITY);
  motor[middle_left_wheel]->setVelocity(v * VELOCITY);
  motor[back_left_wheel]->setVelocity(v * VELOCITY);
  motor[front_right_wheel]->setVelocity(v * VELOCITY);
  motor[middle_right_wheel]->setVelocity(v * VELOCITY);
  motor[back_right_wheel]->setVelocity(v * VELOCITY);

  motor[middle_right_wheel]->setAvailableTorque(0.0);
  motor[middle_left_wheel]->setAvailableTorque(0.0);
}

void Sojourner::move_6_wheels(double v) {
  motor[middle_right_wheel]->setAvailableTorque(2.0);
  motor[middle_left_wheel]->setAvailableTorque(2.0);

  motor[front_left_wheel]->setVelocity(v * VELOCITY);
  motor[middle_left_wheel]->setVelocity(v * VELOCITY);
  motor[back_left_wheel]->setVelocity(v * VELOCITY);
  motor[front_right_wheel]->setVelocity(v * VELOCITY);
  motor[middle_right_wheel]->setVelocity(v * VELOCITY);
  motor[back_right_wheel]->setVelocity(v * VELOCITY);
}

void Sojourner::turn_wheels_right() {
  motor[front_left_arm]->setPosition(0.4);
  motor[front_right_arm]->setPosition(0.227);
  motor[back_right_arm]->setPosition(-0.227);
  motor[back_left_arm]->setPosition(-0.4);
}

void Sojourner::turn_wheels_left() {
  motor[front_left_arm]->setPosition(-0.227);
  motor[front_right_arm]->setPosition(-0.4);
  motor[back_right_arm]->setPosition(0.4);
  motor[back_left_arm]->setPosition(0.227);
}

void Sojourner::wheels_straight() {
  motor[front_left_arm]->setPosition(0.0);
  motor[front_right_arm]->setPosition(0.0);
  motor[back_right_arm]->setPosition(0.0);
  motor[back_left_arm]->setPosition(0.0);
}

void Sojourner::turn_around(double v) {
  motor[front_left_arm]->setPosition(-0.87);
  motor[front_right_arm]->setPosition(0.87);
  motor[back_right_arm]->setPosition(-0.87);
  motor[back_left_arm]->setPosition(0.87);

  motor[front_left_wheel]->setVelocity(v * VELOCITY);
  motor[middle_left_wheel]->setVelocity(v * VELOCITY);
  motor[back_left_wheel]->setVelocity(v * VELOCITY);
  motor[front_right_wheel]->setVelocity(-v * VELOCITY);
  motor[middle_right_wheel]->setVelocity(-v * VELOCITY);
  motor[back_right_wheel]->setVelocity(-v * VELOCITY);

  motor[middle_right_wheel]->setAvailableTorque(0.0);
  motor[middle_left_wheel]->setAvailableTorque(0.0);
}

vector<double> Sojourner::getPosition() {
  vector<double> position(3);
  const double* gpsVal = gps->getValues();
  for (int i = 0; i < 3; i++) {
    position[i] = gpsVal[i];
  }
  return position;
}

vector<double> Sojourner::getOrientation() {
  vector<double> inertial(4);
  const double* inertialVal = orientation->getQuaternion();
  for (int i = 0; i < 4; i++) {
    inertial[i] = inertialVal[i];
  }
  return inertial;
}

double Sojourner::getLight() {
  return lightSensor->getValue();
}

int main() {
  // Required to initialize Webots
//  wb_robot_init();
  Sojourner rover;
  
   // Create an InOrbitSDK object
  inorbit::InOrbitSDK inorbit(INORBIT_HOST, INORBIT_PORT);
  
  cout << "Select the 3D window and use the keyboard to drive this robot:" << endl
       << "Q: forwards-left;  W: forwards;  E: forwards-right" << endl
       << "S: spin counter-clockwise" << endl 
       << "Y: backwards-left; X: backwards; C: backwards-right\n" << endl;
  
  Keyboard keyboard;
  keyboard.enable(TIME_STEP);

  // start moving
  rover.move_6_wheels(1.0);
  
  int count{0};
  while (rover.step(TIME_STEP) != -1) {
    int key = keyboard.getKey();
    count++;
    if (count > 60)
    {
      cout << "Battery: " << rover.batterySensorGetValue() << endl;
      auto p = rover.getPosition();
      cout << "Position: x:" << p[0] << " y:" << p[1] << " z:" << p[2] << endl;
      auto o = rover.getOrientation();
      cout << "Orientation: x:" <<  o[0] << " y:" << o[1] << " z:" << o[2] << " w:" << o[3] << endl;
      cout << "Light sensor: " << rover.getLight() << endl;
      cout << "\n" << endl;
      count = 0;
    }
    inorbit.sendKeyValue("Battery (J)", rover.batterySensorGetValue());
    inorbit.sendPose("map", rover.getPosition().data(), rover.getOrientation().data());
    inorbit.sendKeyValue("Incident light (W_m2)", rover.getLight());
    switch (key) {
      case 'W':
        // forwards
        rover.wheels_straight();
        rover.move_6_wheels(1.0);
        break;
      case 'X':
        // backwards
        rover.wheels_straight();
        rover.move_6_wheels(-1.0);
        break;
      case 'Q':
        // forwards left
        rover.turn_wheels_left();
        rover.move_4_wheels(1.0);
        break;
      case 'E':
        // forwards right
        rover.turn_wheels_right();
        rover.move_4_wheels(1.0);
        break;
      case 'Y':
        // backwards left
        rover.turn_wheels_left();
        rover.move_4_wheels(-1.0);
        break;
      case 'C':
        // backwards right
        rover.turn_wheels_right();
        rover.move_4_wheels(-1.0);
        break;
      case 'S':
        // spin counter-clockwise
        rover.turn_around(1.0);
        break;
    }
  }

  return 0;
}

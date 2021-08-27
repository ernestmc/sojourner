
# Sojourner simulation

This is a simple simulation of NASA's Sojourner Mars rover. The rover starts moving on its own over a simulated martian surface and can be controlled using the keyboard.

The simulation runs on the [Webots](https://www.cyberbotics.com/) simulation engine.

It is designed to work with [InOrbit](https://www.inorbit.ai/) so you will need to install the agent and have an active account. It uses the [C++ SDK](https://github.com/inorbit-ai/robot-sdk-cpp).

## Data produced by the simulation

The simulation generates the following data that is streamed to the InOrbit dashboard:

- Pose: the robot's current pose
- Battery: energy currently available in the robot's battery measured in joules.
- Incident light: amount of light received by the robot's solar panels measured in watts per square meters.

## Install Webots

Follow the procedure [described in Webots page](https://www.cyberbotics.com/doc/guide/installation-procedure#installing-the-debian-package-with-the-advanced-packaging-tool-apt) to install the simulator in your system using APT.

## Clone the repo

Clone this repo with the following instructions. Note that the repo contains git submodules that need to be installed.

```
git clone --recurse-submodules https://github.com/ernestmc/sojourner.git

```

## Run the simulation

The following commands will build and run the simulation.

```
cd sojourner
./run
```


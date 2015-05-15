#ifndef INTERFACE_HPP
#define INTERFACE_HPP



#include "globals.hpp"
#include "scene.hpp"

Scene initilizeSimulator();

void runSimulator(Scene scene, double *x, double *x_dot, double *theta, double *theta_dot);

int checkForFall(void);

void closeSimulator();



#endif
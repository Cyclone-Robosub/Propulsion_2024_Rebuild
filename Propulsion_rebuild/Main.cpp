#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "Thruster_Commander.h"
#include "eigen-3.4.0/Eigen/Dense"



int main() {


	Thruster_Commander Thruster = Thruster_Commander();
	Thruster.print_info();
	return 0;
}
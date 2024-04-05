#ifndef PHYSICS_H
#define PHYSICS_H

#include "vendors/glad/glad.h"
#include "vendors/GLFW/glfw3.h"
#include "vendors/glm/glm.hpp"
#include "vendors/glm/gtc/matrix_transform.hpp"
#include "vendors/glm/gtc/type_ptr.hpp"

#include <iostream>

#define DEBUG std::cout << "DEBUG" << std::endl;

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 800;

const unsigned int pixPerMeter = 10;

const unsigned int SCRADJUST = SCREEN_WIDTH / pixPerMeter;


#endif
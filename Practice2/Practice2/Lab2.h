#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <gl/gl.h>
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>

using namespace std;

const float PI = 3.141592653589793;
const float speed = 10.0f;

class Point
{
private:
   double x, y, z;
public:
   Point(double _x = 0, double _y = 0, double _z = 0) {
      x = _x; y = _y; z = _z;
   }
};
Point* p;

int light = Spotlight;
float angle_tiraj, angle_x = 0.0f, angle_y = 0.0f;
float rotateMatrix[3][3];

bool isSmoothNorm = true, 
     isCarcass = false,
     isPerspective = true, 
     isTextured = true, 
     isShownGrid = true;
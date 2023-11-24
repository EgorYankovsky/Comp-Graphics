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

enum rotateAxis
{
   rotateY, rotateX
};

enum MoveMenuFrags
{
   Up,
   Left,
   Down,
   Right
};


struct Point
{
   double x, y, z;
   Point(double _x = 0, double _y = 0, double _z = 0) {
      x = _x; y = _y; z = _z;
   }
};
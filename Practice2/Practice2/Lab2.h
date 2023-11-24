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

bool isSmoothNorm = true, 
     isCarcass = false,
     isPerspective = true, 
     isTextured = true, 
     forward, 
     isShownGrid = true;

enum rotateAxis
{
   rotateY, rotateX
};

enum MoveMenuFrags
{
   Up,
   Left,
   Down,
   Right,
   Forward,
   Backward
};

enum LightingMode
{
   Directed = 1,
   Dot1,
   Dot2,
   SpotlightSmallAngle,
   Spotlight,
   NoLight
};

struct Point
{
   double x, y, z;
   Point(double _x = 0, double _y = 0, double _z = 0) {
      x = _x; y = _y; z = _z;
   }
};
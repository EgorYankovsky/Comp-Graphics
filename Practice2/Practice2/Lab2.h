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
public:
   double x = 0,
          y = 0,
          z = 0;

   Point() {}

   Point (double _x, double _y, double _z) 
   {
      x = _x; y = _y; z = _z;
   }
};


class Vector
{
public:
   double x, y, z;

   Vector()
   {
      x = 0; y = 0; z = 0;
   }

   Vector(Point a, Point b)
   {
      x = b.x - a.x;
      y = b.y - a.y;
      z = b.z - a.z;
   }

   void ConvertToVector(Point *p)
   {
      x = p->x;
      y = p->y;
      z = p->z;
   }

   // Конструктор вектора.
   Vector(double x, double y, double z)
   {
      this->x = x;
      this->y = y;
      this->z = z;
   }

   // Нормализация вектора.
   void Normalise()
   {
      double sum = 0;
      sum = sqrt(x * x + y * y + z * z);
      x /= sum;
      y /= sum;
      z /= sum;
   }
};
Vector* p;

struct Figure
{
   vector<Point> Points;
};


int light;
float angle_tiraj, angle_x = 0.0f, angle_y = 0.0f;
float rotateMatrix[3][3];
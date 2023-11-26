#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <gl/gl.h>
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Flags.h"

using namespace std;

const float PI = 3.141592653589793;
const float speed = 10.0f;

int light = Spotlight;
float angle_tiraj, angle_x = 0.0f, angle_y = 0.0f;
float rotateMatrix[3][3];
vector<int> Direction;
vector<float> TexCord = { 0.0f, 0.0f, 1.0f, 0.0f,
                          1.0f, 1.0f, 0.0f, 1.0f };
GLint Width, Height;
int texWidth, texHeight;
GLuint type, tex[2];
unsigned char* pixels;
unsigned char* pixels1;

class Point
{
public:
   double x = 0,
          y = 0,
          z = 0;

   Point() {}

   Point (double x, double y, double z) 
   {
      this->x = x;
      this->y = y;
      this->z = z;
   }
};


class Vector
{
public:
   double x, y, z;

   Vector()
   {
      x = 1; y = 0; z = 0;
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

class Lantern
{
private:
   double xBLen = 2;
   double yBLen = 2;
   double xFLen = 5;
   double yFLen = 5;
   double zLen = 2.5;
public:

   vector<Figure> Sides;

   Point LookFromPosition;

   Vector LookDirection;

   Lantern()
   {
      LookFromPosition = Point(0.0, 0.0, 0.0);
      LookDirection = Vector(1.0, 0.0, 0.0);
   }

   Lantern(Point point, Vector vector)
   {
      LookFromPosition = point;
      LookDirection = vector;
   }

   void BuildLantern(GLfloat lightPosition[], GLfloat lightDirection[])
   {
      Sides.push_back(Figure());
      Sides[0].Points.push_back(Point(lightPosition[0] - xBLen, lightPosition[1] - yBLen, lightPosition[2] - zLen));
      Sides[0].Points.push_back(Point(lightPosition[0] - xBLen, lightPosition[1] + yBLen, lightPosition[2] - zLen));
      Sides[0].Points.push_back(Point(lightPosition[0] + xBLen, lightPosition[1] - yBLen, lightPosition[2] - zLen));
      Sides[0].Points.push_back(Point(lightPosition[0] + xBLen, lightPosition[1] + yBLen, lightPosition[2] - zLen));

      Sides.push_back(Figure());
      Sides[1].Points.push_back(Point(lightPosition[0] - xFLen, lightPosition[1] - yFLen, lightPosition[2] + zLen));
      Sides[1].Points.push_back(Point(lightPosition[0] - xFLen, lightPosition[1] + yFLen, lightPosition[2] + zLen));
      Sides[1].Points.push_back(Point(lightPosition[0] + xFLen, lightPosition[1] - yFLen, lightPosition[2] + zLen));
      Sides[1].Points.push_back(Point(lightPosition[0] + xFLen, lightPosition[1] + yFLen, lightPosition[2] + zLen));

      for (int i = 0; i < 4; i++)
      {
         Sides.push_back(Figure());
         Sides[i + 2].Points.push_back(Point(Sides[0].Points[i].x, Sides[0].Points[i].y, Sides[0].Points[i].z));
         Sides[i + 2].Points.push_back(Point(Sides[0].Points[(i + 1) % 4].x, Sides[0].Points[(i + 1) % 4].y, Sides[0].Points[(i + 1) % 4].z));
         Sides[i + 2].Points.push_back(Point(Sides[1].Points[(i + 1) % 4].x, Sides[1].Points[(i + 1) % 4].y, Sides[1].Points[(i + 1) % 4].z));
         Sides[i + 2].Points.push_back(Point(Sides[1].Points[i].x, Sides[1].Points[i].y, Sides[1].Points[i].z));
      }
   }

   void PrintLantern()
   {
      glColor4ub(255, 255, 255, 0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glBegin(GL_POLYGON);
      for (int i = 0; i < 6; i++)
         for (int j = 0; j < 4; j++)
            glVertex3f(Sides[i].Points[j].x, Sides[i].Points[j].y, Sides[i].Points[j].z);
      glEnd();
   }
};


Point pos;
Vector strafe, view, up = { 0.0f, 1.0f, 0.0f };
vector<Figure> Figures;
vector<Vector> Normals;
vector<Vector> SmoothedNormals;
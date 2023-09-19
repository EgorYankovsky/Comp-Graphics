#pragma once
#include <vector>
#include <iostream>
#include "glut.h"

using namespace std;

#define BLACK        0  //   0   0   0
#define NAVY         1  //   0   0 127
#define BLUE         2  //   0   0 255
#define GREEN        3  //   0 128   0
#define TEAL         4  //   0 128 128
#define LIME         5  //   0 255   0
#define SPRINGGREEN  6  //   0 255 127
#define AQUA         7  //   0 255 255
#define MAROON       8  // 128   0   0
#define PURPLE       9  // 128   0 128
#define OLIVE       10  // 128 128   0
#define GRAY        11  // 128 128 128
#define CHARTREUSE  12  // 127 255   0
#define RED         13  // 255   0   0
#define FUCHSIA     14  // 255   0 255
#define ORANGE      15  // 255 165   0
#define YELLOW      16  // 255 255   0
#define WHITE       17  // 255 255 255

#define CLOCKWISE        0
#define COUNTERCLOCKWISE 1

#define MOVENEXT 0
#define MOVEPREV 1

GLint WINDOW_WIDTH = 1024;
GLint WINDOW_HEIGTH = 512;
const GLubyte ACTIVE_GROUP_OPACITY = 255;
const GLubyte DEFAULT_GROUP_OPACITY = 100;

GLuint activeGroupIndex = -1;

class Color
{
public:
   GLubyte R;
   GLubyte G;
   GLubyte B;

   Color(GLubyte R, GLubyte G, GLubyte B) {
      this->R = R;
      this->G = G;
      this->B = B;
   }

   Color() {
      this->R = 255;
      this->G = 0;
      this->B = 0;
   }
};

struct Point
{
   GLint x, y;

   Point(GLint x, GLint y) {
      this->x = x;
      this->y = y;
   }
};

class Group
{
public:
   int x_mid, y_mid;
   vector<Point> points = {};
   Color color;

   int Size() {
      return points.size();
   }

   void addNewPoint(Point p) {
      points.push_back(p);
   }

   bool removeLastPoint() {
      if (points.size() > 0) {
         points.pop_back();
         return true;
      }
      else {
         return false;
      }
   }

   void countMidPoints()
   {
      x_mid = 0;
      y_mid = 0;
      for (Point p : points) {
         x_mid += p.x;
         y_mid += p.y;
      }
      x_mid /= points.size();
      y_mid /= points.size();
   }
};
vector<Group> groups {};

void Rotate(Group* gr)
{
   for (Point& p : gr->points)
      p = Point(gr->x_mid + gr->y_mid - p.y,
         -1 * gr->x_mid + gr->y_mid + p.x);
}

void BackRotate(Group* gr)
{
   for (Point& p : gr->points)
      p = Point(gr->x_mid - gr->y_mid + p.y,
         gr->x_mid + gr->y_mid - p.x);
}

void Delete(int a)
{
   switch (a)
   {
   case 0:
      if (groups.size() > 0) {
         groups.erase(groups.begin() + activeGroupIndex);
         activeGroupIndex--;
      }
      break;
   case 1:
      if (groups[activeGroupIndex].points.size() == 0) {
         cerr << "Group is empty" << endl;
      }
      else {
         groups[activeGroupIndex].points.pop_back();
      }
      break;
   }
   glutPostRedisplay();
}

void MoveNext()
{
   if (activeGroupIndex == groups.size() - 1)
      activeGroupIndex = 0;
   else
      activeGroupIndex++;
   glutPostRedisplay();
}

void MovePrev()
{
   if (activeGroupIndex == 0)
      activeGroupIndex = groups.size() - 1;
   else
      activeGroupIndex--;
   glutPostRedisplay();
}
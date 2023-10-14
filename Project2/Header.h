#pragma once

#pragma comment (linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") 
#pragma comment (lib, "glut32.lib")

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

#define SELECTNEXT 0
#define SELECTPREV 1

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

const double sin15 = 0.2588190451025208;
const double cos15 = 0.9659258262890683;

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
      this->G = 255;
      this->B = 255;
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
   int pointsAmount;
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
      pointsAmount = 0;
      x_mid = 0;
      y_mid = 0;
      for (Point p : points) {
         x_mid += p.x;
         y_mid += p.y;
         pointsAmount++;
      }
      x_mid /= points.size();
      y_mid /= points.size();
   }
};
vector<Group> groups{};

void Move(Group* gr, int a)
{
   switch (a)
   {
   case UP:
      for (Point& point : gr->points)
         point.y += 9;
      break;
   case DOWN:
      for (Point& point : gr->points)
         point.y -= 9;
      break;
   case LEFT:
      for (Point& point : gr->points)
         point.x -= 9;
      break;
   case RIGHT:
      for (Point& point : gr->points)
         point.x += 9;
      break;
   }
   glutPostRedisplay();
}

void Rotate(Group* gr)
{
   for (Point& p : gr->points)
      p = Point(cos15 * (p.x - gr->x_mid) - sin15 * (p.y - gr->y_mid) + gr->x_mid,
         cos15 * (p.y - gr->y_mid) + sin15 * (p.x - gr->x_mid) + gr->y_mid);
}

void BackRotate(Group* gr)
{
   for (Point& p : gr->points)
      p = Point(cos15 * (p.x - gr->x_mid) + sin15 * (p.y - gr->y_mid) + gr->x_mid,
         cos15 * (p.y - gr->y_mid) - sin15 * (p.x - gr->x_mid) + gr->y_mid);
}

void Delete(int a)
{
   switch (a)
   {
   case 0:
      if (groups.size() > 0) {
         groups.erase(groups.begin() + activeGroupIndex);
         if (activeGroupIndex == 0)
            activeGroupIndex = groups.size() - 1;
         else 
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

void SelectNext()
{
   if (activeGroupIndex == groups.size() - 1)
      activeGroupIndex = 0;
   else
      activeGroupIndex++;
   glutPostRedisplay();
}

void SelectPrev()
{
   if (activeGroupIndex == 0)
      activeGroupIndex = groups.size() - 1;
   else
      activeGroupIndex--;
   glutPostRedisplay();
}

void CreateGroup()
{
   for (Group gr : groups)
      if (gr.Size() == 0)
         return;
   groups.push_back(Group{});
   activeGroupIndex = groups.size() - 1;
}

void Increase(Group* gr)
{
   for (Point& p : gr->points)
      p = Point(p.x + 0.2 * (p.x - gr->x_mid), p.y + 0.2 * (p.y - gr->y_mid));
}

void Reduce(Group* gr)
{
   for (Point& p : gr->points)
      p = Point(p.x - 0.2 * (p.x - gr->x_mid), p.y - 0.2 * (p.y - gr->y_mid));
}
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

GLint Width = 1024, Height = 512;
int CurrentGroupIndex = 0;

struct type_point
{
   GLint x, y;
   type_point(GLint _x, GLint _y) { x = _x; y = _y; }
};

vector <type_point> Points;
vector <int> Refs{ 0 };
vector <vector<int>> ColorGroups{ {255, 0, 0} };
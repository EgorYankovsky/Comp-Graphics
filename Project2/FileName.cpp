#include "Header.h"

/*
   1) изменение не только координат и цвета вершин примитивов, но
      и режимов сглаживания, шаблона закрашивания примитива, …;
   2) изменение параметров (в том числе и удаление) не только текущего набора примитивов, но и произвольного.
   3) изменение параметров произвольного примитива в наборе.
*/


void Display(void)
{
   int pointSize = 6;
   glClearColor(1, 1, 1, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glEnable(GL_BLEND);

   for (int i = 0; i < groups.size(); i++) {
      if (i == activeGroupIndex) {
         glPointSize(pointSize + 10);
         glEnable(GL_POINT_SMOOTH);
      }
      else {
         glPointSize(pointSize);
         glDisable(GL_POINT_SMOOTH);
      }
      
      glBegin(GL_POLYGON);
      for (Point point : groups[i].points) {
         glColor4ub(groups[i].color.R, groups[i].color.G, groups[i].color.B, DEFAULT_GROUP_OPACITY);
         glVertex2i(point.x, point.y);
      }
      glEnd();

      glLineWidth(3);
      glBegin(GL_LINE_LOOP);
      for (Point point : groups[i].points) {
         glColor4ub(0, 0, 0, DEFAULT_GROUP_OPACITY);
         glVertex2i(point.x, point.y);
      }
      glEnd();

      glBegin(GL_POINTS);
      for (Point point : groups[i].points) {
         glColor4ub(0, 0, 0, DEFAULT_GROUP_OPACITY);
         glVertex2i(point.x, point.y);
      }
      glEnd();
   }
   glFinish();
}

void Reshape(GLint w, GLint h)
{
   WINDOW_WIDTH = w; WINDOW_HEIGTH = h;
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, w, 0, h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
   if (key == '\r') {
      CreateGroup();
   }

   if (activeGroupIndex == -1) {
      return;
   }

   Group* activeGroup = &groups[activeGroupIndex];
   if (activeGroup->Size() != 0 && activeGroup->points.size() != activeGroup->pointsAmount)
      activeGroup->countMidPoints();

   switch (key) {
   case 't':
      Rotate(activeGroup);
      break;
   case 'T':
      BackRotate(activeGroup);
      break;

   case '+':
      Increase(activeGroup);
      break;

   case '-':
      Reduce(activeGroup);
      break;

   case 'r':
      activeGroup->color.R += 5;
      break;
   case 'R':
      activeGroup->color.R -= 5;
      break;

   case 'g':
      activeGroup->color.G += 5;
      break;
   case 'G':
      activeGroup->color.G -= 5;
      break;

   case 'b':
      activeGroup->color.B += 5;
      break;
   case 'B':
      activeGroup->color.B -= 5;
      break;

   case 'w':
      Move(activeGroup, UP);
      break;
   case 's':
      Move(activeGroup, DOWN);
      break;
   case 'a':
      Move(activeGroup, LEFT);
      break;
   case 'd':
      Move(activeGroup, RIGHT);
      break;

   case '<':
      SelectPrev();
      break;

   case '>':
      SelectNext();
      break;

   case 127:
      Delete(0);
      break;

   case '\b':
   case 26:
      Delete(1);
      break;
   }
   glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
   if (state != GLUT_DOWN) return;

   if (button == GLUT_LEFT_BUTTON)
   {
      if (groups.size() > 0) {
         groups[activeGroupIndex].points.push_back(Point{ x, WINDOW_HEIGTH - y });
      }
   }
   glutPostRedisplay();
}

void MainMenu(int a)
{
   switch (a)
   {
   case -1:
      CreateGroup();
      break;
   case 0:
      Delete(0);
      break;
   case 1:
      Delete(1);
      break;
   }
   glutPostRedisplay();
}

void ColorMenu(int switcher)
{
   Group* activeGroup = &groups[activeGroupIndex];
   switch (switcher)
   {
   case BLACK:
      activeGroup->color.R = 0;
      activeGroup->color.G = 0;
      activeGroup->color.B = 0;
      break;
   case NAVY:
      activeGroup->color.R = 0;
      activeGroup->color.G = 0;
      activeGroup->color.B = 127;
      break;
   case BLUE:
      activeGroup->color.R = 0;
      activeGroup->color.G = 0;
      activeGroup->color.B = 255;
      break;
   case GREEN:
      activeGroup->color.R = 0;
      activeGroup->color.G = 128;
      activeGroup->color.B = 0;
      break;
   case TEAL:
      activeGroup->color.R = 0;
      activeGroup->color.G = 128;
      activeGroup->color.B = 128;
      break;
   case LIME:
      activeGroup->color.R = 0;
      activeGroup->color.G = 255;
      activeGroup->color.B = 0;
      break;
   case SPRINGGREEN:
      activeGroup->color.R = 0;
      activeGroup->color.G = 255;
      activeGroup->color.B = 127;
      break;
   case AQUA:
      activeGroup->color.R = 0;
      activeGroup->color.G = 255;
      activeGroup->color.B = 255;
      break;
   case MAROON:
      activeGroup->color.R = 128;
      activeGroup->color.G = 0;
      activeGroup->color.B = 0;
      break;
   case PURPLE:
      activeGroup->color.R = 128;
      activeGroup->color.G = 0;
      activeGroup->color.B = 128;
      break;
   case OLIVE:
      activeGroup->color.R = 128;
      activeGroup->color.G = 128;
      activeGroup->color.B = 0;
      break;
   case GRAY:
      activeGroup->color.R = 128;
      activeGroup->color.G = 128;
      activeGroup->color.B = 128;
      break;
   case CHARTREUSE:
      activeGroup->color.R = 127;
      activeGroup->color.G = 255;
      activeGroup->color.B = 0;
      break;
   case RED:
      activeGroup->color.R = 255;
      activeGroup->color.G = 0;
      activeGroup->color.B = 0;
      break;
   case FUCHSIA:
      activeGroup->color.R = 255;
      activeGroup->color.G = 0;
      activeGroup->color.B = 255;
      break;
   case ORANGE:
      activeGroup->color.R = 255;
      activeGroup->color.G = 165;
      activeGroup->color.B = 0;
      break;
   case YELLOW:
      activeGroup->color.R = 255;
      activeGroup->color.G = 255;
      activeGroup->color.B = 0;
      break;
   case WHITE:
      activeGroup->color.R = 255;
      activeGroup->color.G = 255;
      activeGroup->color.B = 255;
      break;
   }
   glutPostRedisplay();
}

void RotateMenu(int switcher)
{
   Group* activeGroup = &groups[activeGroupIndex];
   if (activeGroup->Size() != 0 && activeGroup->points.size() != activeGroup->pointsAmount)
      activeGroup->countMidPoints();
   switch (switcher)
   {
   case CLOCKWISE:
      Rotate(activeGroup);
      break;
   case COUNTERCLOCKWISE:
      BackRotate(activeGroup);
      break;
   }
   glutPostRedisplay();
}

void SelectMenu(int switcher)
{
   switch (switcher)
   {
   case SELECTNEXT:
      SelectNext();
      break;
   case SELECTPREV:
      SelectPrev();
      break;
   }
}

void MoveMenu(int switcher)
{
   Group* activeGroup = &groups[activeGroupIndex];
   Move(activeGroup, switcher);
}

void ZoomMenu(int switcher)
{
   Group* activeGroup = &groups[activeGroupIndex];
   if (activeGroup->Size() != 0 && activeGroup->points.size() != activeGroup->pointsAmount)
      activeGroup->countMidPoints();
   switch (switcher)
   {
   case 0:
      Increase(activeGroup);
      break;
   case 1:
      Reduce(activeGroup);
      break;
   }
   glutPostRedisplay();
}

void ShowMenu()
{
   int CM = glutCreateMenu(ColorMenu);
   glutAddMenuEntry("Black", BLACK);
   glutAddMenuEntry("Navy", NAVY);
   glutAddMenuEntry("Blue", BLUE);
   glutAddMenuEntry("Green", GREEN);
   glutAddMenuEntry("Teal", TEAL);
   glutAddMenuEntry("Lime", LIME);
   glutAddMenuEntry("Spring green", SPRINGGREEN);
   glutAddMenuEntry("Aqua", AQUA);
   glutAddMenuEntry("Maroon", MAROON);
   glutAddMenuEntry("Purple", PURPLE);
   glutAddMenuEntry("Olive", OLIVE);
   glutAddMenuEntry("Gray", GRAY);
   glutAddMenuEntry("Chartreuse", CHARTREUSE);
   glutAddMenuEntry("Red", RED);
   glutAddMenuEntry("Fuchsia", FUCHSIA);
   glutAddMenuEntry("Orange", ORANGE);
   glutAddMenuEntry("Yellow", YELLOW);
   glutAddMenuEntry("White", WHITE);

   int RM = glutCreateMenu(RotateMenu);
   glutAddMenuEntry("Clockwise", CLOCKWISE);
   glutAddMenuEntry("Counterclockwise", COUNTERCLOCKWISE);

   int SM = glutCreateMenu(SelectMenu);
   glutAddMenuEntry("Select previous", SELECTPREV);
   glutAddMenuEntry("Select next", SELECTNEXT);

   int MvM = glutCreateMenu(MoveMenu);
   glutAddMenuEntry("Up", UP);
   glutAddMenuEntry("Down", DOWN);
   glutAddMenuEntry("Left", LEFT);
   glutAddMenuEntry("Right", RIGHT);

   int ZM = glutCreateMenu(ZoomMenu);
   glutAddMenuEntry("Increase", 0);
   glutAddMenuEntry("Reduce", 1);

   int MM = glutCreateMenu(MainMenu);
   glutAddSubMenu("Color", CM);
   glutAddSubMenu("Rotate", RM);
   glutAddSubMenu("Select", SM);
   glutAddSubMenu("Move", MvM);
   glutAddSubMenu("Zoom", ZM);
   glutAddMenuEntry("Push back group", -1);
   glutAddMenuEntry("Delete group", 0);
   glutAddMenuEntry("Delete last primitive", 1);

   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main(int argc, char* argv[])
{
   if (groups.empty()) {
      groups.push_back(Group{});
      activeGroupIndex = 0;
   }
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB);
   glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
   glutCreateWindow("LR 1. Salyaev Yankovskij");
   ShowMenu();
   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Keyboard);
   glutMouseFunc(Mouse);

   glutMainLoop();
}
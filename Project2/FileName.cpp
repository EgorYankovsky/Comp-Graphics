#include "Header.h"

/* Функция вывода на экран */
void Display(void)
{
   int pointSize = 16;
   glClearColor(1, 1, 1, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   glEnable(GL_POINT_SMOOTH);
   glEnable(GL_BLEND);

   for (int i = 0; i < groups.size(); i++) {
      if (i == activeGroupIndex) {
         glPointSize(pointSize + 10);
         glColor4ub(groups[i].color.R, groups[i].color.G, groups[i].color.B, ACTIVE_GROUP_OPACITY);
      }
      else {
         glPointSize(pointSize);
         glColor4ub(groups[i].color.R, groups[i].color.G, groups[i].color.B, DEFAULT_GROUP_OPACITY);
      }
      glBegin(GL_POINTS);
      for (Point point : groups[i].points) {
         glVertex2i(point.x, point.y);
      }
      glEnd();
   }
   glFinish();
}

/* Функция изменения размеров окна */
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

/* Функция обработки сообщений от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
   if (key == '\r' && !groups.back().points.empty()) {
      groups.push_back(Group{});
      activeGroupIndex = groups.size() - 1;
   }

   if (activeGroupIndex == -1) {
      return;
   }

   Group* activeGroup = &groups[activeGroupIndex];
   if (activeGroup->Size() != 0)
      activeGroup->countMidPoints();

   switch (key) {
   /* Поворот против часовой стрелки */
   case 't':
      Rotate(activeGroup);
      break;
   /* Поворот по часовой стрелке */
   case 'T':
      BackRotate(activeGroup);
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

      /* Изменение XY-кординат точек */
   case 'w':
      for (Point& point : activeGroup->points) {
         point.y += 9;
      }
      break;
   case 's':
      for (Point& point : activeGroup->points) {
         point.y -= 9;
      }
      break;
   case 'a':
      for (Point& point : activeGroup->points) {
         point.x -= 9;
      }
      break;
   case 'd':
      for (Point& point : activeGroup->points) 
         point.x += 9;
      break;

      /* Выбор предыдущей группы */
   case '<':
      MovePrev();
      break;

      /* Выбор следующей группы */
   case '>':
      MoveNext();
      break;

   /* Удаление */
   case 127: 
      Delete(0); 
      break;

   case '\b': 
      Delete(1); 
      break;
   }
   glutPostRedisplay();
}

/* Функция обработки сообщения от мыши */
void Mouse(int button, int state, int x, int y)
{
   /* клавиша была нажата, но не отпущена */
   if (state != GLUT_DOWN) return;

   /* новая точка по левому клику */
   if (button == GLUT_LEFT_BUTTON)
   {
      if (groups.size() > 0) {
         groups[activeGroupIndex].points.push_back(Point{ x, WINDOW_HEIGTH - y });
      }
   }
   glutPostRedisplay();
}

void MainMenu(int a) {}

void ColorMenu(int switcher)
{
   Group* activeGroup = &groups[activeGroupIndex];
   switch (switcher)
   {
   case BLACK:
   {
      activeGroup->color.R = 0;
      activeGroup->color.G = 0;
      activeGroup->color.B = 0;
      break;
   }
   case NAVY:
   {
      activeGroup->color.R = 0;
      activeGroup->color.G = 0;
      activeGroup->color.B = 127;
      break;
   }
   case BLUE:
   {
      activeGroup->color.R = 0;
      activeGroup->color.G = 0;
      activeGroup->color.B = 255;
      break;
   }
   case GREEN:
   {
      activeGroup->color.R = 0;
      activeGroup->color.G = 128;
      activeGroup->color.B = 0;
      break;
   }
   case TEAL:
   {
      activeGroup->color.R = 0;
      activeGroup->color.G = 128;
      activeGroup->color.B = 128;
      break;
   }
   case LIME:
   {
      activeGroup->color.R = 0;
      activeGroup->color.G = 255;
      activeGroup->color.B = 0;
      break;
   }
   case SPRINGGREEN:
   {
      activeGroup->color.R = 0;
      activeGroup->color.G = 255;
      activeGroup->color.B = 127;
      break;
   }
   case AQUA:
   {
      activeGroup->color.R = 0;
      activeGroup->color.G = 255;
      activeGroup->color.B = 255;
      break;
   }
   case MAROON:
   {
      activeGroup->color.R = 128;
      activeGroup->color.G = 0;
      activeGroup->color.B = 0;
      break;
   }
   case PURPLE:
   {
      activeGroup->color.R = 128;
      activeGroup->color.G = 0;
      activeGroup->color.B = 128;
      break;
   }
   case OLIVE:
   {
      activeGroup->color.R = 128;
      activeGroup->color.G = 128;
      activeGroup->color.B = 0;
      break;
   }
   case GRAY:
   {
      activeGroup->color.R = 128;
      activeGroup->color.G = 128;
      activeGroup->color.B = 128;
      break;
   }
   case CHARTREUSE:
   {
      activeGroup->color.R = 127;
      activeGroup->color.G = 255;
      activeGroup->color.B = 0;
      break;
   }
   case RED:
   {
      activeGroup->color.R = 255;
      activeGroup->color.G = 0;
      activeGroup->color.B = 0;
      break;
   }
   case FUCHSIA:
   {
      activeGroup->color.R = 255;
      activeGroup->color.G = 0;
      activeGroup->color.B = 255;
      break;
   }
   case ORANGE:
   {
      activeGroup->color.R = 255;
      activeGroup->color.G = 165;
      activeGroup->color.B = 0;
      break;
   }
   case YELLOW:
   {
      activeGroup->color.R = 255;
      activeGroup->color.G = 255;
      activeGroup->color.B = 0;
      break;
   }
   case WHITE:
   {
      activeGroup->color.R = 255;
      activeGroup->color.G = 255;
      activeGroup->color.B = 255;
      break;
   }
   }
   glutPostRedisplay();
}

void RotateMenu(int switcher)
{
   Group* activeGroup = &groups[activeGroupIndex];
   if (activeGroup->Size() != 0)
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

void MoveMenu(int switcher)
{
   switch (switcher)
   {
   case MOVENEXT:
      MoveNext();
      break;
   case MOVEPREV:
      MovePrev();
      break;
   }
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

   int DM = glutCreateMenu(Delete);
   glutAddMenuEntry("Delete group", 0);
   glutAddMenuEntry("Delete last item", 1);

   int MvM = glutCreateMenu(MoveMenu);
   glutAddMenuEntry("Move previous", MOVEPREV);
   glutAddMenuEntry("Move next", MOVENEXT);

   int MM = glutCreateMenu(MainMenu);
   glutAddSubMenu("Color menu", CM);
   glutAddSubMenu("Rotate menu", RM);
   glutAddSubMenu("Delete", DM);
   glutAddSubMenu("Move", MvM);

   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* Головная программа */
void main(int argc, char* argv[])
{
   if (groups.empty()){
      groups.push_back(Group{});
      activeGroupIndex = groups.size() - 1;
   }
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB);
   glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
   glutCreateWindow("ЛР 1. Саляев Янковский");
   ShowMenu();
   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Keyboard);
   glutMouseFunc(Mouse);

   /* Функция, запускающая бесконечный цикл для работы с графическими объектами. */
   glutMainLoop();
}
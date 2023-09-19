#include "Header.h"

/*
   TODO:
      
      1. (+) ���������� � ���� ��������� ���������� (������� ������� �������� ������� ����) � ������������ � ��������� �������.
      
      2. (+) ��� ���������� �������� (���������) ������ (���������) ���������� � ������ ������ ��������������� ����������� ������� (������ ��� ������ ����).
      
      3. (+) ��� �������� ������ ���������� ������������ ����������� ��������� ����� � ��������� ��� ������.
      
      4. (+) ������� ��������� ���������� �������� ����� ������, ��������, ���������� ������� ��� ������ �������� glPointSize(*).
      
      5. (+) ������������ ��������� vector �� ���������� STL ��� �������� ������ ���������� � ��������� ������ ������� ���������,
         � ��� �������� ��������� ������������� ������������ ����������� ����� struct.
      
      6. (+) ������������� ����������� �������� ���������� ��������� � ���������� ������ ����������.
      
      7. �������������� ������� � ����, ��������� � ������� ���������� GLUT.
*/

/* ������� ������ �� ����� */
void Display(void)
{
   int pointSize = 16;
   glClearColor(1, 1, 1, 0);
   glClear(GL_COLOR_BUFFER_BIT);

   // ���������� �����
   glPointSize(pointSize);
   glEnable(GL_POINT_SMOOTH);
   glBegin(GL_POINTS);
   
   for (int ii = 0; ii < Refs.size() - 1; ii++)
   {
      for (int i = Refs[ii]; i < Refs[ii + 1]; i++)
      {
         glColor3ub(ColorGroups[ii][0],
                    ColorGroups[ii][1],
                    ColorGroups[ii][2]);

         glVertex2i(Points[i].x, Points[i].y);
      }
   }
   glEnd();
   glFinish();

   // ������� �����
   glPointSize(pointSize + 10);
   glEnable(GL_POINT_SMOOTH);
   glBegin(GL_POINTS);

   for (int i = Refs.back(); i < Points.size(); i++)
   {
      glColor3ub(ColorGroups[ColorGroups.size() - 1][0],
                 ColorGroups[ColorGroups.size() - 1][1],
                 ColorGroups[ColorGroups.size() - 1][2]);
      glVertex2i(Points[i].x, Points[i].y);
   }
   glEnd();
   glFinish();
}

/* ������� ��������� �������� ���� */
void Reshape(GLint w, GLint h)
{
   Width = w; Height = h;
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, w, 0, h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/* ������� ��������� ��������� �� ���������� */
void Keyboard(unsigned char key, int x, int y)
{
   int i, n = Points.size();

   if (key == '<')
   {
      /* ���������� ������ */
   }
   if (key == '>')
   {
      /* ��������� ������ */
   }


   /* ��������� RGB-��������� ����� ����� */
   if (key == 'r') ColorGroups[ColorGroups.size() - 1][0] += 5;
   if (key == 'R') ColorGroups[ColorGroups.size() - 1][0] -= 5;

   if (key == 'g') ColorGroups[ColorGroups.size() - 1][1] += 5;
   if (key == 'G') ColorGroups[ColorGroups.size() - 1][1] -= 5;

   if (key == 'b') ColorGroups[ColorGroups.size() - 1][2] += 5;
   if (key == 'B') ColorGroups[ColorGroups.size() - 1][2] -= 5;
   
   /* ��������� XY-�������� ����� */
   if (key == 'w') for (i = Refs.back(); i < n; i++) Points[i].y += 9;
   if (key == 's') for (i = Refs.back(); i < n; i++) Points[i].y -= 9;
   if (key == 'a') for (i = Refs.back(); i < n; i++) Points[i].x -= 9;
   if (key == 'd') for (i = Refs.back(); i < n; i++) Points[i].x += 9;

   /* �������� ����� ������ ����� �� Enter */
   if (key == '\r')
   {
      /* ��������� ������ � ��� ������, ���� ������ �� ������ */
      if (Points.size() != Refs.back())
      {
         Refs.push_back(Points.size());
         ColorGroups.push_back(vector<int> {255, 0, 0});
         CurrentGroupIndex++;
      }
   }

   /* �������� ����� �� backspace */
   if (key == '\b')
   {
      if (Points.size() == 0) cerr << "Points is empty" << endl;
      else if (Points.size() == Refs.back())
      {
         Refs.pop_back();
         ColorGroups.pop_back();
         CurrentGroupIndex--;
      }
      else
      {
         Points.pop_back();
         if (Points.size() < Refs.back())
         {
            Refs.pop_back();
            ColorGroups.pop_back();
            CurrentGroupIndex--;
         }
      }
   }

   /* �������� ���� ������ ����� */
   if (key == 127)
   {
      int last = Points.size() - 1;
      for (int i = last; i >= Refs.back(); i--) Points.pop_back();
   }

   glutPostRedisplay();
}

/* ������� ��������� ��������� �� ���� */
void Mouse(int button, int state, int x, int y)
{
   /* ������� ���� ������, �� �� �������� */
   if (state != GLUT_DOWN) return;

   /* ����� ����� �� ������ ����� */
   if (button == GLUT_LEFT_BUTTON)
   {
      if (Points.size() > 0) Points.push_back(type_point(x, Height - y));
      if (Points.size() == 0)
      {
         Points = { type_point(x, Height - y) };
         Refs = { 0 };
      }
   }
   glutPostRedisplay();
}

/* �������� ������� ��� ���� */
void processMainMenu(int a) {}

/* �������� ���� */
void ColorMenu(int switcher)
{
   switch (switcher)
   {
   case BLACK:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 0;
      ColorGroups[ColorGroups.size() - 1][1] = 0;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case NAVY:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 0;
      ColorGroups[ColorGroups.size() - 1][1] = 0;
      ColorGroups[ColorGroups.size() - 1][2] = 127;
      return;
   }
   case BLUE:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 0;
      ColorGroups[ColorGroups.size() - 1][1] = 0;
      ColorGroups[ColorGroups.size() - 1][2] = 255;
      return;
   }
   case GREEN:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 0;
      ColorGroups[ColorGroups.size() - 1][1] = 128;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case TEAL:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 0;
      ColorGroups[ColorGroups.size() - 1][1] = 128;
      ColorGroups[ColorGroups.size() - 1][2] = 128;
      return;
   }
   case LIME:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 0;
      ColorGroups[ColorGroups.size() - 1][1] = 255;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case SPRINGGREEN:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 0;
      ColorGroups[ColorGroups.size() - 1][1] = 255;
      ColorGroups[ColorGroups.size() - 1][2] = 127;
      return;
   }
   case AQUA: 
   {
      ColorGroups[ColorGroups.size() - 1][0] = 0;
      ColorGroups[ColorGroups.size() - 1][1] = 255;
      ColorGroups[ColorGroups.size() - 1][2] = 255;
      return;
   }
   case MAROON: 
   {
      ColorGroups[ColorGroups.size() - 1][0] = 128;
      ColorGroups[ColorGroups.size() - 1][1] = 0;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case PURPLE:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 128;
      ColorGroups[ColorGroups.size() - 1][1] = 0;
      ColorGroups[ColorGroups.size() - 1][2] = 128;
      return;
   }
   case OLIVE:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 128;
      ColorGroups[ColorGroups.size() - 1][1] = 128;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case GRAY:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 128;
      ColorGroups[ColorGroups.size() - 1][1] = 128;
      ColorGroups[ColorGroups.size() - 1][2] = 128;
      return;
   }
   case CHARTREUSE:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 127;
      ColorGroups[ColorGroups.size() - 1][1] = 255;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case RED: 
   {
      ColorGroups[ColorGroups.size() - 1][0] = 255;
      ColorGroups[ColorGroups.size() - 1][1] = 0;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case FUCHSIA: 
   {
      ColorGroups[ColorGroups.size() - 1][0] = 255;
      ColorGroups[ColorGroups.size() - 1][1] = 0;
      ColorGroups[ColorGroups.size() - 1][2] = 255;
      return;
   }
   case ORANGE: 
   {
      ColorGroups[ColorGroups.size() - 1][0] = 255;
      ColorGroups[ColorGroups.size() - 1][1] = 165;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case YELLOW: 
   {
      ColorGroups[ColorGroups.size() - 1][0] = 255;
      ColorGroups[ColorGroups.size() - 1][1] = 255;
      ColorGroups[ColorGroups.size() - 1][2] = 0;
      return;
   }
   case WHITE:
   {
      ColorGroups[ColorGroups.size() - 1][0] = 255;
      ColorGroups[ColorGroups.size() - 1][1] = 255;
      ColorGroups[ColorGroups.size() - 1][2] = 255;
      return;
   }
   }
   glutPostRedisplay();
}

/* �������� ���� */
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

   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* �������� ��������� */
void main(int argc, char* argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB);
   glutInitWindowSize(Width, Height);
   glutCreateWindow("�� 1. ������ ���������");
   ShowMenu();

   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Keyboard);
   glutMouseFunc(Mouse);

   /* �������, ����������� ����������� ���� ��� ������ � ������������ ���������. */
   glutMainLoop();
}
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment( linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Lab2.h"

Point* p;
int light = 5;
float angle_tiraj, angle_x = 0.0f, angle_y = 0.0f;
float rotateMatrix[3][3];

struct Figure
{
   vector<Point> Points;
};
Point pos, view, strafe, up = { 0.0f, 1.0f, 0.0f };
vector<Figure> Figures;
vector<Point> Normals;
vector<Point> SmoothNormals;
vector<int> Direction;
vector<float> TexCord = { 0.0f , 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };
GLint Width = GetSystemMetrics(SM_CXSCREEN), Height = GetSystemMetrics(SM_CYSCREEN);
int texWidth, texHeight;
GLuint type, tex[2];
unsigned char* pixels;
unsigned char* pixels1;

void multiply(Point& vec)
{
   vector<float> tmp;
   tmp.resize(3);
   for (int i = 0; i < 3; i++)
   {
      tmp[i] += rotateMatrix[i][0] * vec.x;
      tmp[i] += rotateMatrix[i][1] * vec.y;
      tmp[i] += rotateMatrix[i][2] * vec.z;
   }
   vec.x = tmp[0];
   vec.y = tmp[1];
   vec.z = tmp[2];
   tmp.clear();
}

/* Изменение вида */
void rotateView(float angle, int axis)
{
   float cosa = cos(angle), sina = sin(angle);
   if (axis == rotateAxis::rotateY)
   {
      rotateMatrix[0][0] = cosa + (1.0f - cosa) * up.x * up.x;
      rotateMatrix[0][1] = (1.0f - cosa) * up.x * up.y - sina * up.z;
      rotateMatrix[0][2] = (1.0f - cosa) * up.x * up.z + sina * up.y;
      rotateMatrix[1][0] = (1.0f - cosa) * up.x * up.y + sina * up.z;
      rotateMatrix[1][1] = cosa + (1.0f - cosa) * up.y * up.y;
      rotateMatrix[1][2] = (1.0f - cosa) * up.z * up.y - sina * up.x;
      rotateMatrix[2][0] = (1.0f - cosa) * up.x * up.z - sina * up.y;
      rotateMatrix[2][1] = (1.0f - cosa) * up.y * up.z + sina * up.x;
      rotateMatrix[2][2] = cosa + (1.0f - cosa) * up.z * up.z;
      multiply(view);
      multiply(strafe);
   }
   else
   {
      rotateMatrix[0][0] = cosa + (1.0f - cosa) * strafe.x * strafe.x;
      rotateMatrix[0][1] = (1.0f - cosa) * strafe.x * strafe.y - sina *
         strafe.z;
      rotateMatrix[0][2] = (1.0f - cosa) * strafe.x * strafe.z + sina *
         strafe.y;
      rotateMatrix[1][0] = (1.0f - cosa) * strafe.x * strafe.y + sina *
         strafe.z;
      rotateMatrix[1][1] = cosa + (1.0f - cosa) * strafe.y * strafe.y;
      rotateMatrix[1][2] = (1.0f - cosa) * strafe.z * strafe.y - sina *
         strafe.x;
      rotateMatrix[2][0] = (1.0f - cosa) * strafe.x * strafe.z - sina *
         strafe.y;
         rotateMatrix[2][1] = (1.0f - cosa) * strafe.y * strafe.z + sina *
         strafe.x;
      rotateMatrix[2][2] = cosa + (1.0f - cosa) * strafe.z * strafe.z;
      multiply(view);
      multiply(up);
   }
}

/* Специальные клавиши */
void specialKeys(int key, int x, int y)
{
   //if (key = 'q')
   //   rotateView();
   if (key == GLUT_KEY_RIGHT)
      rotateView(-3.0f * PI / 180.0f, rotateAxis::rotateY);
   if (key == GLUT_KEY_LEFT)
      rotateView(3.0f * PI / 180.0f, rotateAxis::rotateY);
   if (key == GLUT_KEY_DOWN)
      rotateView(3.0f * PI / 180.0f, rotateAxis::rotateX);
   if (key == GLUT_KEY_UP)
      rotateView(-3.0f * PI / 180.0f, rotateAxis::rotateX);
   glutPostRedisplay();
}

/* Рисование 3D сетки нулевой высоты */
void Draw3DSGrid()
{
   if (isShownGrid)
   {
      glColor3ub(253, 31, 212);
      glLineWidth(3);
      for (int i = -1000; i <= 1000; i += 50)
      {
         glBegin(GL_LINES);
         // Ось Х
         glVertex3f(-1000, 0, i);
         glVertex3f(1000, 0, i);
         // Ось Z
         glVertex3f(i, 0, -1050);
         glVertex3f(i, 0, 1050);
         glEnd();
      }
   }
}

/* Клавиатурное взаимодействие */
void Keyboard(unsigned char key, int x, int y)
{
   if (key == 27)
      exit(0);

   if (key == 'g')
      isShownGrid = !isShownGrid;

   /* Добавить повороты на кнопки: q и e */
   if (key == 'c')
      isCarcass = !isCarcass;
   if (key == 'n')
      isSmoothNorm = !isSmoothNorm;
   if (key == 'p')
      isPerspective = !isPerspective;
   if (key == 't')
      isTextured = !isTextured;
   if (key == 'w')
   {
      pos.z += speed * view.z;
      pos.x += speed * view.x;
      pos.y += speed * view.y;
   }
   if (key == 's')
   {
      pos.z -= speed * view.z;
      pos.x -= speed * view.x;
      pos.y -= speed * view.y;
   }
   if (key == 'a')
   {
      pos.z -= speed * strafe.z;
      pos.x -= speed * strafe.x;
      pos.y -= speed * strafe.y;
   }
   if (key == 'd')
   {
      pos.z += speed * strafe.z;
      pos.x += speed * strafe.x;
      pos.y += speed * strafe.y;
   }
   if (key == 'z')
      pos.y += speed;
   if (key == 'x')
      pos.y -= speed;
   if (key == '1')
      light = 1;
   if (key == '2')
      light = 2;
   if (key == '3')
      light = 3;
   if (key == '4')
      light = 4;
   if (key == '5')
      light = 5;
   if (key == '0')
      light = 0;
   glutPostRedisplay();
}

/* Нормализация вектора */
void norma(Point& vec)
{
   double sum = 0;
   sum = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
   vec.x /= sum;
   vec.y /= sum;
   vec.z /= sum;
}

Point normal(Point* n1, Point* n2, Point* n3)
{
   if (Direction[2] < 0)
   {
      Point w(n1->x - n2->x, n1->y - n2->y, n1->z - n2->z);
      Point v(n3->x - n2->x, n3->y - n2->y, n3->z - n2->z);
      Point p = Point(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
      norma(p);
      return p;
   }
   else
   {
      Point w(n1->x - n2->x, n1->y - n2->y, n1->z - n2->z);
      Point v(n3->x - n2->x, n3->y - n2->y, n3->z - n2->z);
      Point p = Point(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
      norma(p);
      return p;
   }
}

Point addWithNorm(Point & n1, Point & n2, Point & n3)
{
   Point p = Point(n1.x + n2.x + n3.x, n1.y + n2.y + n3.y, n1.z + n2.z + n3.z);
   norma(p);
   return p;
}

void makeNormals()
{
   Figure* fg = &Figures[0];
   Normals.push_back(normal(&fg->Points[1], &fg->Points[0], &fg->Points[3]));
   Normals.push_back(normal(&fg->Points[2], &fg->Points[1], &fg->Points[0]));
   Normals.push_back(normal(&fg->Points[3], &fg->Points[2], &fg->Points[1]));
   Normals.push_back(normal(&fg->Points[0], &fg->Points[3], &fg->Points[2]));
   for (int i = 1; i < Figures.size(); i++)
   {
      Figure* fg = &Figures[i];
      Normals.push_back(normal(&fg->Points[3], &fg->Points[0], &fg -> Points[1]));
      Normals.push_back(normal(&fg->Points[0], &fg->Points[1], &fg -> Points[2]));
      Normals.push_back(normal(&fg->Points[1], &fg->Points[2], &fg -> Points[3]));
      Normals.push_back(normal(&fg->Points[2], &fg->Points[3], &fg -> Points[0]));
   }
   SmoothNormals.push_back(addWithNorm(Normals[0], Normals[8], Normals[20]));
   SmoothNormals.push_back(addWithNorm(Normals[1], Normals[9], Normals[12]));
   SmoothNormals.push_back(addWithNorm(Normals[2], Normals[13], Normals[17]));
   SmoothNormals.push_back(addWithNorm(Normals[3], Normals[21], Normals[16]));
   SmoothNormals.push_back(addWithNorm(Normals[4], Normals[11], Normals[23]));
   SmoothNormals.push_back(addWithNorm(Normals[5], Normals[15], Normals[10]));
   SmoothNormals.push_back(addWithNorm(Normals[6], Normals[18], Normals[14]));
   SmoothNormals.push_back(addWithNorm(Normals[7], Normals[19], Normals[22]));
}

void Shine_a_Light()
{
   GLfloat ambience[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
   GLfloat material_diffuse[] = { 0.15f, 0.15f, 0.15f, 1.0f };
   glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
   glEnable(GL_COLOR_MATERIAL);
   //направленный
   if (light == 1)
   {
      GLfloat light0_diffuse[] = { 0.7f, 0.7f, 0.7f };
      GLfloat light0_direction[] = { 1.0f, 0.0f, 0.0f, 0.0f };
      glEnable(GL_LIGHT0);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
      glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
   }
   //точечный
   if (light == 2)
   {
      //убывание интенсивности с расстоянием
      //отключено (по умолчанию)
      GLfloat light1_diffuse[] = { 0.0f, 0.0f, 1.0f };// синий
      GLfloat light1_position[] = { 1.0f, 0.0f, 0.0f, 1.0f };
      glEnable(GL_LIGHT1);
      glLightfv(GL_LIGHT1, GL_AMBIENT, ambience);
      glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
      glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
   }
   //точечный
   if (light == 3)
   {
      //убывание интенсивности с расстоянием
      GLfloat light2_diffuse[] = { 0.0, 1.0, 1.0 };//желтый
      GLfloat light2_position[] = { 1.0f, 0.0f, 0.0f, 1.0f };
      glEnable(GL_LIGHT2);
      glLightfv(GL_LIGHT2, GL_AMBIENT, ambience);
      glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
      glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
      glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
      glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0);
      glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
   }
   //прожектор маленький угол
   if (light == 4)
   {
      //убывание интенсивности с расстоянием
      //отключено (по умолчанию)
      GLfloat light3_diffuse[] = { 1.0, 0.0, 0.0 };//красный
      GLfloat light3_position[] = { 1.0f, 1.0f, 1.0f, 1.0f };
      GLfloat light3_spot_direction[] = { 0.0f, 1.0f, 1.0f };
      glEnable(GL_LIGHT3);
      glLightfv(GL_LIGHT3, GL_AMBIENT, ambience);
      glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
      glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
      glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 60);
      glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
   }
   //прожектор
   if (light == 5)
   {
      //включен рассчет убывания интенсивности для прожектора
      GLfloat light4_diffuse[] = { 1.0f, 1.0f, 0.0f };//желтый
      GLfloat light4_position[] = { 0.0f, 0.0f, 50.0f, 1.0f };
      GLfloat light4_spot_direction[] = { 0.0f, 0.0f, -1.0f };
      glEnable(GL_LIGHT4);
      glLightfv(GL_LIGHT4, GL_AMBIENT, ambience);
      glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
      glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
      glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 150);
      glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light4_spot_direction);
      glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);
   }
   if (light == 0)
   {
      glDisable(GL_LIGHT0);
      glDisable(GL_LIGHT1);
      glDisable(GL_LIGHT2);
      glDisable(GL_LIGHT3);
      glDisable(GL_LIGHT4);
   }
}

bool makeTextures(int n)
{
   BITMAP bmp;
   if (n == 0)
   {
      LPCWSTR FileName1 = L"tex4.bmp";
      HBITMAP hbmp1 = (HBITMAP)LoadImage(NULL, FileName1, IMAGE_BITMAP, 0, 0,
         LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
      if (!hbmp1) return (false);
      GetObject(hbmp1, sizeof(bmp), &bmp);
   }
   else if (n == 1)
   {
      LPCWSTR FileName1 = L"tex5.bmp";
      HBITMAP hbmp1 = (HBITMAP)LoadImage(NULL, FileName1, IMAGE_BITMAP, 0, 0,
         LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
      if (!hbmp1) return (false);
      GetObject(hbmp1, sizeof(bmp), &bmp);
   }
   texWidth = bmp.bmWidth;
   texHeight = bmp.bmHeight;
   
   pixels = (unsigned char*)bmp.bmBits;
   type = GL_BGR_EXT;
   glGenTextures(2, tex);
   glBindTexture(GL_TEXTURE_2D, tex[n]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_BGR_EXT,
      GL_UNSIGNED_BYTE, pixels);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    return true;
}

void Display(void)
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
   gluLookAt(pos.x, pos.y, pos.z, 
             pos.x + view.x, pos.y + view.y, pos.z + view.z,
             up.x, up.y, up.z);
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (isPerspective)
      gluPerspective(50, 1.0 * Width / Height, 0.1f, 1000.0f);
   else
   {
      if (Width > Height)
         glOrtho(-200 * Width / Height, 200 * Width / Height, -200,
                  200, 300, -1000);
      else
         glOrtho(-200, 200, -200 * Width / Height,
                  200 * Width / Height, 300, -1000);
   }
   glClearColor(0.5, 0.7, 0.7, 1);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);
   Draw3DSGrid();
   Shine_a_Light();
   int n = 0;
   while (n != 2)
   {
      glPushMatrix();
      glTranslatef(n * 150, n * 10, n * 10);
      makeTextures(n);
      for (int i = 0; i < Figures.size(); i++)
      {
         if (isTextured)
            glEnable(GL_TEXTURE_2D);
         glColor3ub(255, 255, 255);
         if (isCarcass)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glBegin(GL_POLYGON);
         for (int j = 0; j < 4; j++)
         {
            if (!isSmoothNorm)
            {
               p = &Normals[4 * i + j];
               glNormal3f(p->x, p->y, p->z);
            }
            else
            {
               if (i < 2)
               {
                  p = &SmoothNormals[4 * i + j];
                  glNormal3f(p->x, p->y, p->z);
               }
               else
               {
                  p = &SmoothNormals[4 * (j / 2) + i % 3 + j % 2];
                  glNormal3f(p->x, p->y, p->z);
               }
            }
            p = &Figures[i].Points[j];
            if (isTextured)
               glTexCoord2f(TexCord[2 * j], TexCord[2 * j + 1]);
            glVertex3f(p->x, p->y, p->z);
         }
         glEnd();
         if (isTextured)
            glDisable(GL_TEXTURE_2D);
         glColor3ub(0, 0, 0);
         glBegin(GL_LINES);
         for (int j = 0; j < 4; j++)
         {
            p = &Figures[i].Points[j];
            if (!isSmoothNorm)
            {
               glVertex3f(p->x, p->y, p->z);
               glVertex3f(p->x + Normals[4 * i + j].x * 50, p->y + Normals[4 * i + j].y * 50, p->z + Normals[4 * i + j].z * 50);
            }
            else if (i < 2)
            {
               glVertex3f(p->x, p->y, p->z);
               glVertex3f(p->x + SmoothNormals[4 * i + j].x * 50, p->y +
                  SmoothNormals[4 * i + j].y * 50, p->z + SmoothNormals[4 * i + j].z * 50);
            }
         }
         glEnd();
      }
      n++;
      glPopMatrix();
   }
   glDisable(GL_LIGHT0);
   glDisable(GL_LIGHT1);
   glDisable(GL_LIGHT2);
   glDisable(GL_LIGHT3);
   glDisable(GL_LIGHT4);
   glutSwapBuffers();
}

/* Уже было */
void Reshape(GLint w, GLint h)
{
   Width = w;
   Height = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glViewport(0, 0, Width, Height);
   if (isPerspective)
      gluPerspective(60, 1.0 * Width / Height, 0.1f, 1000.0f);
   else
   {
      if (Width > Height)
         glOrtho(-200 * Width / Height, 200 * Width / Height, -200, 200, 300,
            -1000);
      else
         glOrtho(-200, 200, -200 * Width / Height, 200 * Width / Height, 300,
            -1000);
   }
   glMatrixMode(GL_MODELVIEW);
   glutPostRedisplay();
}

/* Тиражирование сечений */
void make_tirajj()
{
   double x, y;
   Figures.push_back(Figure());
   for (int i = 0; i < 4; i++)
   {
      Figures[1].Points.push_back(Point(Figures[0].Points[i].x + Direction[0], 
                                        Figures[0].Points[i].y + Direction[1], 
                                        Figures[0].Points[i].z + Direction[2]));
      x = Figures[1].Points[i].x;
      y = Figures[1].Points[i].y;

      Figures[1].Points[i].x = x * cos(angle_tiraj * PI / 180) - y * sin(angle_tiraj * PI / 180);
      Figures[1].Points[i].y = x * sin(angle_tiraj * PI / 180) + y * cos(angle_tiraj * PI / 180);
   }

   for (int j = 0; j < 4; j++)
   {
      Figures.push_back(Figure());
      Figures[j + 2].Points.push_back(Point(Figures[0].Points[j].x, 
                                            Figures[0].Points[j].y, 
                                            Figures[0].Points[j].z));

      Figures[j + 2].Points.push_back(Point(Figures[0].Points[(j + 1) % 4].x,
                                            Figures[0].Points[(j + 1) % 4].y,
                                            Figures[0].Points[(j + 1) % 4].z));
      
      Figures[j + 2].Points.push_back(Point(Figures[1].Points[(j + 1) % 4].x,
                                            Figures[1].Points[(j + 1) % 4].y,
                                            Figures[1].Points[(j + 1) % 4].z));

      Figures[j + 2].Points.push_back(Point(Figures[1].Points[j].x,
                                            Figures[1].Points[j].y,
                                            Figures[1].Points[j].z));
   }
}

/* Создание, позиционирование камеры */
void makeCamera()
{
   pos.x = (Figures[0].Points[0].x + Figures[0].Points[1].x) / 2.0f;
   pos.y = (Figures[0].Points[0].y + Figures[0].Points[2].y) / 2.0f;
   pos.z = (Figures[0].Points[0].z + Figures[0].Points[1].z) / 2.0f + 200.0f * Normals[0].z;
   view.x = -Normals[0].x;
   view.y = -Normals[0].y;
   view.z = -Normals[0].z;
   strafe.x = -view.z;
   strafe.z = view.x;
   norma(strafe);
}

void MoveMenu(int frag)
{
   switch (frag)
   {
   case Up:
      Keyboard('z', 0, 0);
      break;
   case Left:
      Keyboard('a', 0, 0);
      break;
   case Down:
      Keyboard('x', 0, 0);
      break;
   case Right:
      Keyboard('d', 0, 0);
      break;
   case Forward:
      Keyboard('w', 0, 0);
      break;
   case Backward:
      Keyboard('s', 0, 0);
      break;
   default:
      throw new exception("Unexpected move, bro. Cool your fucking");
      break;
   }
   glutPostRedisplay();
}


void LightningMenu(int frag)
{
   switch (frag)
   {
   case Directed:
      light = 1;
      break;
   case Dot1:
      light = 2;
      break;
   case Dot2:
      light = 3;
      break;
   case SpotlightSmallAngle:
      light = 4;
      break;
   case Spotlight:
      light = 5;
      break;
   case NoLight:
      light = 0;
      break;
   default:
      throw new exception("Unexpected light, bro");
      break;
   }
   glutPostRedisplay();
}

void MainMenu(int frag)
{
   switch (frag)
   {
   case 1:
      Keyboard('t', 0, 0);
      break;
   case 2:
      Keyboard('p', 0, 0);
      break;
   case 3:
      Keyboard('g', 0, 0);
      break;
   case 4:
      Keyboard('c', 0, 0);
      break;
   case 5:
      Keyboard('n', 0, 0);
      break;
   case 27:
      Keyboard(27, 0, 0);
      break;
   default:
      break;
   }
   glutPostRedisplay();
}

void ShowMenu()
{
   int MoveMenuID = glutCreateMenu(MoveMenu);
   glutAddMenuEntry("Up", Up);
   glutAddMenuEntry("Left", Left);
   glutAddMenuEntry("Down", Down);
   glutAddMenuEntry("Right", Right);
   glutAddMenuEntry("Forward", Forward);
   glutAddMenuEntry("Backward", Backward);

   int LightingMenuID = glutCreateMenu(LightningMenu);
   glutAddMenuEntry("Directed", Directed);
   glutAddMenuEntry("Dot1", Dot1);
   glutAddMenuEntry("Dot2", Dot2);
   glutAddMenuEntry("SpotlightSmallAngle", SpotlightSmallAngle);
   glutAddMenuEntry("Spotlight", Spotlight);
   glutAddMenuEntry("NoLight", NoLight);


   int MainMenuID = glutCreateMenu(MainMenu);
   glutAddSubMenu("Move", MoveMenuID);
   glutAddSubMenu("Lighting", LightingMenuID);

   // Очень хочется сделать меню динамическим.
   glutAddMenuEntry(isTextured ? "Hide texture" : "Show texture", 1);
   glutAddMenuEntry(isPerspective ? "Change to not perspective" : "Change to perspective", 2);
   glutAddMenuEntry(isShownGrid ? "Hide grid" : "Show grid", 3);
   glutAddMenuEntry(!isCarcass ? "Show carcass" : "Show material", 4);
   glutAddMenuEntry(isSmoothNorm ? "Disable smoothing normals" : "Enable this shit", 5);
   glutAddMenuEntry("Quit", 27);



   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutPostRedisplay();
}


/* Общие замечания:
* 1. Одна фигура статична, вторая двигается относительно нее при перемещении камеры. Баг или фича?
*/

int main(int argc, char* argv[])
{
   int x, y, z;

   /* Считываем данные из файла. */
   fstream fin("Datatxt.txt");
   Direction.resize(3);



   /* Аргументы:
   * 1. угол скручивания фигур;
   * 2. растянуть влево-вправо (в чем это измеряется я не понял);
   * 3. растянуть вверх-вниз (в чем это измеряется я не понял);
   * 4. длина параллелепипеда (всегда больше нуля).
   */
   fin >> angle_tiraj >> Direction[0] >> Direction[1] >> Direction[2];
   
   Figures.push_back(Figure());
   // Аргументы: Координаты точек квадрата (4 штуки).
   for (int j = 0; j < 4; j++)
   {
      fin >> x >> y >> z;
      Figures[0].Points.push_back(Point(x, y, z));
   }
   fin.close();

   // Если Direction[2] == 0, то вылет программы.
   if (Direction[2] != 0)
      make_tirajj();

   // Создаем нормали.
   makeNormals();

   // Создаем камеру.
   makeCamera();

   // Классика.
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   int mainWindow = glutCreateWindow("КГ ПМ-02 Саляев Янковский ПЗ 2");
   glutFullScreen();

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_POINT_SMOOTH);
   glutDisplayFunc(Display);
   glutSpecialFunc(specialKeys);
   glutSetCursor(1);
   glutKeyboardFunc(Keyboard);
   glutReshapeFunc(Reshape);
   ShowMenu();
   glutMainLoop();
   return 0;
}
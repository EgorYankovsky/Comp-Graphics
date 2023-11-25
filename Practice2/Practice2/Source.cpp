#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment( linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Lab2.h"

void Multiply(Vector& vec)
{
   vector<float> tmp(3);
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
void RotateView(float angle, int axis)
{
   float cosa = cos(angle), sina = sin(angle);
   switch (axis)
   {
   case RotateX:
      rotateMatrix[0][0] = cosa + (1.0f - cosa) * strafe.x * strafe.x;
      rotateMatrix[0][1] = (1.0f - cosa) * strafe.x * strafe.y - sina * strafe.z;
      rotateMatrix[0][2] = (1.0f - cosa) * strafe.x * strafe.z + sina * strafe.y;
      rotateMatrix[1][0] = (1.0f - cosa) * strafe.x * strafe.y + sina * strafe.z;
      rotateMatrix[1][1] = cosa + (1.0f - cosa) * strafe.y * strafe.y;
      rotateMatrix[1][2] = (1.0f - cosa) * strafe.z * strafe.y - sina * strafe.x;
      rotateMatrix[2][0] = (1.0f - cosa) * strafe.x * strafe.z - sina * strafe.y;
      rotateMatrix[2][1] = (1.0f - cosa) * strafe.y * strafe.z + sina * strafe.x;
      rotateMatrix[2][2] = cosa + (1.0f - cosa) * strafe.z * strafe.z;
      Multiply(view);
      Multiply(up);
      break;
   case RotateY:
      rotateMatrix[0][0] = cosa + (1.0f - cosa) * up.x * up.x;
      rotateMatrix[0][1] = (1.0f - cosa) * up.x * up.y - sina * up.z;
      rotateMatrix[0][2] = (1.0f - cosa) * up.x * up.z + sina * up.y;
      rotateMatrix[1][0] = (1.0f - cosa) * up.x * up.y + sina * up.z;
      rotateMatrix[1][1] = cosa + (1.0f - cosa) * up.y * up.y;
      rotateMatrix[1][2] = (1.0f - cosa) * up.z * up.y - sina * up.x;
      rotateMatrix[2][0] = (1.0f - cosa) * up.x * up.z - sina * up.y;
      rotateMatrix[2][1] = (1.0f - cosa) * up.y * up.z + sina * up.x;
      rotateMatrix[2][2] = cosa + (1.0f - cosa) * up.z * up.z;
      Multiply(view);
      Multiply(strafe);
      break;
   case RotateZ:
      rotateMatrix[0][0] = cosa + (1.0f - cosa) * view.x * view.x;
      rotateMatrix[0][1] = (1.0f - cosa) * view.x * view.y - sina * view.z;
      rotateMatrix[0][2] = (1.0f - cosa) * view.x * view.z + sina * view.y;
      rotateMatrix[1][0] = (1.0f - cosa) * view.x * view.y + sina * view.z;
      rotateMatrix[1][1] = cosa + (1.0f - cosa) * view.y * view.y;
      rotateMatrix[1][2] = (1.0f - cosa) * view.z * view.y - sina * view.x;
      rotateMatrix[2][0] = (1.0f - cosa) * view.x * view.z - sina * view.y;
      rotateMatrix[2][1] = (1.0f - cosa) * view.y * view.z + sina * view.x;
      rotateMatrix[2][2] = cosa + (1.0f - cosa) * view.z * view.z;
      Multiply(up);
      Multiply(strafe);
      break;
   default:
      throw new exception("Error during rotation");
   }
}

/* Call-back */
/* Специальные клавиши */
void SpecialKeys(int key, int x, int y)
{

   switch (key)
   {
   case GLUT_KEY_RIGHT:
      RotateView(-3.0f * PI / 180.0f, RotateY);
      break;
   case GLUT_KEY_LEFT:
      RotateView(3.0f * PI / 180.0f, RotateY);
      break;
   case GLUT_KEY_DOWN:
      RotateView(3.0f * PI / 180.0f, RotateX);
      break;
   case GLUT_KEY_UP:
      RotateView(-3.0f * PI / 180.0f, RotateX);
      break;
   case 60:
      RotateView(-3.0f * PI / 180.0f, RotateZ);
      break;
   case 62:
      RotateView(3.0f * PI / 180.0f, RotateZ);
      break;
   default:
      break;
   }
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

/* Call-back */
/* Клавиатурное взаимодействие */
void Keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'g':
      isShownGrid = !isShownGrid;
      break;
   case 'c':
      isCarcass = !isCarcass;
      break;
   case 'n':
      isSmoothNorm = !isSmoothNorm;
      break;
   case 'p':
      isPerspective = !isPerspective;
      break;
   case 't':
      isTextured = !isTextured;
      break;
   case 'w':
      pos.z += speed * view.z;
      pos.x += speed * view.x;
      pos.y += speed * view.y;
      break;
   case 's':
      pos.z -= speed * view.z;
      pos.x -= speed * view.x;
      pos.y -= speed * view.y;
      break;
   case 'a':
      pos.z -= speed * strafe.z;
      pos.x -= speed * strafe.x;
      pos.y -= speed * strafe.y;
      break;
   case 'd':
      pos.z += speed * strafe.z;
      pos.x += speed * strafe.x;
      pos.y += speed * strafe.y;
      break;
   case 'z':
      pos.y += speed;
      break;
   case 'x':
      pos.y -= speed;
      break;
   case '1':
      light = Directed;
      break;
   case '2':
      light = Dot1;
      break;
   case '3':
      light = Dot2;
      break;
   case '4':
      light = SpotlightSmallAngle;
      break;
   case '5':
      light = Spotlight;
      break;
   case '0':
      light = NoLight;
      break;
   case 60:
   case 62:
      SpecialKeys(key, 0, 0);
      break;
   case 27:
      exit(0);
   default:
      break;
   }

   /* Добавить повороты на кнопки: q и e */
   glutPostRedisplay();
}

// Функционал вроде один и тот же.
Vector Normal(Point* n1, Point* n2, Point* n3)
{
   Vector w(n1->x - n2->x, n1->y - n2->y, n1->z - n2->z);
   Vector v(n3->x - n2->x, n3->y - n2->y, n3->z - n2->z);
   Vector p = Vector(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
   p.Normalise();
   return p;
   //if (Direction[2] < 0) // Зачем ?
   //{
   //   Vector w(n1->x - n2->x, n1->y - n2->y, n1->z - n2->z);
   //   Vector v(n3->x - n2->x, n3->y - n2->y, n3->z - n2->z);
   //   Vector p = Vector(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
   //   p.Normalise();
   //   return p;
   //}
   //else
   //{
   //   Vector w(n1->x - n2->x, n1->y - n2->y, n1->z - n2->z);
   //   Vector v(n3->x - n2->x, n3->y - n2->y, n3->z - n2->z);
   //   Vector p = Vector(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
   //   p.Normalise();
   //   return p;
   //}
}

Vector AddWithNorm(Vector& n1, Vector& n2, Vector& n3)
{
   Vector p = Vector(n1.x + n2.x + n3.x, n1.y + n2.y + n3.y, n1.z + n2.z + n3.z);
   p.Normalise();
   return p;
}

void MakeNormals()
{
   Figure* fg = &Figures[0];
   Normals.push_back(Normal(&fg->Points[1], &fg->Points[0], &fg->Points[3]));
   Normals.push_back(Normal(&fg->Points[2], &fg->Points[1], &fg->Points[0]));
   Normals.push_back(Normal(&fg->Points[3], &fg->Points[2], &fg->Points[1]));
   Normals.push_back(Normal(&fg->Points[0], &fg->Points[3], &fg->Points[2]));
   for (int i = 1; i < Figures.size(); i++)
   {
      Figure* fg = &Figures[i];
      Normals.push_back(Normal(&fg->Points[3], &fg->Points[0], &fg -> Points[1]));
      Normals.push_back(Normal(&fg->Points[0], &fg->Points[1], &fg -> Points[2]));
      Normals.push_back(Normal(&fg->Points[1], &fg->Points[2], &fg -> Points[3]));
      Normals.push_back(Normal(&fg->Points[2], &fg->Points[3], &fg -> Points[0]));
   }
   SmoothedNormals.push_back(AddWithNorm(Normals[0], Normals[8], Normals[20]));
   SmoothedNormals.push_back(AddWithNorm(Normals[1], Normals[9], Normals[12]));
   SmoothedNormals.push_back(AddWithNorm(Normals[2], Normals[13], Normals[17]));
   SmoothedNormals.push_back(AddWithNorm(Normals[3], Normals[21], Normals[16]));
   SmoothedNormals.push_back(AddWithNorm(Normals[4], Normals[11], Normals[23]));
   SmoothedNormals.push_back(AddWithNorm(Normals[5], Normals[15], Normals[10]));
   SmoothedNormals.push_back(AddWithNorm(Normals[6], Normals[18], Normals[14]));
   SmoothedNormals.push_back(AddWithNorm(Normals[7], Normals[19], Normals[22]));
}

void ShineLight()
{
   GLfloat ambience[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
   GLfloat materialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

   GLfloat lightDiffuse[] = { 0.7f, 0.7f, 0.7f };
   GLfloat lightDirection[] = { 1.0f, 0.0f, 0.0f, 0.0f };
   GLfloat lightPosition[] = { 0.0f, 1000.0f, 0.0f, 1.0f };
   GLfloat lightSpotDirection[] = { 0.0f, 1.0f, 1.0f };

   /*
   * glMaterialfv - задает параметры материала для модели освещения.
   * GL_FRONT - 
   * GL_DIFFUSE - 
   */
   glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

   /*
   * glLightModeli - задает параметры модели освещения.
   * GL_LIGHT_MODEL_TWO_SIDE - 
   * GL_TRUE - 
   */
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
   
   /*
   * glEnable - позволяют включить или отключить возможности OpenGL.
   * GL_COLOR_MATERIAL
   */
   glEnable(GL_COLOR_MATERIAL);

   switch (light)
   {
   case Directed:
      glEnable(GL_LIGHT0);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
      glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
      break;
   case Dot1:
      //убывание интенсивности с расстоянием
      //отключено (по умолчанию)
      lightDiffuse[0] = 0.0f;
      lightDiffuse[1] = 0.0f;
      lightDiffuse[2] = 1.0f;
      glEnable(GL_LIGHT1);
      glLightfv(GL_LIGHT1, GL_AMBIENT, ambience);
      glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
      glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
      break;
   case Dot2:
      //убывание интенсивности с расстоянием
      lightDiffuse[0] = 0.0f;
      lightDiffuse[1] = 1.0f;
      lightDiffuse[2] = 0.0f;
      glEnable(GL_LIGHT2);
      glLightfv(GL_LIGHT2, GL_AMBIENT, ambience);
      glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
      glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);
      glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
      glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0);
      glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
      break;
   case SpotlightSmallAngle:
      //убывание интенсивности с расстоянием
      //отключено (по умолчанию)
      lightDiffuse[0] = 1.0f;
      lightDiffuse[1] = 0.0f;
      lightDiffuse[2] = 0.0f;
      glEnable(GL_LIGHT3);
      glLightfv(GL_LIGHT3, GL_AMBIENT, ambience);
      glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDiffuse);
      glLightfv(GL_LIGHT3, GL_POSITION, lightPosition);
      glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 60);
      glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightSpotDirection);
      break;
   case Spotlight:
      //включен рассчет убывания интенсивности для прожектора
      lightDiffuse[0] = 1.0f;
      lightDiffuse[1] = 1.0f;
      lightDiffuse[2] = 0.0f;
      glEnable(GL_LIGHT4);
      glLightfv(GL_LIGHT4, GL_AMBIENT, ambience);
      glLightfv(GL_LIGHT4, GL_DIFFUSE, lightDiffuse);
      glLightfv(GL_LIGHT4, GL_POSITION, lightPosition);
      glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 150);
      glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lightSpotDirection);
      glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);
      break;
   case NoLight:
      glDisable(GL_LIGHT0);
      glDisable(GL_LIGHT1);
      glDisable(GL_LIGHT2);
      glDisable(GL_LIGHT3);
      glDisable(GL_LIGHT4);
      break;
   default:
      throw new exception("Unexpected lighting mode.");
      
   }
}

bool MakeTextures(int n)
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

/* Call-back */
/* C вероятностью 99% ошибка здесь */
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
   glClearColor(0.5, 0.5, 0.5, 1.0); // Фон.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);
   Draw3DSGrid();
   ShineLight();
   int n = 0;
   while (n != 2)
   {
      glPushMatrix();
      glTranslatef(n * 150, n * 10, n * 10);
      MakeTextures(n);
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
                  p = &SmoothedNormals[4 * i + j];
                  glNormal3f(p->x, p->y, p->z);
               }
               else
               {
                  p = &SmoothedNormals[4 * (j / 2) + i % 3 + j % 2];
                  glNormal3f(p->x, p->y, p->z);
               }
            }
            p->ConvertToVector(&Figures[i].Points[j]);
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
            p->ConvertToVector(&Figures[i].Points[j]);
            if (!isSmoothNorm)
            {
               glVertex3f(p->x, p->y, p->z);
               glVertex3f(p->x + Normals[4 * i + j].x * 50, p->y + Normals[4 * i + j].y * 50, p->z + Normals[4 * i + j].z * 50);
            }
            else if (i < 2)
            {
               glVertex3f(p->x, p->y, p->z);
               glVertex3f(p->x + SmoothedNormals[4 * i + j].x * 50, p->y +
                  SmoothedNormals[4 * i + j].y * 50, p->z + SmoothedNormals[4 * i + j].z * 50);
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

/* Call-back */
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
         glOrtho(-200 * Width / Height, 200 * Width / Height, -200, 200, 300, -1000);
      else
         glOrtho(-200, 200, -200 * Width / Height, 200 * Width / Height, 300, -1000);
   }
   glMatrixMode(GL_MODELVIEW);
   glutPostRedisplay();
}

/* Тиражирование сечений */
void MakeTirajj()
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
void MakeCamera()
{
   pos.x = (Figures[0].Points[0].x + Figures[0].Points[1].x) / 2.0f;
   pos.y = (Figures[0].Points[0].y + Figures[0].Points[2].y) / 2.0f;
   pos.z = (Figures[0].Points[0].z + Figures[0].Points[1].z) / 2.0f + 200.0f * Normals[0].z;
   view.x = -Normals[0].x;
   view.y = -Normals[0].y;
   view.z = -Normals[0].z;
   strafe.x = -view.z;
   strafe.z = view.x;
   strafe.Normalise();
}

void MoveMenu(int flag)
{
   switch (flag)
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

void LightningMenu(int flag)
{
   light = flag;
   glutPostRedisplay();
}

void MainMenu(int flag)
{
   switch (flag)
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

void AngleMenu(int flag)
{
   switch (flag)
   {
   case PitchUp:
      SpecialKeys(GLUT_KEY_DOWN, 0, 0);
      break;
   case PitchDown:
      SpecialKeys(GLUT_KEY_UP, 0, 0);
      break;
   case RightYaw:
      SpecialKeys(GLUT_KEY_RIGHT, 0, 0);
      break;
   case LeftYaw:
      SpecialKeys(GLUT_KEY_LEFT, 0, 0);
      break;
   case LeftRoll:
      SpecialKeys(60, 0, 0);
      break;
   case RightRoll:
      SpecialKeys(62, 0, 0);
      break;
   default:
      throw new exception("Kuda move");
      break;
   }
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
   glutAddMenuEntry("Dot 1", Dot1);
   glutAddMenuEntry("Dot 2", Dot2);
   glutAddMenuEntry("Spotlight small angle", SpotlightSmallAngle);
   glutAddMenuEntry("Spotlight", Spotlight);
   glutAddMenuEntry("No light", NoLight);

   int AngleMenuID = glutCreateMenu(AngleMenu);
   glutAddMenuEntry("Pitch up", PitchUp);
   glutAddMenuEntry("Pitch down", PitchDown);
   glutAddMenuEntry("Right yaw", RightYaw);
   glutAddMenuEntry("Left yaw", LeftYaw);
   glutAddMenuEntry("Left roll", LeftRoll);
   glutAddMenuEntry("Right roll", RightRoll);

   int MainMenuID = glutCreateMenu(MainMenu);
   glutAddSubMenu("Move", MoveMenuID);
   glutAddSubMenu("Lighting", LightingMenuID);
   glutAddSubMenu("Angle", AngleMenuID);

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
* 2. Неправильная отрисовка освещения на 4/6 сторонах. (Возможно проблема в неправильном расположении сторон).
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
   if (Direction[2] == 0)
      throw new exception("Figure is 2-dim. Emergency exit");

   MakeTirajj();

   // Создаем нормали.
   MakeNormals();

   // Создаем камеру.
   MakeCamera();

   // Классика.
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   int mainWindow = glutCreateWindow("КГ ПМ-02 Саляев Янковский ПЗ 2");
   glutFullScreen();

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_POINT_SMOOTH);
   glutDisplayFunc(Display);
   glutSpecialFunc(SpecialKeys);
   glutSetCursor(1);
   glutKeyboardFunc(Keyboard);
   glutReshapeFunc(Reshape);
   ShowMenu();
   glutMainLoop();
   return 0;
}
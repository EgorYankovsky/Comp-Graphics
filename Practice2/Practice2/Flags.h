#pragma once

bool isSmoothNorm = true,
     isCarcass = false,
     isPerspective = true,
     isTextured = true,
     isShownGrid = true;


enum Angle
{
   PitchUp,
   PitchDown,
   RightYaw,
   LeftYaw,
   LeftRoll,
   RightRoll
};

enum RotateAxis
{
   RotateY, 
   RotateX,
   RotateZ
};

enum MoveMenuFlags
{
   Up,
   Left,
   Down,
   Right,
   Forward,
   Backward
};

enum LightingMode
{
   NoLight,
   Directed,
   Dot1,
   Dot2,
   SpotlightSmallAngle,
   Spotlight
};
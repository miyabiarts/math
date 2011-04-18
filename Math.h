#pragma once

#include <iostream>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Plane.h"
#include "Color.h"

const double PI = 3.1415926535897932384626433832795;


inline double toRadian(double degree)
{
  return PI * degree/180;
}

inline double toDegree(double rad)
{
  return rad*180 / PI;
}


inline float toRadian(float degree)
{
  return static_cast<float>(PI * degree/180);
}

inline float toDegree(float rad)
{
  return static_cast<float>(rad*180 / PI);
}

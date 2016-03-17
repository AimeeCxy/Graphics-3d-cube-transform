#include "StdAfx.h"
#include "Point_3D.h"

Point_3D::Point_3D(void)
: x(0)
, y(0)
, z(0)
{
}

Point_3D::~Point_3D(void)
{
}

Point_3D::Point_3D(int xCorrd, int yCorrd, int zCorrd)
{
	x = xCorrd;
	y = yCorrd;
	z = zCorrd;
}

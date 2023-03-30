#include "utils.h"

#include <math.h>

double degree_to_radian(double degree)
{
	return degree * atan(1)*4 / 180.0;
}

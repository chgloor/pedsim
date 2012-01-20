

#include "vector.h"

#include "math.h"

/// vector cross product helper
/// \author  chgloor
/// \date    2010-02-12
void Tvector::cross(Tvector *a, Tvector *b) {
	this->x = a->y*b->z - a->z*b->y;
	this->y = a->z*b->x - a->x*b->z;
	this->z = a->x*b->y - a->y*b->x;
}


/// vector normalization
/// \author  chgloor
/// \date    2010-02-12
void Tvector::normalize() {
	double length = sqrt(x*x + y*y + z*z);
	x = x / length;
	y = y / length;
	z = z / length;
}

/// vector scalar product
/// \author  chgloor
/// \date    2012-01-14
double Tvector::scalar(Tvector *a, Tvector *b) {
	return acos( (a->x*b->x + a->y*b->y + a->z*b->z) / ( sqrt(a->x*a->x + a->y*a->y + a->z*a->z) * sqrt(b->x*b->x + b->y*b->y + b->z*b->z) ) );
}

/**
 * @file MyPoint.cpp
 * @brief Implements 2D and 3D distance calculations for the MyPoint class.
 */
#include "MyPoint.h"

using namespace std;

double MyPoint::distanceTo_2D(const MyPoint& p) const {
	// Euclidean distance in 2D (ignoring Z)
	return sqrt(pow(x - p.x,2) + pow(y-p.y,2));
	
}

double MyPoint::distanceTo_3D(const MyPoint& p) const {
	// Euclidean distance in 3D
	return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2));

}

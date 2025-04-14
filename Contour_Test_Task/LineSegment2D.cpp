/**
 * @file LineSegment2D.h
 * @brief Represents a 2D line segment defined by two endpoints and provides slope calculation.
 */
#include "LineSegment2D.h"

 /**
  * @brief Calculates and stores the slope of the line segment.
  *
  * Computes the slope between point A and point B. If the segment is vertical
  * (i.e., dx is near zero), the slope is set to positive infinity.
  */
void LineSegment2D::calcSlope(){

    double dx = pointB.getX() - pointA.getX();
    double dy = pointB.getY() - pointA.getY();
    if (std::abs(dx) < 1e-9) {
        // Vertical line
        slope = std::numeric_limits<double>::infinity();
    }
    else {
        slope = dy / dx;
    }

}
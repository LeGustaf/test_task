/**
 * @file ContourUtils.h
 * @brief Utility functions for generating and manipulating Contour2D objects.
 */
#pragma once
#include "Contour2D.h"
#include "LineSegment2D.h"

 /**
  * @brief Constructs a Contour2D from a list of points interpreted as a polyline.
  *
  * Creates a contour by connecting each consecutive pair of points with a LineSegment2D.
  * Optionally closes the contour by connecting the last point back to the first.
  *
  * @param ptr Vector of points to connect.
  * @param closedContour If true, adds a segment from the last point to the first.
  * @return A Contour2D composed of straight segments between the given points.
  */
Contour2D polylineContourFromPoints(std::vector<MyPoint>& ptr, bool closedContour);
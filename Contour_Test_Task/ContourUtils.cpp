/**
 * @file ContourUtils.cpp
 * @brief Implements utility functions for constructing Contour2D objects.
 */
#include "ContourUtils.h"

 /**
  * @brief Converts a sequence of points into a polyline contour.
  *
  * Creates line segments between each consecutive pair of points.
  * Optionally closes the contour by connecting the last point to the first.
  * Points closer than Contour2D::defaultEpsilon are ignored to prevent zero-length segments.
  *
  * @param ptr Vector of MyPoint representing the polyline.
  * @param closedContour Whether to close the contour (connect last to first).
  * @return A Contour2D object built from the input points.
  */
Contour2D polylineContourFromPoints(std::vector<MyPoint>& ptr, bool closedContour = false) {

	Contour2D myContour;
	if (!ptr.empty()) {

		for (size_t i = 0; i + 1 < ptr.size(); ++i) {
			if (ptr[i].distanceTo_2D(ptr[i + 1]) > Contour2D::defaultEpsilon) {
				myContour.addSegment(std::make_unique<LineSegment2D>(ptr[i], ptr[i + 1]));
			}
		}

		if (closedContour) {
			if (ptr.front().distanceTo_2D(ptr.back()) > Contour2D::defaultEpsilon) {
				myContour.addSegment(std::make_unique<LineSegment2D>(ptr.back(), ptr.front()));
			}
		}
		
	}
	return myContour;

}

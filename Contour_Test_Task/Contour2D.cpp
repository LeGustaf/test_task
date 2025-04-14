/**
 * @file Contour2D.cpp
 * @brief Implements the Contour2D class methods, including copy/move logic, validation, and geometry manipulation.
 */
#include "Contour2D.h"

Contour2D::Contour2D(const Contour2D& other) {
	for (const auto& seg : other.segments) {
		segments.push_back(seg->clone());
	}
	cacheValidity = false;
}

Contour2D& Contour2D::operator=(const Contour2D& other) {
	if (this != &other) {
		segments.clear();
		for (const auto& seg : other.segments) {
			segments.push_back(seg->clone());
		}
	}
	return *this;
}

void Contour2D::addSegment(std::unique_ptr<Segment2D> segment) {
	segments.push_back(std::move(segment));
	cacheValidity = false;
}
void Contour2D::addSegment(const Segment2D& segment) {
	segments.push_back(segment.clone());
	cacheValidity = false;
}

void Contour2D::insertSegment(std::unique_ptr<Segment2D> segment, int position) {
	if (position < 0 || position > static_cast<int>(segments.size())) {
		throw std::out_of_range("Invalid position in insertSegment()");
	}

	segments.insert(segments.begin() + position, std::move(segment));
	cacheValidity = false;
}

void Contour2D::removeSegment(int position) {
	if (position < 0 || position >= static_cast<int>(segments.size())) {
		throw std::out_of_range("Invalid position in removeSegment()");
	}
	segments.erase(segments.begin() + position);
	cacheValidity = false;
}


/**
 * @brief Checks if all segments in the contour are connected end-to-end within a tolerance.
 *
 * This method is cached for performance. A contour is valid if the end of each segment
 * matches the start of the next within a small epsilon.
 *
 * @return True if the contour is continuous.
 */
bool Contour2D::isValid() const {
	//here we check the distance between the end of a segmnet and the following segment
	//since these are not directional segments, distance is calculated between point b and point A of the next pointer
	//need to go through all the segments in this contuor
	//need to cache the validity check to avoid recalculations
	if (!cacheValidity) {
		cachedIsValid = true;
		for (size_t i = 0; i + 1 < segments.size(); ++i) {
			const MyPoint& end = segments[i]->getPointB();
			const MyPoint& start = segments[i + 1]->getPointA();
			if (end.distanceTo_2D(start) > epsilon) {
				cachedIsValid = false;
			}
		}
		cacheValidity = true;
	}
	return cachedIsValid;

}

Segment2D& Contour2D::getSegmentAt(std::size_t index) {
	if (index >= segments.size()) {
		throw std::out_of_range("Invalid index in getSegmentAt()");
	}
	return *segments[index];
}


void Contour2D::move(double dx, double dy) {
	for (auto& segPtr : segments) {
		segPtr->move(dx, dy);
	}
}

/**
 * @brief Checks if the contour forms a closed loop.
 *
 * A contour is considered closed if it's valid and the end of the last segment
 * is within epsilon of the start of the first segment.
 *
 * @return True if the contour is closed.
 */

bool Contour2D::isClosedShape() const {

	if (!isValid()) {
		return false;
	}

	if (segments.size() == 1) {
		if (segments.front()->isNonZeroLength(epsilon)) {
			return (segments.front()->getPointA().distanceTo_2D(segments.front()->getPointB()) < epsilon);
		}
	}
	else if (segments.size() > 1) {

		if (segments.back()->getPointB().distanceTo_2D(segments.front()->getPointA()) < epsilon) {
			return true;
		}
	}
	return false;
}
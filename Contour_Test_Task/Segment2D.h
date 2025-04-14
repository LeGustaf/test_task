/**
 * @file Segment2D.h
 * @brief Defines the abstract base class for all 2D segments (e.g., lines, arcs).
 */
#pragma once
#include <memory>
#include <vector>   
#include <utility>
#define _USE_MATH_DEFINES 
#include <math.h>
#include "MyPoint.h"

 /**
  * @class Segment2D
  * @brief Abstract interface for 2D geometric segments.
  *
  * Provides a common interface for operations on segments like movement, length calculation,
  * and point access. Used as a polymorphic base for concrete types such as LineSegment2D and ArcSegment2D.
  */
class Segment2D {
private:
	MyPoint pointA, pointB;
	double myLength;

public:
	/**
	* @brief Virtual destructor.
	*/
	virtual ~Segment2D() = default;
	/**
	* @brief Creates a deep copy of the segment.
	* @return A unique_ptr to a cloned Segment2D object.
	*/
	virtual std::unique_ptr<Segment2D> clone() const = 0;  // Cloning for copying
	/**
	* @brief Returns a reference to the starting point of the segment.
	* @return Const reference to point A.
	*/
	virtual const MyPoint& getPointA() const = 0;
	/**
	* @brief Returns a reference to the ending point of the segment.
	* @return Const reference to point B.
	*/
	virtual const MyPoint& getPointB() const = 0;
	/**
	* @brief Translates the segment by a given delta in x and y.
	* @param dx Offset in the X direction.
	* @param dy Offset in the Y direction.
	*/
	virtual void move(double dx, double dy) = 0;
	/**
	* @brief Calculates and updates the segment's length.
	*/
	virtual void length() = 0;
	/**
	* @brief Checks if the segment length exceeds a given threshold.
	* @param epsilon Minimum non-zero threshold.
	* @return True if length is greater than epsilon.
	*/
	virtual bool isNonZeroLength(double epsilon) const = 0;

};

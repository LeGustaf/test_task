/**
 * @file LineSegment2D.h
 * @brief Defines a 2D line segment derived from Segment2D.
 */
#pragma once
#include "Segment2D.h"

 /**
  * @class LineSegment2D
  * @brief Represents a straight 2D line segment between two points.
  *
  * Provides geometric utilities such as length, slope calculation, and movement.
  * Automatically recalculates properties when endpoints are modified.
  */
class LineSegment2D : public Segment2D {
private:
	double length_;
	double slope;
	MyPoint pointA;
	MyPoint pointB;
public:
	/**
	* @brief Creates a clone (deep copy) of the line segment.
	* @return A unique_ptr to the cloned LineSegment2D.
	*/
	std::unique_ptr<Segment2D> clone() const override {
		return std::make_unique<LineSegment2D>(*this);
	}
	/**
	* @brief Constructs a line segment from two endpoints.
	* @param a Start point.
	* @param b End point.
	*/
	LineSegment2D(const MyPoint& a, const MyPoint& b)
		: pointA(a), pointB(b) {
		calcSlope();
		length();
	}
	/**
	* @brief Gets the first endpoint of the segment.
	* @return Reference to point A.
	*/
	const MyPoint& getPointA() const override { return pointA; }
	/**
	 * @brief Gets the second endpoint of the segment.
	 * @return Reference to point B.
	 */
	const MyPoint& getPointB() const override { return pointB; }
	/**
	* @brief Returns the slope of the segment.
	* @return Slope value (infinite if vertical).
	*/
	double getSlope() const { return slope; }
	/**
	* @brief Sets the start point and updates length and slope.
	* @param newA New start point.
	*/
	void calcSlope();
	/**
	* @brief Sets the start point and updates length and slope.
	* @param newA New start point.
	*/
	void setPointA(const MyPoint& newA) {
		pointA = newA;
		calcSlope();
		length();
	}
	/**
	* @brief Sets the end point and updates length and slope.
	* @param newB New end point.
	*/
	void setPointB(const MyPoint& newB) {
		pointB = newB;
		calcSlope();
		length();
	}
	/**
	* @brief Translates the line segment by a given delta in x and y.
	* @param dx Offset along X.
	* @param dy Offset along Y.
	*/
	void move(double dx, double dy) override {
		pointA.setX(pointA.getX() + dx);
		pointB.setX(pointB.getX() + dx);

		pointA.setY(pointA.getY() + dy);
		pointB.setY(pointB.getY() + dy);
		calcSlope();

	}
	/**
	* @brief Calculates and stores the segment length.
	*/
	void length() override {
		length_ = getPointA().distanceTo_2D(getPointB());
	}
	/**
	* @brief Checks whether the line has a non-zero length above a threshold.
	* @param epsilon Tolerance value.
	* @return True if length exceeds epsilon.
	*/
	bool isNonZeroLength(double epsilon) const { return (length_ > epsilon); }
};

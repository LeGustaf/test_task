/**
 * @file ArcSegment2D.h
 * @brief Defines a 2D circular arc segment derived from Segment2D.
 *
 * Supports construction from endpoints and radius or from polar parameters (center, angles).
 * Provides utilities for modifying arc geometry and calculating length.
 */

#pragma once
#include <iostream>
#include "Segment2D.h"
#include "MyPoint.h"

 /**
  * @class ArcSegment2D
  * @brief Represents a 2D arc segment defined by a circular arc between two points.
  *
  * Stores geometric data such as center, radius, orientation, and start/end angles.
  * Can be created from endpoints or directly via polar form. Supports movement,
  * recalculation, and conversion from polar to Cartesian coordinates.
  */
class ArcSegment2D : public Segment2D {
private:
	double radius;
	double startAngle;
	double endAngle;
	double length_;
	bool clockwise;
	MyPoint center;
	MyPoint pointA;
	MyPoint pointB;

public:

	/**
	* @brief Creates a copy of this arc segment.
	* @return A unique_ptr to the cloned ArcSegment2D.
	*/
	std::unique_ptr<Segment2D> clone() const override {
		return std::make_unique<ArcSegment2D>(*this);
	}

	/**
	* @brief Constructs an arc from two endpoints and a radius.
	*
	* If the specified radius is too small to form a valid arc, it is clamped slightly above the minimum.
	*
	* @param start Starting point of the arc.
	* @param end Ending point of the arc.
	* @param radius_ Desired radius of the arc.
	* @param clockwise_ Direction of curvature (true = clockwise).
	*/
	ArcSegment2D(MyPoint start, MyPoint end, double radius_, bool clockwise_ = true) : pointA(start), pointB(end), radius(radius_), clockwise(clockwise_)
	{
		calculateFromEndpoints();
	}
	/**
	* @brief Constructs an arc from center, radius, and angle parameters.
	*
	* @param c Center of the arc.
	* @param r Radius.
	* @param startAng Start angle in radians.
	* @param endAng End angle in radians.
	*/
	ArcSegment2D(const MyPoint& c, double r, double startAng, double endAng)
		: center(c), radius(r), startAngle(startAng), endAngle(endAng)
	{
		pointB = polarToCartesian(center, radius, endAngle);
		pointA = polarToCartesian(center, radius, startAngle);
		length();
		double angleSweep = endAngle - startAngle;
		if (angleSweep < 0) { angleSweep += 2 * M_PI; }
		clockwise = angleSweep > M_PI;

	}

	/**
	 * @brief Recalculates center and angles based on endpoints and radius.
	 *
	 * This is used internally when modifying or moving the arc.
	 */
	void calculateFromEndpoints() {
		double dx = pointB.getX() - pointA.getX();
		double dy = pointB.getY() - pointA.getY();
		double chordLen = std::sqrt(dx * dx + dy * dy);
		double minRadius = chordLen / 2;
		if (minRadius > radius) {
			std::cerr << "Radius too small, clamping to " << (minRadius * 1.1) << std::endl;
			radius = minRadius * 1.1;
		}

		double mx = (pointB.getX() + pointA.getX()) / 2;
		double my = (pointB.getY() + pointA.getY()) / 2;
		double h = std::sqrt(radius * radius - (chordLen * chordLen) / 4);

		double perp_dx = -dy;
		double perp_dy = dx;
		double mag = std::sqrt(perp_dx * perp_dx + perp_dy * perp_dy);
		perp_dx /= mag;
		perp_dy /= mag;

		// Adjust direction
		if (!clockwise) {
			perp_dx = -perp_dx;
			perp_dy = -perp_dy;
		}

		double cx = mx + h * perp_dx;
		double cy = my + h * perp_dy;

		center = MyPoint(cx, cy);
		// Ensure angle is in range [-PI, PI] if needed later for arc traversal
		startAngle = atan2(pointA.getY() - cy, pointA.getX() - cx);
		endAngle = atan2(pointB.getY() - cy, pointB.getX() - cx);

		length();
	}

	const MyPoint& getPointA() const override { return pointA; }
	const MyPoint& getPointB() const override { return pointB; }

	/**
	* @brief Returns whether the arc is clockwise.
	* @return True if clockwise, false if counter-clockwise.
	*/
	bool isClockwise() const { return clockwise; }
	/**
	* @brief Converts polar coordinates to Cartesian coordinates.
	* @param c Arc center.
	* @param r Radius.
	* @param angle Angle in radians.
	* @return Resulting Cartesian point.
	*/
	static MyPoint polarToCartesian(const MyPoint& c, double r, double angle) {
		return MyPoint(
			c.getX() + r * std::cos(angle), c.getY() + r * std::sin(angle), c.getZ()
		);
	}

	/**
	* @brief Translates the arc by a given delta in x and y.
	* @param dx Offset in X.
	* @param dy Offset in Y.
	*/
	void move(double dx, double dy) override {

		pointA.setX(pointA.getX() + dx);
		pointA.setY(pointA.getY() + dy);
		pointB.setX(pointB.getX() + dx);
		pointB.setY(pointB.getY() + dy);
		calculateFromEndpoints();
	}
	/**
	* @brief Calculates the arc length based on radius and angle span.
	*/
	void length() override {

		double arc_ = endAngle - startAngle;
		if (arc_ < 0) {
			arc_ += 2 * M_PI;
		}
		length_ = radius * arc_;
	}
	/**
	 * @brief Checks whether the arc has a non-zero length above a threshold.
	 * @param epsilon Tolerance value.
	 * @return True if arc length exceeds epsilon.
	 */
	bool isNonZeroLength(double epsilon) const { return (length_ > epsilon); }
};


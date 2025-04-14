/**
 * @file Contour2D.h
 * @brief Defines a 2D contour composed of connected line or arc segments.
 *
 * A Contour2D is a container for ordered segments (e.g., LineSegment2D, ArcSegment2D)
 * forming an open or closed polyline. It supports geometric queries, modification,
 * movement, and validity checking.
 */
#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include "Segment2D.h"
#include "MyPoint.h"

 /**
 * @class Contour2D
 * @brief Represents a 2D contour composed of connected segments.
 *
 * Allows adding, removing, and moving segments, and checks if the contour is valid (i.e., continuous).
 * A contour is considered valid if all segments are connected end-to-end within a small epsilon tolerance.
 */
class Contour2D {
private:
	const double epsilon = defaultEpsilon;
	std::vector<std::unique_ptr<Segment2D>> segments;
	mutable bool cachedIsValid = false;
	mutable bool cacheValidity = false;

public:

	static constexpr double defaultEpsilon = 1e-5;
	/**
	* @brief Default constructor.
	*/
	Contour2D() = default;
	/**
	* @brief Copy constructor.
	* @param other Contour2D to copy from.
	*/
	Contour2D(const Contour2D& other);
	/**
	* @brief Copy assignment operator.
	* @param other Contour2D to copy from.
	* @return Reference to this.
	*/
	Contour2D& operator=(const Contour2D& other);
	/**
	* @brief Move constructor.
	* @param other Contour2D to move from.
	*/
	Contour2D(Contour2D&& other) noexcept = default;
	/**
	* @brief Move assignment operator.
	* @param other Contour2D to move from.
	* @return Reference to this.
	*/
	Contour2D& operator=(Contour2D&& other) noexcept = default;


	/**
	* @brief Adds a segment to the contour.
	* @param segment A unique_ptr to a Segment2D.
	*/
	void addSegment(std::unique_ptr<Segment2D> segment);
	/**
	* @brief Adds a copy of an existing segment to the contour.
	* @param segment The Segment2D to copy.
	*/
	void addSegment(const Segment2D& segment);
	/**
	* @brief Checks whether the contour is valid (continuous).
	* @return True if all segments are connected within epsilon.
	*/
	bool isValid() const;
	/**
	* @brief Inserts a segment at a specified position.
	* @param segment A unique_ptr to a Segment2D.
	* @param position Index at which to insert the segment.
	*/
	void insertSegment(std::unique_ptr<Segment2D> segment, int position);
	/**
	* @brief Removes a segment at the given position.
	* @param position Index of the segment to remove.
	*/
	void removeSegment(const int position);
	/**
	* @brief Retrieves a reference to the segment at the given index.
	* @param index Index of the segment.
	* @return Reference to the Segment2D.
	*/
	Segment2D& getSegmentAt(std::size_t index);

	/**
	 * @brief Returns a const iterator to the beginning of the segment container.
	 */
	std::vector<std::unique_ptr<Segment2D>>::const_iterator begin() const { return segments.begin(); }
	/**
	* @brief Returns a const iterator to the end of the segment container.
	*/
	std::vector<std::unique_ptr<Segment2D>>::const_iterator end() const { return segments.end(); }
	/**
	* @brief Determines whether the contour forms a closed shape.
	* @return True if the start point and end point are within epsilon.
	*/
	bool isClosedShape() const;
	/**
	* @brief Translates all segments in the contour by the given delta.
	* @param dx Offset along the X axis.
	* @param dy Offset along the Y axis.
	*/
	void move(double dx, double dy);
	/**
	* @brief Returns the number of segments in the contour.
	* @return Number of segments.
	*/
	size_t getSegmentCount()const { return segments.size(); }

};

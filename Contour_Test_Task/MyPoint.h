/**
 * @file MyPoint.h
 * @brief Defines a simple 3D point class with basic distance and accessor methods.
 */
#pragma once
#include <cmath>
 /**
  * @class MyPoint
  * @brief Represents a 3D point with x, y, z coordinates.
  *
  * Provides getters/setters and distance calculations in both 2D and 3D space.
  * Used as a fundamental geometric type across contour and segment operations.
  */

class MyPoint
{
private:
	double x, y, z;
public:
	/**
	* @brief Constructs a point with the given coordinates.
	* @param X X-coordinate (default 0).
	* @param Y Y-coordinate (default 0).
	* @param Z Z-coordinate (default 0).
	*/
	MyPoint(double X = 0, double Y = 0,double Z = 0) :x(X), y(Y), z(Z) {}
	/**
	* @brief Computes the Euclidean distance to another point in 2D (ignoring Z).
	* @param p Target point.
	* @return Distance in XY-plane.
	*/
	double distanceTo_2D(const MyPoint& p)const;
	/**
	* @brief Computes the Euclidean distance to another point in 3D.
	* @param p Target point.
	* @return Full 3D distance.
	*/
	double distanceTo_3D(const MyPoint& p)const;
	/**
	* @brief Gets the X coordinate.
	* @return X value.
	*/
	double getX() const { return x; }
	/**
	* @brief Gets the Y coordinate.
	* @return Y value.
	*/
	double getY() const { return y; }
	/**
	* @brief Gets the Z coordinate.
	* @return Z value.
	*/
	double getZ() const { return z; }
	/**
	* @brief Sets the X coordinate.
	* @param val New X value.
	*/
	void setX(double val) { x = val; }
	/**
	* @brief Sets the Y coordinate.
	* @param val New Y value.
	*/
	void setY(double val) { y = val; }
	/**
	* @brief Sets the Z coordinate.
	* @param val New Z value.
	*/
	void setZ(double val) { z = val; }

};


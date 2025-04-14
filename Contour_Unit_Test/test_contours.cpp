/**
 * @file Contour2DTests.cpp
 * @brief Unit tests for the Contour2D class using Google Test framework.
 */

#include <gtest/gtest.h>
#include <vector>
#include <thread>
#include <future>
#include "Contour2D.h"
#include "LineSegment2D.h"
#include "ArcSegment2D.h"
#include "ContourUtils.h"
#include "MyPoint.h"

 /**
  * @test	CopyContour
  * @brief	Tests that a valid Contour2D can be copied correctly.
  */
TEST(ContourTest, CopyContour) {

	Contour2D c1, c2;
	//valid contour
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 5), MyPoint(5, 6)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));
	c2 = c1;

	EXPECT_EQ(c2.getSegmentCount(), 5);
	EXPECT_EQ(c1.getSegmentCount(), 5);
	EXPECT_TRUE(c1.isValid());
	EXPECT_TRUE(c2.isValid());
}

/**
 * @test	InsertRemoveContourSegment
 * @brief	Tests  removal and insertion of segments in a contour.
 */
TEST(ContourTest, InsertRemoveContourSegment) {
	Contour2D c1;

	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 5), MyPoint(5, 6)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));
	size_t count = c1.getSegmentCount();

	c1.removeSegment(3);
	EXPECT_TRUE(c1.getSegmentCount() < count);

	c1.insertSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(1, 1)), 0);
	EXPECT_TRUE(c1.getSegmentCount() == count);
}

/**
 * @test	ValidContour
 * @brief	Checks that a well-formed contour is marked as valid.
 */
TEST(ContourTest, ValidContour) {

	Contour2D validContour;

	validContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	validContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	validContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	validContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 5), MyPoint(5, 6)));
	validContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));

	EXPECT_TRUE(validContour.isValid());
}

/**
 * @test	InvalidContour_A
 * @brief	Contour with broken continuity (point jump) should be invalid.
 */

TEST(ContourTest, InvalidContour_A) {
	Contour2D invalidContour;

	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	//Next point start is offset 2 units on y axis
	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 7), MyPoint(5, 6)));
	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));

	EXPECT_FALSE(invalidContour.isValid());
}
/**
 * @test	InvalidContour_B
 * @brief	Contour with a reversed segment should be invalid.
 */
TEST(ContourTest, InvalidContour_B) {
	Contour2D invalidContour;

	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	//Next segment is reversed, but same point coordinates
	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(5, 5)));
	invalidContour.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));

	EXPECT_FALSE(invalidContour.isValid());
}

/**
 * @test	ValidContourClosedPolyline
 * @brief	Generates a valid closed contour from a polyline of points.
 */

TEST(ContourTest, ValidContourClosedPolyline) {
	std::vector<MyPoint> polyPoints;

	polyPoints.push_back(MyPoint(0, 0));
	polyPoints.push_back(MyPoint(1, 2));
	polyPoints.push_back(MyPoint(2, 1));
	polyPoints.push_back(MyPoint(4, 3));
	polyPoints.push_back(MyPoint(5, 7));

	Contour2D validPolylineContour = polylineContourFromPoints(polyPoints, true);
	EXPECT_TRUE(validPolylineContour.isValid());
}

/**
 * @test	ArcContour
 * @brief	Tests that Contour2D creation with a chain of ArcSegment2D is valid
 */
TEST(ContourTest, ArcContour) {

	Contour2D c1;
	//valid  ARC contour
	c1.addSegment(std::make_unique<ArcSegment2D>(MyPoint(1, 1), MyPoint(1, 2), 5, false));
	c1.addSegment(std::make_unique<ArcSegment2D>(MyPoint(1, 2), MyPoint(4, 2), 5, true));
	c1.addSegment(std::make_unique<ArcSegment2D>(MyPoint(4, 2), MyPoint(5, 5), 5, false));
	c1.addSegment(std::make_unique<ArcSegment2D>(MyPoint(5, 5), MyPoint(5, 6), 5, true));
	c1.addSegment(std::make_unique<ArcSegment2D>(MyPoint(5, 6), MyPoint(6, 7), 5, false));

	EXPECT_EQ(c1.getSegmentCount(), 5);
	EXPECT_TRUE(c1.isValid());
}

/**
 * @test	ArcLineContour
 * @brief	Tests that Contour2D creation with a chain of ArcSegment2D and LineSegment2D is valid
 */
TEST(ContourTest, ArcLineContour) {

	Contour2D c1;
	//valid  ARC-LINE contour
	c1.addSegment(std::make_unique<ArcSegment2D>(MyPoint(1, 1), MyPoint(1, 2), 5, false));
	c1.addSegment(std::make_unique<ArcSegment2D>(MyPoint(1, 2), MyPoint(4, 2), 5, true));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	c1.addSegment(std::make_unique<ArcSegment2D>(MyPoint(5, 5), MyPoint(5, 6), 5, true));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));

	EXPECT_EQ(c1.getSegmentCount(), 5);
	EXPECT_TRUE(c1.isValid());
}

/**
 * @brief			Helper function to filter valid contours.
 * @param contours	Vector of Contour2D objects.
 * @return			Vector of pointers to valid contours.
 */
std::vector<Contour2D*> findValidContours_test(std::vector<Contour2D>& contours) {
	std::vector<Contour2D*> result;
	for (auto& contour : contours) {
		if (contour.isValid())
			result.push_back(&contour);
	}
	return result;
}

/**
 * @brief			Helper function to filter invalid contours.
 * @param contours	Vector of Contour2D objects.
 * @return			Vector of pointers to invalid contours.
 */

std::vector<Contour2D*> findInvalidContours_test(std::vector<Contour2D>& contours) {
	std::vector<Contour2D*> result;
	for (auto& contour : contours) {
		if (!contour.isValid())
			result.push_back(&contour);
	}
	return result;
}

/**
 * @test	ValidInvalidContourSearch
 * @brief	Tests parallel filtering of valid/invalid contours and checks no duplicates are found.
 */

TEST(ContourTest, ValidInvalidContourSearch) {

	std::vector<Contour2D> contourVec;
	Contour2D c1;
	//valid contour
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 5), MyPoint(5, 6)));
	c1.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));
	contourVec.push_back(c1);
	EXPECT_TRUE(c1.isValid());
	Contour2D c2;
	//invalid contour
	c2.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	c2.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	c2.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	c2.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 5), MyPoint(8, 6)));
	c2.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));
	contourVec.push_back(c2);
	EXPECT_FALSE(c2.isValid());
	Contour2D c3;
	//invalid contour
	c3.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	c3.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	c3.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	c3.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(5, 6)));
	c3.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));
	contourVec.push_back(c3);
	EXPECT_FALSE(c3.isValid());
	Contour2D c4;
	//invalid contour
	c4.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 1), MyPoint(1, 2)));
	c4.addSegment(std::make_unique<LineSegment2D>(MyPoint(1, 2), MyPoint(4, 2)));
	c4.addSegment(std::make_unique<LineSegment2D>(MyPoint(4, 2), MyPoint(5, 5)));
	c4.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 4), MyPoint(5, 6)));
	c4.addSegment(std::make_unique<LineSegment2D>(MyPoint(5, 6), MyPoint(6, 7)));
	contourVec.push_back(c4);

	EXPECT_FALSE(c4.isValid());

	auto validFuture = std::async(std::launch::async, findValidContours_test, std::ref(contourVec));
	auto invalidFuture = std::async(std::launch::async, findInvalidContours_test, std::ref(contourVec));

	auto valid = validFuture.get();
	EXPECT_EQ(valid.size(), 1);
	std::cout << "Valid search done. Valid contours: " << valid.size() << std::endl;

	auto invalid = invalidFuture.get();
	EXPECT_EQ(invalid.size(), 3);
	std::cout << "Invalid search done. Invalid contours : " << invalid.size() << std::endl;

	EXPECT_TRUE(contourVec.size() == (valid.size() + invalid.size()));
	std::cout << "Total contours: " << contourVec.size() << std::endl;


	std::vector<Contour2D*> duplicates;

	for (auto va : valid) {

		for (auto inv : invalid) {

			if (va == inv) {
				duplicates.push_back(va);
			}
		}
	}

	EXPECT_EQ(duplicates.size(), 0);
	std::cout << "Duplicated contours: " << duplicates.size() << std::endl;

}

/**
 * @test	MoveContour
 * @brief	Validates that a contour is correctly translated by a delta offset.
 */

TEST(ContourTest, MoveContour) {
	std::vector<MyPoint> polyPoints;
	double deltax = 1, deltay = 2;
	polyPoints.push_back(MyPoint(0, 0));
	polyPoints.push_back(MyPoint(1, 2));
	polyPoints.push_back(MyPoint(2, 1));
	polyPoints.push_back(MyPoint(4, 3));
	polyPoints.push_back(MyPoint(5, 7));

	double x1, y1, x2, y2;
	Contour2D validPolylineContour = polylineContourFromPoints(polyPoints, false);

	for (size_t i = 0; i < validPolylineContour.getSegmentCount(); i++) {
		x1 = validPolylineContour.getSegmentAt(i).getPointA().getX();
		y1 = validPolylineContour.getSegmentAt(i).getPointA().getY();
		x2 = validPolylineContour.getSegmentAt(i).getPointB().getX();
		y2 = validPolylineContour.getSegmentAt(i).getPointB().getY();
		std::cout << "A - Old X: " << x1 << " Old Y: " << y1 << " B - Old X: " << x2 << " Old Y: " << y2 << std::endl;
	}
	auto it1 = validPolylineContour.begin();
	double fx1 = it1->get()->getPointA().getX();
	double fy1 = it1->get()->getPointA().getY();

	validPolylineContour.move(deltax, deltay);
	for (size_t i = 0; i < validPolylineContour.getSegmentCount(); i++) {

		x1 = validPolylineContour.getSegmentAt(i).getPointA().getX();
		y1 = validPolylineContour.getSegmentAt(i).getPointA().getY();
		x2 = validPolylineContour.getSegmentAt(i).getPointB().getX();
		y2 = validPolylineContour.getSegmentAt(i).getPointB().getY();

		std::cout << "A - New X: " << x1 << " New Y: " << y1 << " B - New X: " << x2 << " New Y: " << y2 << std::endl;
	}
	auto it2 = validPolylineContour.begin();
	double fx2 = it2->get()->getPointA().getX();
	double fy2 = it2->get()->getPointA().getY();

	EXPECT_TRUE((fx1 + deltax) == fx2);
	EXPECT_TRUE((fy1 + deltay) == fy2);
	EXPECT_TRUE(validPolylineContour.isValid());
}


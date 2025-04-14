

#include <iostream>
#include "Contour2D.h"
#include "LineSegment2D.h"
#include "ArcSegment2D.h"
#include "ContourUtils.h"

int main()
{
    std::cout << "Hello World!\n";

    Contour2D myContour;
   
    LineSegment2D s1(MyPoint(0, 0), MyPoint(0, 10)), s2(MyPoint(0, 10), MyPoint(10, 10)), s3(MyPoint(10, 10), MyPoint(10, 0));
    myContour.addSegment(s1);
    myContour.addSegment(s2);
    myContour.addSegment(s3);

  
    // Check validity
    if (myContour.isValid()) {
        std::cout << "Contour is valid!" << std::endl;
    }
    else {
        std::cout << "Contour is invalid..." << std::endl;
    }

    // Remove the second segment
    myContour.removeSegment(1);

    std::vector<MyPoint> polyPoints;

    polyPoints.push_back(MyPoint(0, 0));
    polyPoints.push_back(MyPoint(1, 2));
    polyPoints.push_back(MyPoint(2, 1));
    polyPoints.push_back(MyPoint(4, 3));
    polyPoints.push_back(MyPoint(5, 7));

    Contour2D test=polylineContourFromPoints(polyPoints, false);

    std::cout << "Contour closed shape: " << test.isClosedShape();

    return 0;
}
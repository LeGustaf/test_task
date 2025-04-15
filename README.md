# 2D Contour Test Task

A lightweight, modular C++ library for representing and manipulating 2D contours made of line and arc segments.  
Includes full Doxygen documentation and unit tests.

## Features

- `Contour2D`: A flexible container for line/arc segments
- `LineSegment2D` and `ArcSegment2D`: Derive from a shared `Segment2D` interface
- `MyPoint`: Simple 3D point class with 2D/3D distance methods
- Utility to build polylines from a point list
- Caching-based contour validity checks
- Fully documented with Doxygen

## Getting started
This project is built with standard C++14 and tested with Visual Studio 2022.
To build:

1. Open the `.sln` file in Visual Studio
2. Select `Build → Build Solution` or press `Ctrl+Shift+B`

No external dependencies are required.
Unit tests are located in the `Contour_Unit_Test/` project and use Google Test.
To run:

1. Set the unit test project as the startup project
2. Press `F5` to build and run all tests


## Documentation

> Documentation is generated with Doxygen and available in the `docs/html` folder.

UML Diagram
[UML Diagram](docs/UML_2_0.png)

[View Documentation for 2D Contour](https://legustaf.github.io/test_task/2D_Contour/)

[View Documentation for Unit Testing](https://legustaf.github.io/test_task/Unit_Test/)
 
You can open it locally:
```sh
docs/2D_Contour/index.html
docs/Unit_Test/index.html

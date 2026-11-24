*This project has been created as part of the 42 curriculum by acasper, rrajni*

# miniRT

## Description
miniRT is a ray tracer written in C using MiniLibX. It renders three-dimensional scenes defined in .rt files, supporting cameras, ambient and diffuse lighting, hard shadows, spheres, planes and cylinders.

This project explores the fundamentals of computer graphics, including vector mathematics, ray-object intersections, surface normals, lighting calculations, scene parsing and image rendering.

## Instructions

### Requirements

This project requires:

- A C compiler
- `make`
- MiniLibX and its platform dependencies

On macOS, the included MiniLibX implementation uses the OpenGL and AppKit
frameworks.

On Linux, MiniLibX requires X11 development libraries, including `libXext`
and `libX11`.

### Compilation

Compile the program with:

```sh
make
Other available Makefile rules are:
make clean
make fclean
make re
Execution
Run the program with one .rt scene file:
./miniRT scenes/valid/basic.rt
The program accepts exactly one scene file with the .rt extension.

Press ESC, or close the window using its close button, to exit cleanly.
Scene format
A scene may contain the following elements:
Identifier	Element
A	Ambient lighting
C	Camera
L	Point light
sp	Sphere
pl	Plane
cy	Cylinder


Example:
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
Invalid scene configurations cause the program to exit with Error followed
by an explanatory message.

## Resources

Ray Tracing in 5 minutes
https://www.youtube.com/watch?v=H5TB2l7zq6s
Ray Tracing in 5 minutes: Part 2 -- implementing a basic ray tracer
https://www.youtube.com/watch?v=mTOllvinv-U
Ray Tracing in 5 minutes: Part 3 -- recursive ray tracing
https://www.youtube.com/watch?v=tUh6gCx08LI
Ray Tracing in One Weekend
https://raytracing.github.io/books/RayTracingInOneWeekend.html
MiniLibX documentation
https://harm-smits.github.io/42docs/libs/minilibx

## Use of AI

AI tools were used to accelerate learning, assist with debugging, and troubleshoot implementation issues throughout development.

This included help with understanding ray-tracing concepts, identifying edge cases, and reviewing technical topics related to scene parsing, vector mathematics, ray-object intersections, lighting, shadows, and memory management.

All final code, implementation decisions, and integration work were completed manually.

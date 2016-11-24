 #include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include "Matrix3.h"

using namespace std;
using namespace sf;
using namespace custom;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	const int primatives;

	GLuint index;
	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;
	custom::Vector_3 vector;
	custom::Matrix_3 matrix;
};
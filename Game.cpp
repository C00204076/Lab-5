#include "Game.h"

bool flip = false;
int current = 1;

custom::Matrix_3 rotatedmatrix, translatedmatrix;
custom::Vector_3 triangle1v1, triangle1v2, triangle1v3, triangle2v1, triangle2v2, triangle2v3;

Game::Game() : window(VideoMode(800, 600), "OpenGL"), primatives(2)
{
	index = glGenLists(primatives);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){


		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();


	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	//
	triangle1v1.setX(custom::Vector_3(0.0, 2.0, -5.0));
	triangle1v2.setX(custom::Vector_3(-2.0, -2.0, -5.0));
	triangle1v3.setX(custom::Vector_3(2.0, -2.0, -5.0));
	//
	triangle1v1.setY(custom::Vector_3(0.0, 2.0, -5.0));
	triangle1v2.setY(custom::Vector_3(-2.0, -2.0, -5.0));
	triangle1v3.setY(custom::Vector_3(2.0, -2.0, -5.0));
	//
	triangle1v1.setZ(custom::Vector_3(0.0, 2.0, -5.0));
	triangle1v2.setZ(custom::Vector_3(-2.0, -2.0, -5.0));
	triangle1v3.setZ(custom::Vector_3(2.0, -2.0, -5.0));



	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(triangle1v1.getX(), triangle1v1.getY(), triangle1v1.getZ());
		glVertex3f(triangle1v2.getX(), triangle1v2.getY(), triangle1v2.getZ());
		glVertex3f(triangle1v3.getX(), triangle1v3.getY(), triangle1v3.getZ());
		
	}
	glEnd();
	glEndList();

	//
	triangle2v1.setX(custom::Vector_3(0.2, 0.0, -2.0));
	triangle2v2.setX(custom::Vector_3(-2.0, -2.0, -2.0));
	triangle2v3.setX(custom::Vector_3(2.0, -2.0, -2.0));
	//		
	triangle2v1.setY(custom::Vector_3(0.2, 0.0, -2.0));
	triangle2v2.setY(custom::Vector_3(-2.0, -2.0, -2.0));
	triangle2v3.setY(custom::Vector_3(2.0, -2.0, -2.0));
	//		
	triangle2v1.setZ(custom::Vector_3(0.2, 0.0, -2.0));
	triangle2v2.setZ(custom::Vector_3(-2.0, -2.0, -2.0));
	triangle2v3.setZ(custom::Vector_3(2.0, -2.0, -2.0));

	glNewList(index + 1, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(triangle2v1.getX(), triangle2v1.getY(), triangle2v1.getZ());
		glVertex3f(triangle2v2.getX(), triangle2v2.getY(), triangle2v2.getZ());
		glVertex3f(triangle2v3.getX(), triangle2v3.getY(), triangle2v3.getZ());
	}
	glEnd();
	glEndList();

	translatedmatrix = translatedmatrix.Translate(1, 0);

	triangle1v1 = triangle1v1 * translatedmatrix;
	triangle1v2 = triangle1v2 * translatedmatrix;
	triangle1v3 = triangle1v3 * translatedmatrix;
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
			current++;
			if (current > primatives)
			{
				current = 1;
			}
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Draw up" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Investigate Here!!!!!
	glLoadIdentity();


	//matrix.Rotation(rotationAngle);
	//matrix.RotationX(rotationAngle);
	//matrix.RotationY(rotationAngle);
	//matrix.RotationZ(rotationAngle);
	//matrix.Translate();
	//matrix.Scale();

	rotatedmatrix = rotatedmatrix.Rotation(12);

	triangle1v1 = triangle1v1 * rotatedmatrix;
	triangle1v2 = triangle1v2 * rotatedmatrix;
	triangle1v3 = triangle1v3 * rotatedmatrix;


	triangle2v1 = triangle2v1 * rotatedmatrix;
	triangle2v2 = triangle2v2 * rotatedmatrix;
	triangle2v3 = triangle2v3 * rotatedmatrix;
	

	cout << "Drawing Primative " << current << endl;
	glCallList(current);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}


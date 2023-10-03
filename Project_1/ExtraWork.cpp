#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>
#include <list>

using namespace std;
using namespace sf;

void DrawPreviousLines(RenderWindow& window, list<Vertex>& drawnPoints);

int main2()
{
	// create the window
	RenderWindow window(VideoMode(800, 600), "Nick's Window");

	//red clicking line
	bool isDrawing = false;
	Vertex line[] =
	{
		Vertex(Vector2f(0,0), Color::Red),
		Vertex(Vector2f(0,0), Color::Red)
	};

	//previously drawn lines
	list<Vertex> drawnPoints;

	//Rendering Loop
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(Color::Black);

		//if the player wants to draw
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i currentMousePos = Mouse::getPosition(window);

			//draw the point that the mouse is currently at
			if (isDrawing)
			{
				line[1].position.x = currentMousePos.x;
				line[1].position.y = currentMousePos.y;

				window.draw(line, 2, Lines);
			}
			//draw the initial point that the mouse started clicking
			else
			{
				line[0].position.x = currentMousePos.x;
				line[0].position.y = currentMousePos.y;

				isDrawing = true;
			}
		}
		//if the player wants to erase
		else if (Mouse::isButtonPressed(Mouse::Right))
		{
			drawnPoints.clear();
		}
		//else, push the newly drawn line to the previously drawn lines
		else
		{
			//this means i finished drawing
			if (isDrawing)
			{
				Vertex newLine[]
				{
					Vertex(Vector2f(line[0].position.x, line[0].position.y), Color::White),
					Vertex(Vector2f(line[1].position.x, line[1].position.y), Color::White)
				};

				drawnPoints.push_back(newLine[0]);
				drawnPoints.push_back(newLine[1]);

				isDrawing = false;

				//USE FOR TESTING - DELETE LATER
				//cout << "finished drawing line!" << endl;
			}
		}

		//draw previous lines
		DrawPreviousLines(window, drawnPoints);

		// end the current frame
		window.display();
	}

	//free up allocated memory
	drawnPoints.clear();
	return 0;
}

//this helper function draws the old lines to the screen
void DrawPreviousLines(RenderWindow& window, list<Vertex>& drawnPoints)
{
	list<Vertex>::iterator it = drawnPoints.begin();

	for (int i = 1; i < drawnPoints.size();)
	{
		//create line
		Vertex tempLine[2];
		tempLine[0] = *it;
		advance(it, 1);
		tempLine[1] = *it;

		//draw new line
		window.draw(tempLine, 2, Lines);

		//inciment counters
		advance(it, 1);
		i += 2;
	}
	return;
}



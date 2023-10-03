#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace std;
using namespace sf;

int main()
{
	// create the window
	RenderWindow window(VideoMode(800, 600), "Nick's Window");
	
	//current point
	Vertex currentPoint;
	currentPoint.color = Color::Green;

	//last point
	Vertex lastPoint;
	lastPoint.color = Color::Green;

	//managing drawing
	bool isDrawing;

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

		//if the player wants to draw
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i currentMousePos = Mouse::getPosition(window);

			if (isDrawing)
			{
				currentPoint.position = Vector2f(currentMousePos);

				sf::Vertex line[] =
				{
					currentPoint,
					lastPoint
				};

				window.draw(line, 2, Lines);

				lastPoint = currentPoint;
			}
			else
			{
				lastPoint.position = Vector2f(currentMousePos);
				isDrawing = true;
			}
			

			
		}
		//if the player wants to erase
		else if (Mouse::isButtonPressed(Mouse::Right))
		{
			// clear the window with black color
			window.clear(Color::Black);
		}
		else
		{
			isDrawing = false;
		}

		// end the current frame
		window.display();
	}

	//free up allocated memory
	return 0;
}

// Worked: Alex Shevchenko and Ivan Makovetskyi

// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Text infoText;

	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	infoText.setFont(font);
	infoText.setString("You need to click on 3 places this will create \n the 3 vertecies and then you need to pick initial point");
	infoText.setCharacterSize(25);
	infoText.setFillColor(Color::White);
	infoText.setPosition(50.f,50.f);

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
				infoText.setString("Now it's working:");
				points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.

			for (int i = 0; i < 10; i++)
			{
				int randNum = rand() % 3;
				Vector2f lastPoint = points.back();
				Vector2f vertex = vertices.at(randNum);

				Vector2f newPoint((lastPoint.x + vertex.x) / 2, (lastPoint.y + vertex.y) /2);
				points.push_back(newPoint);
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(infoText);

		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		
		for(int i = 0; i < points.size(); i++)
		{
		    RectangleShape dot(Vector2f(2,2));
		    dot.setPosition(Vector2f(points[i].x, points[i].y));
		    dot.setFillColor(Color::Green);
		    window.draw(dot);
		}
		window.display();
	}
}

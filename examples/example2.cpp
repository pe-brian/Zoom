////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Zoost/Geom.hpp>
#include <Zoom/Shape.hpp>
#include <Zoost/Converter.hpp>

using namespace zin;

////////////////////////////////////////////////////////////
/// Entry point of the application
////////////////////////////////////////////////////////////
int main()
{
	sf::RenderWindow App(sf::VideoMode(1000, 700, 32), "Zoom example 2");

	bool switched = false;

	Geom heart = Geom::polygon({{120, 60}, {140, 20}, {180, 0}, {220, 20}, {240, 80}, {220, 140}, {180, 180}, {120, 200}, {60, 180}, {20, 140}, {0, 80}, {20, 20}, {60, 0}, {100, 20}});
	heart.setPosition(200, 100);
	heart.scale(1.5, 1.5);

	Shape heartShape(heart);
	heartShape.setFacesColor(Color::IndianRed);
	heartShape.setLiaisonsColor(Color::Red);
	heartShape.setLiaisonsWidth(3);

	Geom snake = Geom::polygon({{0, 0}, {25, 100}, {40, 100}, {40, 0}, {100, 0}, {100, 100}, {120, 100}, {120, 0}, {180, 0}, {180, 100}, {200, 100}, {200, 0}, {260, 0}, {260, 100}, {275, 100}, {300, 0}, {300, 120}, {240, 120}, {240, 20}, {220, 20}, {220, 120}, {160, 120}, {160, 20}, {140, 20}, {140, 120}, {80, 120}, {80, 20}, {60, 20}, {60, 120}, {0, 120}});
	snake.setPosition(130, 200);
	snake.scale(1.5, 1.5);

	Shape snakeShape(snake);
	snakeShape.setFacesColor(Color::SpringGreen);
	snakeShape.setLiaisonsColor(Color::DarkGreen);
	snakeShape.setLiaisonsWidth(3);

	while( App.isOpen() )
	{
		sf::Event Event;
	
		while( App.pollEvent(Event) )
		{
			if( Event.type == sf::Event::Closed )
				App.close();

			else if( Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape )
				App.close();

			else if( Event.type == sf::Event::MouseWheelMoved )
			{
				switched = !switched;

				switched ?
				
				snakeShape.setDebugMode(snake.contains(Coords(Event.mouseWheel.x, Event.mouseWheel.y))) :
				heartShape.setDebugMode(heart.contains(Coords(Event.mouseWheel.x, Event.mouseWheel.y)));
			}

			else if( Event.type == sf::Event::MouseMoved )

				switched ?
				
				snakeShape.setDebugMode(snake.contains(Coords(Event.mouseMove.x, Event.mouseMove.y))) :
				heartShape.setDebugMode(heart.contains(Coords(Event.mouseMove.x, Event.mouseMove.y)));
		}
	
		App.clear(sf::Color(30, 30, 30));
	    App.draw(switched ? snakeShape : heartShape);
		App.display();
	}
	
	return EXIT_SUCCESS;
}
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
	sf::Text text;
	bool switched = false;

	Shape::debugModeEnabled = false;

	Geom geom1 = Geom::polygon({{120, 60}, {140, 20}, {180, 0}, {220, 20}, {240, 80}, {220, 140}, {180, 180}, {120, 200}, {60, 180}, {20, 140}, {0, 80}, {20, 20}, {60, 0}, {100, 20}});
	geom1.setPosition(200, 100);
	geom1.scale(1.5, 1.5);

	Shape shape1(geom1);
	shape1.setFillColor(Color::IndianRed);
	shape1.setOutlineColor(Color::Red);
	shape1.setOutlineWidth(3);

	Geom geom2 = Geom::polygon({{0, 0}, {25, 100}, {40, 100}, {40, 0}, {100, 0}, {100, 100}, {120, 100}, {120, 0}, {180, 0}, {180, 100}, {200, 100}, {200, 0}, {260, 0}, {260, 100}, {275, 100}, {300, 0}, {300, 120}, {240, 120}, {240, 20}, {220, 20}, {220, 120}, {160, 120}, {160, 20}, {140, 20}, {140, 120}, {80, 120}, {80, 20}, {60, 20}, {60, 120}, {0, 120}});
	geom2.setPosition(130, 200);
	geom2.scale(1.5, 1.5);

	Shape shape2(geom2);
	shape2.setFillColor(Color::SpringGreen);
	shape2.setOutlineColor(Color::DarkGreen);
	shape2.setOutlineWidth(3);

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
				Shape::debugModeEnabled = switched ? geom2.contains(Coords(Event.mouseWheel.x, Event.mouseWheel.y)) : geom1.contains(Coords(Event.mouseWheel.x, Event.mouseWheel.y));
			}

			else if( Event.type == sf::Event::MouseMoved )
				  Shape::debugModeEnabled = switched ? geom2.contains(Coords(Event.mouseMove.x, Event.mouseMove.y)) : geom1.contains(Coords(Event.mouseMove.x, Event.mouseMove.y));
		}
	
		App.clear(sf::Color(30, 30, 30));
	    App.draw(switched ? shape2 : shape1);
	    App.draw(text);
		App.display();
	}
	
	return EXIT_SUCCESS;
}
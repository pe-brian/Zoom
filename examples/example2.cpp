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
	sf::RenderWindow app(sf::VideoMode(1000, 700, 32), "Zoom example 2");
	app.setVerticalSyncEnabled(true);

	unsigned int frame = 0;

	Geom heart = Geom::polygon({{120, 60}, {140, 20}, {180, 0}, {220, 20}, {240, 80}, {220, 140}, {180, 180}, {120, 200}, {60, 180}, {20, 140}, {0, 80}, {20, 20}, {60, 0}, {100, 20}});
	heart.setPosition(200, 100);
	heart.scale(1.5, 1.5);

	Shape heartShape(heart);
	heartShape.setFacesColor(Color::IndianRed);
	heartShape.setLiaisonsColor(Color::White);

	Geom snake = Geom::polygon({{0, 0}, {25, 100}, {40, 100}, {40, 0}, {100, 0}, {100, 100}, {120, 100}, {120, 0}, {180, 0}, {180, 100}, {200, 100}, {200, 0}, {260, 0}, {260, 100}, {275, 100}, {300, 0}, {300, 120}, {240, 120}, {240, 20}, {220, 20}, {220, 120}, {160, 120}, {160, 20}, {140, 20}, {140, 120}, {80, 120}, {80, 20}, {60, 20}, {60, 120}, {0, 120}});
	snake.setPosition(130, 200);
	snake.scale(1.5, 1.5);

	Shape snakeShape(snake);
	snakeShape.setFacesColor(Color::SpringGreen);
	snakeShape.setLiaisonsColor(Color::White);

	Geom rectangle = Geom::rectangle({200, 200}, {400, 600}, 40);

	Shape rectangleShape(rectangle);
	rectangleShape.setFacesColor(Color::Blue);
	rectangleShape.setLiaisonsColor(Color::White);

	while( app.isOpen() )
	{
		sf::Event event;
	
		while( app.pollEvent(event) )
		{
			if( event.type == sf::Event::Closed )
				app.close();

			else if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape )
				app.close();

			else if( event.type == sf::Event::MouseWheelMoved )
			{
				if( frame < 2 )
					frame++;
				else frame = 0;

				if( frame == 0 )
					heartShape.setDebugMode(heart.contains(Coords(event.mouseWheel.x, event.mouseWheel.y)));

				else if( frame == 1 )
					snakeShape.setDebugMode(snake.contains(Coords(event.mouseWheel.x, event.mouseWheel.y)));

				else rectangleShape.setDebugMode(rectangle.contains(Coords(event.mouseWheel.x, event.mouseWheel.y)));
			}

			else if( event.type == sf::Event::MouseMoved )
			{
				if( frame == 0 )
					heartShape.setDebugMode(heart.contains(Coords(event.mouseMove.x, event.mouseMove.y)));

				else if( frame == 1 )
					snakeShape.setDebugMode(snake.contains(Coords(event.mouseMove.x, event.mouseMove.y)));

				else rectangleShape.setDebugMode(rectangle.contains(Coords(event.mouseMove.x, event.mouseMove.y)));
			}
		}
	
		app.clear(sf::Color(30, 30, 30));

	    if( frame == 0 )
	    	app.draw(heartShape);

	    else if( frame == 1 )
	    	app.draw(snakeShape);

	    else app.draw(rectangleShape);

		app.display();
	}
	
	return EXIT_SUCCESS;
}
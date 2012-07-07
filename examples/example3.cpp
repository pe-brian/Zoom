////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Zoost/Geom.hpp>
#include <Zoost/Converter.hpp>
#include <Zoom/Shape.hpp>
#include <Zoom/Light.hpp>
#include <Zoom/Spot.hpp>
#include <Zoom/LightManager.hpp>
#include <Zoom/Variation.hpp>

using namespace zin;

////////////////////////////////////////////////////////////
/// Entry point of the application
////////////////////////////////////////////////////////////
int main()
{
	sf::RenderWindow app(sf::VideoMode(800, 600, 32), "Zoom example 3");
	app.setVerticalSyncEnabled(true);
	
	sf::Mouse::setPosition({400, 0});
	sf::Clock clock;

	Geom geom = Geom::segment({100, 100}, {125, 125})
			  + Geom::segment({300, 200}, {450, 325})
			  + Geom::segment({250, 245}, {400, 365})
			  + Geom::segment({500, 200}, {600, 300})
			  + Geom::segment({125, 430}, {125, 475})
			  + Geom::segment({500, 300}, {600, 200})
			  + Geom::segment({125, 475}, {175, 475});
	
	Shape shape(geom);
	shape.setLiaisonsWidth(3);
	shape.setLiaisonsColor(Color::White);

	LightManager lightManager;

	Light light(150, Color::Green);
	light.setPosition({400, 0});

	Spot spot(400, toRads(45), Color(190, 150, 150));
	spot.setPosition({700, 400});

	lightManager.attach(light);
	lightManager.attach(spot);
	lightManager.attach(geom);

	Variation<double> angle(toRads(180), toRads(225), toRads(20), 0, true, true);

	while( app.isOpen() )
	{
		sf::Event event;
	
		while( app.pollEvent(event) )
		{		
			if( event.type == sf::Event::Closed )
				app.close();
		
			else if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape )
				app.close();
		
			else if( event.type == sf::Event::MouseButtonPressed )
				lightManager.setDebugMode(!lightManager.getDebugMode());

			else if( event.type == sf::Event::MouseMoved )
				light.setPosition(event.mouseMove.x, event.mouseMove.y);
		}

		sf::Time timeStep = clock.restart();

		lightManager.update();
		spot.setRotation(angle.update(timeStep));
	
		app.clear();
		app.draw(shape);
		app.draw(lightManager);

		app.display();
	}
	
	return EXIT_SUCCESS;
}
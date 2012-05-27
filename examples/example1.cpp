////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Zoost/Geom.hpp>
#include <Zoost/Converter.hpp>
#include <Zoom/Kinetic.hpp>
#include <Zoom/Shape.hpp>
#include <Zoom/Variation.hpp>

using namespace zin;

////////////////////////////////////////////////////////////
/// Entry point of the application
////////////////////////////////////////////////////////////
int main()
{
   sf::RenderWindow App(sf::VideoMode(1000, 700, 32), "Zoom example 1");

   sf::Clock clock;

   Curve curve = Curve::bezier({767, 410, 1000, 900, 1000, 30, 500, 30, 1, 30, 50, 560, 169, 410}) + Curve({169, 410, 228, 321, 386, 571, 553, 261, 421, 218, 575, 464, 767, 410});
   curve.setOrigin(500, 370);

   Shape shape1(curve);
   shape1.setVertexColor(Color::Green);
   shape1.setLiaisonWidth(1);
   
   Geom geom2 = Geom::star({0, 0}, 0, 30, 60, 20);

   Shape shape2(geom2);
   shape2.showLiaison(false);
   shape2.setFaceColor(Color::Yellow);

   Kinetic kinetic(curve, 400, 0, true);
   
   Variation<double> var1(0.4, 1, 0.2, 0, true, true);
   Variation<double> var2(0, 6.28318531, 0.2, 0, true);

   while( App.isOpen() )
   {
      sf::Event Event;
   
      while( App.pollEvent(Event) )
      {     
         if( Event.type == sf::Event::Closed )
            App.close();
      
         else if( Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape )
            App.close();

         else if( Event.type == sf::Event::MouseButtonPressed  )
            Shape::debugModeEnabled = !Shape::debugModeEnabled;
      }

      sf::Time timeStep = clock.restart();

      double scale = var1.update(timeStep);
      geom2.setPosition(curve.convertToGlobal(kinetic.update(timeStep)));
      geom2.setScale(scale, scale);
      curve.setRotation(var2.update(timeStep));
      curve.setScale(scale, scale);

      App.clear(sf::Color(30, 30, 30));
      App.draw(shape1);
      App.draw(shape2);
      App.display();
   }
   
   return EXIT_SUCCESS;
}
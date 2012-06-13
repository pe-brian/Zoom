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
   App.setVerticalSyncEnabled(true);

   sf::Clock clock;

   Curve curve = Curve::bezier({{767, 410}, {1000, 900}, {1000, 30}, {500, 30}, {1, 30}, {50, 560}, {169, 410}})
               + Curve({{169, 410}, {228, 321}, {386, 571}, {553, 261}, {421, 218}, {575, 464}, {767, 410}});
   curve.setOrigin(500, 370);

   Shape curveShape(curve);
   curveShape.setVerticesColor(Color::Green);
   curveShape.setLiaisonsWidth(1);
   
   Geom star = Geom::star(30, 60, 20);

   Shape starShape(star);
   starShape.showLiaisons(false);
   starShape.setFacesColor(Color::Yellow);

   Kinetic kinetic(curve, 400, 0, true);  
   
   Variation<double> scaleVariation(.4, 1, .2, 0, true, true);
   Variation<double> angleVariation(0, toRads(360), toRads(15), 0, true);

   while( App.isOpen() )
   {
      sf::Event Event;
   
      while( App.pollEvent(Event) )
      {     
         if( Event.type == sf::Event::Closed )
            App.close();
      
         else if( Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape )
            App.close();

         else if( Event.type == sf::Event::MouseButtonPressed )
         {
            curveShape.setDebugMode(!curveShape.getDebugMode());
            starShape.setDebugMode(!starShape.getDebugMode());
         }
      }

      sf::Time timeStep = clock.restart();

      double scale = scaleVariation.update(timeStep);
      Vector2d pos = curve.convertToGlobal(kinetic.update(timeStep));

      star.setPosition(pos);
      star.setScale(scale, scale);

      curve.setRotation(angleVariation.update(timeStep));
      curve.setScale(scale, scale);

      App.clear(sf::Color(30, 30, 30));
      App.draw(curveShape);
      App.draw(starShape);
      App.display();
   }
   
   return EXIT_SUCCESS;
}
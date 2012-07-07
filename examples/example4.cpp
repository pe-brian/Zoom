////////////////////////////////////////////////////////////
// Many thanks for Naisse Grégoire
// the original author of this code
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>
#include <SFML/OpenGL.hpp>
#include <Zoom/Sprite3d.hpp>

using namespace zin;

#define M_PI 3.14159265359
#define M_PI_2 M_PI / 2
#define M_PI_4 M_PI / 4

////////////////////////////////////////////////////////////
/// Entry point of the application
////////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow app(sf::VideoMode(1024, 768), "Zoom example 4");
    app.setVerticalSyncEnabled(true);

    unsigned int noScreen = 0;

    sf::View camera(sf::Vector2f(app.getSize().x / 2, app.getSize().y / 2), sf::Vector2f(app.getSize().x, app.getSize().y));
    app.setView(camera);

    Sprite3d reed1, reed2;
    reed1.load("data/reed-color.png", "data/reed-normal.png", "data/reed-heightmap.png");
    reed2.load("data/reed-color.png", "data/reed-normal.png", "data/reed-heightmap.png");

    Sprite3d cave;
    cave.load("data/cave-color.png", "data/cave-normal.png", "data/cave-heightmap.png");
    cave.height = 100;
    cave.setPosition(2000, 1000);

    Sprite3d abbey;
    abbey.load("data/abbey_color.png", "data/abbey_normal.png", "data/abbey_heightmap.png");
    //abbey.height = 394;// * 2.0 / sqrt(3);// * 255 / 221;
    //abbey.height = 310;// * 2.0 / sqrt(3);// * 255 / 221;
    abbey.height = 460;// * 2.0 / sqrt(3);// * 255 / 221;
    abbey.height = 385;// * 2.0 / sqrt(3);// * 255 / 221;
    abbey.setPosition(-500, -300, 0);

    Sprite3d abbey2 = abbey;
    abbey2.setPosition(5000, 3000, 0);
    abbey2.scale(-1, 1);
    abbey2.setOrigin(1920, 0);

    Sprite3d roughGrass;
    roughGrass.load("data/rough_grass_color.png", "data/rough_grass_normal.png", "data/rough_grass_heightmap.png");
    roughGrass.setTextureRect(sf::IntRect(0, 0, 5000, 5000));
    roughGrass.setPosition(-400, -300, 0/*-10*/);
    roughGrass.height = 16;

    Sprite3d fir;
    fir.load("data/fir_color.png", "data/fir_normal.png", "data/fir_heightmap.png");
    fir.setPosition(600,400);
    fir.height = 240;

    Sprite3d oak;
    oak.load("data/oak_color.png", "data/oak_normal.png", "data/oak_heightmap.png");
    oak.setPosition(700, 450);
    oak.height = 240;

    reed1.setPosition(500, 500);
    reed2.setPosition(550, 530);
    reed1.scale(0.75, 0.75);
    reed2.scale(0.8, 0.8);

    reed1.height = 80 * 2.0 / sqrt(3);
    reed2.height = 80 * 2.0 / sqrt(3);

    ShaderPack pack(app);

    sf::Vector3f lightPos(0,0,200);

    pack.screen.setActive(true);

    /*glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);*/

    GLfloat position1[] = { 700.0, 600.0, 200.0, 1.0f };
    GLfloat position2[] = { 200.0, 750.0, 50.0, 1.0f };
    GLfloat position3[] = { 0.0, 0.0, 0.0, 0.0f };
    GLfloat color0[] = { 1.0, 1.0, 1.0, 1.0f };
    GLfloat color1[] = { 1.0, 0.0, 0.0, 1.0f };
    GLfloat color2[] = { 0.0, 0.5, 1.0, 1.0f };
    GLfloat color3[] = { 1.0, 1.0, 0.75, 1.0f };

    float sunAngle = M_PI_4;
    float sunAngle2 = 3.5/5;

    pack.normalShader.setParameter("NBR_LIGHTS", 4);

    position3[0] = -cos(sunAngle) * cos(sunAngle2);
    position3[1] = -sin(sunAngle) * cos(sunAngle2);
    position3[2] = -sin(sunAngle2);

    GLfloat a[] = {0.00001};


    GLfloat p[4] = {lightPos.x,  lightPos.y*2,  lightPos.z, 1.0f};
    glLightfv(GL_LIGHT3, GL_POSITION, p);

    glLightfv(GL_LIGHT3, GL_DIFFUSE, color0);
    glLightfv(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, a);

    a[0] = 0.00002;

    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color1);
    glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, a);


    a[0] = 0.00002;

    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, color2);
    glLightfv(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, a);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, color3);

    {
        sf::Vector3f light(position3[0], position3[1], position3[2]);
        abbey.generateAmbientShadow(app, pack, light);
        abbey2.generateAmbientShadow(app, pack, light);
        fir.generateAmbientShadow(app, pack, light);
        oak.generateAmbientShadow(app, pack, light);
    }

    sf::Clock clock;

    while( app.isOpen() )
    {
        sf::Event event;

        while( app.pollEvent(event) )
        {
            if(event.type == sf::Event::Closed)
                app.close();

            if( event.type == sf::Event::KeyReleased )
            {
                if(event.key.code == sf::Keyboard::Q
                || event.key.code == sf::Keyboard::D
                || event.key.code == sf::Keyboard::Z
                || event.key.code == sf::Keyboard::S)
                {
                    sf::Vector3f light(position3[0], position3[1], position3[2]);
                    abbey.generateAmbientShadow(app, pack, light);
                    abbey2.generateAmbientShadow(app, pack, light);
                    fir.generateAmbientShadow(app, pack, light);
                    oak.generateAmbientShadow(app, pack, light);
                    reed1.generateAmbientShadow(app, pack, light);
                    reed2.generateAmbientShadow(app, pack, light);
                }
            }

            if( event.type == sf::Event::KeyPressed )
            {
                std::ostringstream buf;

                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        app.close();
                        break;

                    case sf::Keyboard::Up:
                        lightPos.z-=5;
                        //abbey.height+=5;
                        //std::cout<<abbey.height<<std::endl;
                        break;

                    case sf::Keyboard::Down:
                        lightPos.z+=5;
                        //abbey.height-=5;
                        //std::cout<<abbey.height<<std::endl;
                        break;

                    case sf::Keyboard::Z:
                        sunAngle2+=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        break;

                    case sf::Keyboard::S:
                        sunAngle2-=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        break;

                    case sf::Keyboard::Q:
                        sunAngle-=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        break;

                    case sf::Keyboard::D:
                        sunAngle+=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        break;

                    case sf::Keyboard::R:
                        color3[3]+=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        color3[0]+=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        color3[1]+=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        color3[2]-=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        break;
                    case sf::Keyboard::F:
                        color3[3]-=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        color3[0]-=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        color3[1]-=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        color3[2]+=(float)clock.getElapsedTime().asMilliseconds() * 0.001;
                        break;

                    case sf::Keyboard::P:
                        buf << "Screens/screenshot" << noScreen << ".png";
                        app.capture().saveToFile(buf.str());
                        noScreen++;
                        break;

                    default:
                        break;
                }
            }

            if( event.type == sf::Event::MouseButtonPressed )
            {
                if( event.mouseButton.button == sf::Mouse::Left )
                    oak.setPosition((float)sf::Mouse::getPosition(app).x + camera.getCenter().x - camera.getSize().x / 2 - oak.getGlobalBounds().width / 2,
                                    (float)sf::Mouse::getPosition(app).y + camera.getCenter().y - camera.getSize().y / 2 - oak.getGlobalBounds().height / 2);

                if(event.mouseButton.button == sf::Mouse::Right)
                    abbey2.setPosition((float)sf::Mouse::getPosition(app).x + camera.getCenter().x - camera.getSize().x / 2 - abbey2.getGlobalBounds().width / 2,
                                       (float)sf::Mouse::getPosition(app).y + camera.getCenter().y - camera.getSize().y / 2 - abbey2.getGlobalBounds().height / 2);
            }
         }

         if( sf::Mouse::getPosition(app).x > (int)app.getSize().x - 10 )
            camera.move((float)clock.getElapsedTime().asMilliseconds(),0);

         if( sf::Mouse::getPosition(app).x < 10 )
            camera.move(-(float)clock.getElapsedTime().asMilliseconds(),0);

         if( sf::Mouse::getPosition(app).y > (int)app.getSize().y - 10 )
            camera.move(0,(float)clock.getElapsedTime().asMilliseconds());

         if( sf::Mouse::getPosition(app).y < 10 )
            camera.move(0,-(float)clock.getElapsedTime().asMilliseconds());

        if( camera.getCenter().x < 0 )
            camera.setCenter(0, camera.getCenter().y);

        if( camera.getCenter().y < 0 )
            camera.setCenter(camera.getCenter().x, 0);

        if( sunAngle2 > M_PI_2 )
            sunAngle2 = M_PI_2;

        if( sunAngle2 < M_PI_4 )
            sunAngle2 = M_PI_4;

        if( sunAngle > M_PI )
            sunAngle = M_PI;

        if( sunAngle < 0 )
            sunAngle = 0;

        position3[0] = -cos(sunAngle) * cos(sunAngle2);
        position3[1] = -sin(sunAngle) * cos(sunAngle2);
        position3[2] = -sin(sunAngle2);

        p[0] = lightPos.x;
        p[1] = lightPos.y*2;
        p[2] = lightPos.z;

        clock.restart();

        pack.screen.setActive(true);

        glLightfv(GL_LIGHT3, GL_POSITION, p);
        glLightfv(GL_LIGHT0, GL_POSITION, position3);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, color3);

        app.setView(camera);

        app.clear();

        lightPos.x = sf::Mouse::getPosition(app).x + camera.getCenter().x - camera.getSize().x/2;
        lightPos.y = sf::Mouse::getPosition(app).y + camera.getCenter().y - camera.getSize().y/2;

        pack.clear();

        if( !sf::Keyboard::isKeyPressed(sf::Keyboard::E) )
        {
            abbey.drawAmbientShadow(app, pack);
            abbey2.drawAmbientShadow(app, pack);
            fir.drawAmbientShadow(app, pack);
            oak.drawAmbientShadow(app, pack);
            reed1.drawAmbientShadow(app, pack);
            reed2.drawAmbientShadow(app, pack);
            pack.drawAmbientShadow();
        }

        oak.draw(app, pack);
        abbey.draw(app, pack);
        roughGrass.draw(app, pack);
        abbey2.draw(app, pack);
        reed1.draw(app, pack);
        reed2.draw(app, pack);
        fir.draw(app, pack);
        cave.draw(app, pack);

        sf::View oldCam = app.getView();
        app.setView(app.getDefaultView());
        app.draw(sf::Sprite(pack.screen.getTexture()));
        app.setView(oldCam);

        sf::Vertex triangle[] =
        {
            sf::Vertex(sf::Vector2f(lightPos.x, lightPos.y), sf::Color(255, 255, 255)),
            sf::Vertex(sf::Vector2f(lightPos.x+position3[0] * 100,lightPos.y+position3[1] * 50), sf::Color(0, 0, 0)),
            sf::Vertex(sf::Vector2f(lightPos.x + 10,lightPos.y), sf::Color(255, 255, 255))
        };

        app.draw(triangle, 3, sf::Triangles);


        sf::CircleShape c = sf::CircleShape(4, 32);
        c.setPosition(lightPos.x, lightPos.y);
        c.setFillColor(sf::Color(255, 255, 255));
        app.draw(c);

        c.setPosition(lightPos.x, lightPos.y-sqrt(3) / 2.0 * lightPos.z);
        c.setFillColor(sf::Color(255, 255, 0));
        app.draw(c);

        c.setPosition(position1[0], position1[1]/2);
        c.setFillColor(sf::Color(255, 255, 255));
        app.draw(c);

        c.setPosition(position1[0], position1[1] / 2 - sqrt(3) / 2.0 * position1[2]);
        c.setFillColor(sf::Color(255, 0, 0));
        app.draw(c);

        c.setPosition(position2[0], position2[1] / 2);
        c.setFillColor(sf::Color(255, 255, 255));
        app.draw(c);

        c.setPosition(position2[0], position2[1] / 2 - sqrt(3) / 2.0 * position2[2]);
        c.setFillColor(sf::Color(0, 127, 255));
        app.draw(c);

        // Update the window
        app.display();
     }

     return EXIT_SUCCESS;
 }
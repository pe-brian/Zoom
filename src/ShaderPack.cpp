////////////////////////////////////////////////////////////
//
// Zoom C++ library
// Copyright (C) 2011-2012 Pierre-Emmanuel BRIAN (zinlibs@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Many thanks for Naisse Grégoire
// the original author of this code
////////////////////////////////////////////////////////////

#include <Zoom/ShaderPack.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
ShaderPack::ShaderPack(sf::RenderTarget& target)
{
    screen.create(target.getSize().x, target.getSize().y);
    heightmapScreen.create(target.getSize().x, target.getSize().y);
    shadowScreen.create(target.getSize().x * 1.5, target.getSize().y * 1.5);

    normalShader.loadFromFile("data/normal.vert", "data/normal.frag");
    normalShader.setParameter("diffuse", sf::Shader::CurrentTexture);
    normalShader.setParameter("heightmap_screen", heightmapScreen.getTexture());
    normalShader.setParameter("screen", screen.getTexture());
    normalShader.setParameter("screen_ratio", sf::Vector2f(1.f / target.getSize().x, 1.f / target.getSize().y));
    normalShader.setParameter("shadow_ratio", sf::Vector2f(1.f / shadowScreen.getSize().x, 1.f / shadowScreen.getSize().y));
    normalShader.setParameter("shadow_map", shadowScreen.getTexture());
    //normalShader.setParameter("ambient_light", 0.1f, 0.1f, 0.1f, 1.0f);
    normalShader.setParameter("ambient_light", 0.15f, 0.15f, 0.15f, 1.0f);
    //normalShader.setParameter("ambient_light", 1.f, 1.f, 1.f, 1.0f);

    heightmapShader.loadFromFile("data/heightmap.frag", sf::Shader::Fragment);
    heightmapShader.setParameter("heightmap", sf::Shader::CurrentTexture);
    heightmapShader.setParameter("heightmap_screen", heightmapScreen.getTexture());
    heightmapShader.setParameter("screen_ratio", sf::Vector2f(1.f / target.getSize().x, 1.f / target.getSize().y));

    blurShader.loadFromFile("data/blur.frag", sf::Shader::Fragment);
    blurShader.setParameter("texture", sf::Shader::CurrentTexture);
    blurShader.setParameter("offset", 0.005);
}

////////////////////////////////////////////////////////////
void ShaderPack::clear()
{
    heightmapScreen.clear(sf::Color(0, 0, 0, 255));
    heightmapScreen.display();

    screen.clear();
    screen.display();

    shadowScreen.clear(sf::Color(0, 0, 0, 255));
    shadowScreen.display();
}

////////////////////////////////////////////////////////////
void ShaderPack::drawAmbientShadow()
{
    sf::View oldCam = screen.getView();
    screen.setView(screen.getDefaultView());
    shadowScreen.setView(shadowScreen.getDefaultView());

    blurShader.setParameter("direction_x", 1.0);
    shadowScreen.draw(sf::Sprite(shadowScreen.getTexture()), &blurShader);
    shadowScreen.display();
    blurShader.setParameter("direction_x", 0);
    shadowScreen.draw(sf::Sprite(shadowScreen.getTexture()), &blurShader);
    shadowScreen.display();

    screen.setView(oldCam);
}

}
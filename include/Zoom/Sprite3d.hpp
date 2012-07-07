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

#ifndef SPRITE3D_HPP
#define SPRITE3D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Zoom/ShaderPack.hpp>
#include <Zoom/Config.hpp>

namespace zin
{

class Sprite3d : public sf::Sprite
{
    public:

    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    Sprite3d();

    ////////////////////////////////////////////////////////////
    // Destructor
    ////////////////////////////////////////////////////////////
    ~Sprite3d();

    ////////////////////////////////////////////////////////////
    // Draw
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, ShaderPack& shaderPack);

    ////////////////////////////////////////////////////////////
    // Generate ambient shadow
    ////////////////////////////////////////////////////////////
    void generateAmbientShadow(sf::RenderTarget& target, ShaderPack& shaderPack, const sf::Vector3f& light);

    ////////////////////////////////////////////////////////////
    // Draw ambient shadow
    ////////////////////////////////////////////////////////////
    void drawAmbientShadow(sf::RenderTarget& target, ShaderPack& shaderPack);

    ////////////////////////////////////////////////////////////
    // Load
    ////////////////////////////////////////////////////////////
    void load(const sf::String& diffuseFilePath, const sf::String& normalFilePath, const sf::String& heightmapFilePath);

    ////////////////////////////////////////////////////////////
    // Set position
    ////////////////////////////////////////////////////////////
    void setPosition(float x, float y);

    ////////////////////////////////////////////////////////////
    // Set position
    ////////////////////////////////////////////////////////////
    void setPosition(float x, float y, float z);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Texture  diffuse;
    sf::Texture  normal;
    sf::Texture  heightmap;
    sf::Image    imgHeightmap;
    sf::Vector3f Pos3d;
    sf::Texture  shadowMapImg;
    sf::Sprite   shadowMap;
    float        height;
};

}

#endif // SPRITE3D_HPP
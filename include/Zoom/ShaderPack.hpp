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

#ifndef ZOOM_SHADERPACK_HPP
#define ZOOM_SHADERPACK_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Zoom/Config.hpp>

namespace zin
{

struct ShaderPack
{
    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    ShaderPack(sf::RenderTarget& target);

    ////////////////////////////////////////////////////////////
    // Clear
    ////////////////////////////////////////////////////////////
    void clear();

    ////////////////////////////////////////////////////////////
    // Draw ambient shadow
    ////////////////////////////////////////////////////////////
    void drawAmbientShadow();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
     sf::RenderTexture screen,
                       heightmapScreen,
                       shadowScreen;
     sf::Shader        normalShader,
                       heightmapShader,
                       shadowShader,
                       blurShader;
};

}


#endif // ZOOM_SHADERPACK_HPP
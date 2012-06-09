////////////////////////////////////////////////////////////
///
/// Zoom C++ library
/// Copyright (C) 2011-2012 ZinLibs (zinlibs@gmail.com)
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the use of this software.
/// Permission is granted to anyone to use this software for any purpose,
/// including commercial applications, and to alter it and redistribute it freely,
/// subject to the following restrictions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///    and must not be misrepresented as being the original software.
///
/// 3. This notice may not be removed or altered from any source distribution.
///
////////////////////////////////////////////////////////////

#ifndef ZOOM_LIGHT_MANAGER_HPP
#define ZOOM_LIGHT_MANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include <SFML/Graphics.hpp>
#include <Zoom/Light.hpp>
#include <Zoom/Spot.hpp>
#include <Zoom/Config.hpp>

namespace zin
{
	
class ZOOM_API LightManager : public sf::Drawable
{
public:

    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    LightManager(Uint32 width = 800, Uint32 height = 600, const Color& ambiantLightColor = Color(50, 50, 50, 128));
    
    ////////////////////////////////////////////////////////////
    // Attach a light to the manager
    ////////////////////////////////////////////////////////////
	void attach(Light& light);
    
    ////////////////////////////////////////////////////////////
    // Detach a light from the manager
    ////////////////////////////////////////////////////////////
    void detach(Light& light);
    
    ////////////////////////////////////////////////////////////
    // Attach a geom to the manager
    ////////////////////////////////////////////////////////////
    void attach(const Geom& geom);
    
    ////////////////////////////////////////////////////////////
    // Detach a geom from the manager
    ////////////////////////////////////////////////////////////
    void detach(const Geom& geom);

    ////////////////////////////////////////////////////////////
    // Set the blend mode
    ////////////////////////////////////////////////////////////
    void setBlendMode(sf::BlendMode blendMode);
    
    ////////////////////////////////////////////////////////////
    // Update the lights
    ////////////////////////////////////////////////////////////
    void update();

    ////////////////////////////////////////////////////////////
    // Set the debug mode
    ////////////////////////////////////////////////////////////
    void setDebugMode(bool enabled);

    ////////////////////////////////////////////////////////////
    // Get the debug mode
    ////////////////////////////////////////////////////////////
    bool getDebugMode();
    
private:
    
    ////////////////////////////////////////////////////////////
    // Draw the lights
    ////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool                     m_debugMode;
    sf::BlendMode            m_blendMode;
    sf::RenderTexture        m_renderTexture;
    sf::Color                m_ambiantLightColor;
    std::vector<Light*>      m_lights;
    std::vector<const Geom*> m_geoms;
};

}

#endif // ZOOM_LIGHT_MANAGER_HPP

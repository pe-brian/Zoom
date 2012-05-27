////////////////////////////////////////////////////////////
//
// Zooom C++ library
// Copyright (C) 2011-2012 ZinLibs (zinlibs@gmail.com)
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

#include <Zoom/LightManager.hpp>

namespace zin
{

////////////////////////////////////////////////////////////	
LightManager::LightManager(Uint32 width, Uint32 height, const Color& ambiantLightColor) :
m_ambiantLightColor(sf::Color(ambiantLightColor.r, ambiantLightColor.g, ambiantLightColor.b, ambiantLightColor.a))
{
    m_renderTexture.create(width, height);
    m_renderTexture.clear(m_ambiantLightColor);
}

////////////////////////////////////////////////////////////
void LightManager::attach(Light& light)
{
	m_lights.push_back(&light);
}

////////////////////////////////////////////////////////////
void LightManager::detach(Light& light)
{
    for( auto it = m_lights.begin(); it != m_lights.end(); ++it )
        if( &light == *it )
        {
            m_lights.erase(it);
            break;
        }
}

////////////////////////////////////////////////////////////
void LightManager::attach(const Geom& geom)
{
    m_geoms.push_back(&geom);
}

////////////////////////////////////////////////////////////
void LightManager::detach(const Geom& geom) 
{
    for( auto it = m_geoms.begin(); it != m_geoms.end(); ++it )
        if( &geom == *it )
        {
            m_geoms.erase(it);
            break;
        }
}

////////////////////////////////////////////////////////////
void LightManager::setBlendMode(sf::BlendMode blendMode)
{
    m_blendMode = blendMode;
}

////////////////////////////////////////////////////////////
void LightManager::update()
{
    std::vector<Segment> segments;

    for( auto& geom : m_geoms )
        for( size_t k(0); k < geom->getLiaisonsCount(); k++ )
            segments.push_back(geom->getLiaison(k).getSegment());

	for( auto& light : m_lights )
        light->generate(segments);

    m_renderTexture.clear(m_ambiantLightColor);

    for( auto& light : m_lights )
        m_renderTexture.draw(*light);

    m_renderTexture.display();
}

////////////////////////////////////////////////////////////
void LightManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    sprite.setTexture(m_renderTexture.getTexture());
    target.draw(sprite, states);
}

}
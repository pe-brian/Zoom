////////////////////////////////////////////////////////////
//
// Zoom C++ library
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

#include <Zoom/Spot.hpp>

namespace zin
{
	
////////////////////////////////////////////////////////////
Spot::Spot(const Coords& position, double angle, double radius, double aperture, Color color, Uint32 complexity) :
Light(position, radius, color, complexity),
m_aperture(aperture)
{
    setRotation(angle);
}

////////////////////////////////////////////////////////////
void Spot::generate(const std::vector<Segment>& segments)
{
    clear();
    m_vertexColor.clear();

    addVertex({0, 0});
    m_vertexColor.push_back(m_color);

    double angle = getRotation(), delta = m_aperture / double(m_complexity);
        
    for( Indice k(0); k < m_complexity; k++ )
        addTriangle({std::cos(angle) * m_radius, std::sin(angle) * m_radius}, {std::cos(angle + delta) * m_radius, std::sin(angle + delta) * m_radius}, 0, segments), angle+=delta;
}

}
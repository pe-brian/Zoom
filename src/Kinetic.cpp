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
/////////////////////////////////////////////////////////////

#include <Zoom/Kinetic.hpp>
#include <cmath>

namespace zin
{

////////////////////////////////////////////////////////////
Kinetic::Kinetic(const Curve& curve, double speed, double current, bool isRepeatable) :
m_curve(curve),
m_speed(speed),
m_current(current),
m_isRepeatable(isRepeatable) {}

////////////////////////////////////////////////////////////
bool Kinetic::isEnded()
{
    return m_current == 1;
}

////////////////////////////////////////////////////////////
 Point Kinetic::update(sf::Time timeStep)
 {
    if( m_current < 1 )
        m_current+=(m_speed * double(timeStep.asSeconds()) / m_curve.getLength());

    if( m_current > 1 )
        m_current = m_isRepeatable ? m_current - std::floor(m_current) : 1;

   return m_curve[m_current];
}

}

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

#include <Zoost/Math.hpp>
#include <iostream>

namespace zin
{

////////////////////////////////////////////////////////////
template <typename T>
Variation<T>::Variation(T begin, T end, double speed, double current, bool isRepeatable, bool isReversible) :
m_begin(begin),
m_end(end),
m_speed(speed),
m_current(current),
m_isRepeatable(isRepeatable),
m_isReversible(isReversible),
m_isReversed(false),
m_isFinished(false) {}

////////////////////////////////////////////////////////////
template <typename T>
T Variation<T>::update(sf::Time timeStep)
{
    if( !m_isFinished )
    {
        if( !m_isReversed )
        {
            if( m_current < 1 )
                m_current+=(m_speed * double(timeStep.asSeconds()) / Math::abs(m_begin - m_end));

            else if( m_current > 1 )
            {
                m_current = 1;

                m_isReversible ? m_isReversed = true : m_isRepeatable ? m_current = 0 : m_isFinished = true;
            }
        }

        else
        {
            if( m_current > 0 )
                m_current-=(m_speed * double(timeStep.asSeconds()) / Math::abs(m_begin - m_end));

            else if( m_current < 0 )
            {
                if( m_isReversible )
                {
                    m_isReversed = false;
                    m_current = 0;
                }
            
                if( !m_isRepeatable )
                    m_isFinished = true;
            }
        }
    }

    return Math::interpolate(m_begin, m_end, m_current);
}

}
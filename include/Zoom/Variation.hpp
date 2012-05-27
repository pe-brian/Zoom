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

#ifndef ZOOST_VARIATION_HPP
#define ZOOST_VARIATION_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Zoom/Config.hpp>
#include <SFML/System.hpp>

namespace zin
{

template <typename T>
class ZOOST_API Variation
{
public:

    ////////////////////////////////////////////////////////////
    // 
    ////////////////////////////////////////////////////////////
    Variation(T begin, T end, double speed = 1, double current = 0.f, bool isRepeatable = false, bool isRevertable = false);

    ////////////////////////////////////////////////////////////
    // 
    ////////////////////////////////////////////////////////////
    T update(sf::Time timeStep);

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool    m_isRepeatable,
            m_isReversible,
            m_isReversed,
            m_isFinished;
    double  m_current,
            m_speed;
    const T m_begin,
            m_end;
};

}

#include <Zoom/Variation.inl>

#endif // ZOOST_VARIATION_HPP

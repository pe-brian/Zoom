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

#ifndef ZOOST_KINETIC_HPP
#define ZOOST_KINETIC_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Zoost/Curve.hpp>
#include <Zoost/Vector2.hpp>
#include <Zoom/Config.hpp>
#include <SFML/System.hpp>

namespace zin
{

class ZOOST_API Kinetic
{
public:

    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    Kinetic(const Curve& curve, double speed = 1.f, double current = 0.f, bool isRepeatable = false);

    ////////////////////////////////////////////////////////////
    // Return true if the kinetic is ended
    ////////////////////////////////////////////////////////////
    bool isEnded();
    
    ////////////////////////////////////////////////////////////
    // Update the kinetic
    ////////////////////////////////////////////////////////////
    Point update(sf::Time timeStep);

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool         m_isRepeatable;
    double       m_current,
                 m_speed;
    const Curve& m_curve;
};

}

#endif // ZOOST_KINETIC_HPP

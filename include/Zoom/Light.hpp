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

#ifndef ZOOM_LIGHT_HPP
#define ZOOM_LIGHT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Zoost/Geom.hpp>
#include <Zoost/Segment.hpp>
#include <Zoost/Line.hpp>
#include <Zoost/Vector2.hpp>
#include <Zoom/Shape.hpp>
#include <Zoom/Color.hpp>
#include <Zoom/Config.hpp>

namespace zin
{
	
class ZOOM_API Light : public Geom, public sf::Drawable
{
public:
    
    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
	Light(double radius = 100, Color color = Color{255, 255, 255, 200}, Uint32 complexity = 16);
    
    ////////////////////////////////////////////////////////////
    // Generate the light
    ////////////////////////////////////////////////////////////
	virtual void generate(const std::vector<Segment>& segments);

    ////////////////////////////////////////////////////////////
    // Set the debug mode
    ////////////////////////////////////////////////////////////
    void setDebugMode(bool enabled);

    ////////////////////////////////////////////////////////////
    // Get the debug mode
    ////////////////////////////////////////////////////////////
    bool getDebugMode();

protected:

    ////////////////////////////////////////////////////////////
    // Add a triangle to the shape and compute intersections
    ////////////////////////////////////////////////////////////
	void addTriangle(Point p1, Point p2, Uint32 begin, const std::vector<Segment>& segments);

    ////////////////////////////////////////////////////////////
    // Draw the light
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    // Update the rendering
    ////////////////////////////////////////////////////////////
    void update() const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool                                 m_debugMode;
    mutable bool                         m_needUpdate;
	double                               m_radius;
	Color                                m_color;
	Uint32                               m_complexity;
    std::vector<Color>                   m_colors;
    mutable std::vector<sf::VertexArray> m_vertexArray;
    mutable std::vector<sf::VertexArray> m_vertexArrayDebug;
};

}

#endif // ZOOM_LIGHT_HPP
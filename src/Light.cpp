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

#include <Zoom/Light.hpp>

namespace zin
{
	
////////////////////////////////////////////////////////////
Light::Light(double radius, Color color, Uint32 complexity) :
m_color(color),
m_radius(radius),
m_complexity(complexity),
m_debugMode(false),
m_needUpdate(false) {}

////////////////////////////////////////////////////////////
void Light::setDebugMode(bool enabled)
{
    if( m_debugMode != enabled )
    {
        m_debugMode = enabled;
        m_needUpdate = true;
    }
}

////////////////////////////////////////////////////////////
bool Light::getDebugMode()
{
    return m_debugMode;
}

////////////////////////////////////////////////////////////
void Light::update() const
{
    if( m_needUpdate )
    {
        m_vertexArray.clear();

        for( size_t k(0); k < getFacesCount(); k++ )
        {
            Face& face = getFace(k);
            Triangle triangle = face.getTriangle();
                
            Color c1 = m_colors[face.v1.getIndice()],
                  c2 = m_colors[face.v2.getIndice()],
                  c3 = m_colors[face.v3.getIndice()];
                    
            sf::VertexArray array(sf::Triangles, 3);

            array[0].position = sf::Vector2f(triangle.p1.x, triangle.p1.y);
            array[1].position = sf::Vector2f(triangle.p2.x, triangle.p2.y);
            array[2].position = sf::Vector2f(triangle.p3.x, triangle.p3.y);

            array[0].color = sf::Color(c1.r, c1.g, c1.b, c1.a);
            array[1].color = sf::Color(c2.r, c2.g, c2.b, c2.a);
            array[2].color = sf::Color(c3.r, c3.g, c3.b, c3.a);
                    
            m_vertexArray.push_back(array);
        }

        if( m_debugMode )
        {
            for( size_t k(0); k < getFacesCount(); k++ )
            {
                Triangle triangle = getFace(k).getTriangle();
                    
                sf::VertexArray lines(sf::LinesStrip, 4);

                lines[0].position = sf::Vector2f(triangle.p1.x, triangle.p1.y);
                lines[1].position = sf::Vector2f(triangle.p2.x, triangle.p2.y);
                lines[2].position = sf::Vector2f(triangle.p3.x, triangle.p3.y);
                lines[3].position = sf::Vector2f(triangle.p1.x, triangle.p1.y);

                lines[0].color = sf::Color::White;
                lines[1].color = sf::Color::White;
                lines[2].color = sf::Color::White;
                lines[3].color = sf::Color::White;

                m_vertexArray.push_back(lines);
            }

            const Rect& rect = getBounds();
            Point origin = convertToGlobal(getOrigin());

            sf::VertexArray circle(sf::LinesStrip, 10);

            double angus = 0;
                
            for( size_t k(0); k < 10; k++ )
            {
                circle[k].position = sf::Vector2f(origin.x + std::cos(angus) * 11, origin.y + std::sin(angus) * 11);
                circle[k].color = sf::Color::Red;
                angus+=.698131701f;
            }

            m_vertexArray.push_back(circle);

            sf::VertexArray lines(sf::LinesStrip, 5);

            lines[0].position = sf::Vector2f(rect.pos.x - 1, rect.pos.y - 1);
            lines[1].position = sf::Vector2f(rect.pos.x + rect.size.x + 1, rect.pos.y - 1);
            lines[2].position = sf::Vector2f(rect.pos.x + rect.size.x + 1, rect.pos.y + rect.size.y + 1);
            lines[3].position = sf::Vector2f(rect.pos.x - 1, rect.pos.y + rect.size.y + 1);
            lines[4].position = sf::Vector2f(rect.pos.x - 1, rect.pos.y - 1);

            lines[0].color = sf::Color::Red;
            lines[1].color = sf::Color::Red;
            lines[2].color = sf::Color::Red;
            lines[3].color = sf::Color::Red;
            lines[4].color = sf::Color::Red;

            m_vertexArray.push_back(lines);
        }

        m_needUpdate = false;
    }
}

////////////////////////////////////////////////////////////
void Light::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    getTransform();

    update();

    for( auto& vertexArray : m_vertexArray )
        target.draw(vertexArray, states);
}

////////////////////////////////////////////////////////////
void Light::generate(const std::vector<Segment>& segments)
{
    clear();
    m_colors.clear();

    addVertex({0, 0});
    m_colors.push_back(m_color);

    double angle = 0, delta = 6.28318531f / static_cast<double>(m_complexity);
        
    for( size_t k(0); k < m_complexity; k++ )
    {
        addTriangle({std::cos(angle) * m_radius, std::sin(angle) * m_radius}, {std::cos(angle + delta) * m_radius, std::sin(angle + delta) * m_radius}, 0, segments);
        angle+=delta;
    }

    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Light::addTriangle(Point p1, Point p2, Uint32 begin, const std::vector<Segment>& segments)
{
    if( p1 == p2 )
        return;

    for( size_t k(begin); k < segments.size(); k++ )
    {
        Segment s = convertToLocal(segments[k]);
        double a = Vector2d::angle(s.p1, s.p2);

        if( a == 0 )
            continue;

        Point p0, w1, w2;

        if( a > 0 )
        {
            w1 = s.p1;
            w2 = s.p2;
        }

        else
        {
            w1 = s.p2;
            w2 = s.p1;
        }

        if( Triangle::contains(p0, p1, p2, w1) )
        {
            Point i;
            Line::intersects(p0, w1, p1, p2, i);
            addTriangle(p1, i, k + 1, segments);
            p1 = i;
        }
            
        if( Triangle::contains(p0, p1, p2, w2) )
        {
            Point i;
            Line::intersects(p0, w2, p1, p2, i);
            addTriangle(i, p2, k + 1, segments);
            p2 = i;
        }

        Point i1, i2, i3;

        bool int1 = s.intersects(Segment(p0, p1), i1),
             int2 = s.intersects(Segment(p0, p2), i2),
             int3 = s.intersects(Segment(p1, p2), i3);

        if( (int1 && i1 == p0) || (int2 && i2 == p0) || (int3 && i3 == p0) )
            continue;

        if( int1 && int2 )
        {
            p1 = i1;
            p2 = i2;
        }

        else
        {
            if( int1 && int3 )
            {
                addTriangle(i1, i3, begin, segments);
                p1 = i3;
            }

            if( int2 && int3 )
            {
                addTriangle(i2, i3, begin, segments);
                p2 = i3;
            }
        }
    }

    m_colors.push_back({m_color.r, m_color.g, m_color.b, char(255*(m_radius - p2.length()) / m_radius)});
    m_colors.push_back({m_color.r, m_color.g, m_color.b, char(255*(m_radius - p1.length()) / m_radius)});

    addFace(getVertex(0), addVertex(p1), addVertex(p2));
}

}
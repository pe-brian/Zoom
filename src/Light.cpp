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
Light::Light(const Point& position, double radius, Color color, Uint32 complexity) :
m_color(color),
m_radius(radius),
m_complexity(complexity)
{
    setPosition(position);
}

////////////////////////////////////////////////////////////
void Light::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for( size_t k(0); k < getFacesCount(); k++ )
    {
        Face& face = getFace(k);

        Triangle triangle = face.getTriangle();

        Color c1 = m_vertexColor[face.v1.getIndice()],
              c2 = m_vertexColor[face.v2.getIndice()],
              c3 = m_vertexColor[face.v3.getIndice()];
        
        if( Shape::debugModeEnabled )
        {
            sf::VertexArray array(sf::LinesStrip, 3);

            array[0].position = sf::Vector2f(triangle.p1.x, triangle.p1.y);
            array[1].position = sf::Vector2f(triangle.p2.x, triangle.p2.y);
            array[2].position = sf::Vector2f(triangle.p3.x, triangle.p3.y);

            array[0].color = sf::Color::White;
            array[1].color = sf::Color::White;
            array[2].color = sf::Color::White;

            target.draw(array);
        }

        else
        {
            sf::VertexArray array(sf::Triangles, 3);

            array[0].position = sf::Vector2f(triangle.p1.x, triangle.p1.y);
            array[1].position = sf::Vector2f(triangle.p2.x, triangle.p2.y);
            array[2].position = sf::Vector2f(triangle.p3.x, triangle.p3.y);

            array[0].color = sf::Color(c1.r, c1.g, c1.b, c1.a);
            array[1].color = sf::Color(c2.r, c2.g, c2.b, c2.a);
            array[2].color = sf::Color(c3.r, c3.g, c3.b, c3.a);
        
            target.draw(array);
        }
    }

    if( Shape::debugModeEnabled )
    {
        Point origin = convertToGlobal(getOrigin());
        const Rect& rect = getBounds();

        sf::CircleShape circle(8);

        circle.setFillColor(sf::Color(0, 0, 0, 0));
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(1);
        circle.setPosition(origin.x, origin.y);

        target.draw(circle);

        sf::VertexArray rectangle(sf::LinesStrip, 5);

        rectangle[0].position = sf::Vector2f(rect.pos.x - 1,                   rect.pos.y - 1);
        rectangle[1].position = sf::Vector2f(rect.pos.x - 1 + rect.size.x + 2, rect.pos.y - 1);
        rectangle[2].position = sf::Vector2f(rect.pos.x - 1 + rect.size.x + 2, rect.pos.y - 1 + rect.size.y + 2);
        rectangle[3].position = sf::Vector2f(rect.pos.x - 1,                   rect.pos.y - 1 + rect.size.y + 2);
        rectangle[4].position = sf::Vector2f(rect.pos.x - 1,                   rect.pos.y - 1);

        rectangle[0].color = sf::Color::Red;
        rectangle[1].color = sf::Color::Red;
        rectangle[2].color = sf::Color::Red;
        rectangle[3].color = sf::Color::Red;
        rectangle[4].color = sf::Color::Red;

        target.draw(rectangle);
    }
}

////////////////////////////////////////////////////////////
void Light::generate(const std::vector<Segment>& segments)
{
    clear();
    m_vertexColor.clear();

    addVertex({0, 0});
    m_vertexColor.push_back(m_color);

    double angle = 0, delta = 6.28318531 / double(m_complexity);
        
    for( Indice k(0); k < m_complexity; k++ )
        addTriangle({std::cos(angle) * m_radius, std::sin(angle) * m_radius}, {std::cos(angle + delta) * m_radius, std::sin(angle + delta) * m_radius}, 0, segments), angle+=delta;
}

////////////////////////////////////////////////////////////
void Light::addTriangle(Point p1, Point p2, Uint32 begin, const std::vector<Segment>& segments)
{
    if( p1 == p2 )
        return;

    for( Indice k(begin); k < segments.size(); k++ )
    {
        Segment segment = convertToLocal(segments[k]);
        double a = Vector2d::angle(Vector2d(segment.p1), Vector2d(segment.p2));

        if( a == 0 )
            continue;

        Point p0, w1 = a > 0 ? segment.p1 : segment.p2, w2 = a > 0 ? segment.p2 : segment.p1;

        if( Triangle::contains(p0, p1, p2, w1) )
        {
            Point i;
            Line(p0, w1).intersects(Line(p1, p2), i);
            addTriangle(p1, i, k + 1, segments), p1 = i;
        }
            
        if( Triangle::contains(p0, p1, p2, w2) )
        {
            Point i;
            Line(p0, w2).intersects(Line(p1, p2), i);
            addTriangle(i, p2, k + 1, segments), p2 = i;
        }

        Point i1, i2, i3;

        bool is_i1 = segment.intersects(Segment(p0, p1), i1),
             is_i2 = segment.intersects(Segment(p0, p2), i2),
             is_i3 = segment.intersects(Segment(p1, p2), i3);

        if( (is_i1 && i1 == p0) || (is_i2 && i2 == p0) || (is_i3 && i3 == p0) )
            continue;

        if( is_i1 && is_i2 ) p1 = i1, p2 = i2;

        else
        {
            if( is_i1 && is_i3 )
                addTriangle(i1, i3, begin, segments), p1 = i3;

            if( is_i2 && is_i3 )
                addTriangle(i2, i3, begin, segments), p2 = i3;
        }
    }

    Color c1 = m_color, c2 = m_color;

    c1.a = 255*(m_radius - p1.length()) / m_radius;
    c2.a = 255*(m_radius - p2.length()) / m_radius;

    Vertex& vertex1 = addVertex(p1);
    m_vertexColor.push_back(c1);

    Vertex& vertex2 = addVertex(p2);
    m_vertexColor.push_back(c2);

    addFace(getVertex(0), vertex1, vertex2);
}

}
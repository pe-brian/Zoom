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

#include <Zoom/Shape.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
bool Shape::debugModeEnabled = false;

////////////////////////////////////////////////////////////
Shape::Shape(Geom& geom) :
m_geom(geom),
m_outlineWidth(0),
m_pointSize(0)
{
 	for( size_t k(0); k < m_geom.getVerticesCount(); k++ )
		m_vertexColor.push_back(m_fillColor);

    m_geom.addObserver(*this);
}

////////////////////////////////////////////////////////////
void Shape::onNotification(size_t notification, size_t id)
{
    std::cout << "notification" << std::endl;
    switch( notification )
    {
        case Geom::NONE : break;
        case Geom::CREATED_VERTEX : break;
        case Geom::CREATED_LIAISON : break;
        case Geom::CREATED_FACE : break;
        case Geom::REMOVED_VERTEX : break;
        case Geom::REMOVED_LIAISON : break;
        case Geom::REMOVED_FACE : break;
        case Geom::CLEAR : break;
    }
}

////////////////////////////////////////////////////////////
void Shape::clear()
{
	m_geom.clear();
	m_vertexColor.clear();
}

////////////////////////////////////////////////////////////
Geom& Shape::getGeom()
{
    return m_geom;
}

////////////////////////////////////////////////////////////
void Shape::setFillColor(const Color& color)
{
	m_fillColor = color;

	for( size_t k(0); k < m_vertexColor.size(); k++ )
		m_vertexColor[k] = color;
}

////////////////////////////////////////////////////////////
void Shape::setOutlineColor(const Color& color)
{
	m_outlineColor = color;
}

////////////////////////////////////////////////////////////
void Shape::setOutlineWidth(Uint32 width) 
{
	m_outlineWidth = width;
}

////////////////////////////////////////////////////////////
void Shape::setColor(size_t vertexId, const Color& color)
{
	m_vertexColor[vertexId] = color;
}

////////////////////////////////////////////////////////////
void Shape::setPointSize(Uint32 size)
{
	m_pointSize = size;
}

////////////////////////////////////////////////////////////
Uint32 Shape::getPointSize()
{
	return m_pointSize;
}

////////////////////////////////////////////////////////////
void Shape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if( debugModeEnabled )
    {
        const Rect& rect = m_geom.getBounds();
        Point origin = m_geom.convertToGlobal(m_geom.getOrigin());

        sf::CircleShape circle(8);

        circle.setFillColor(sf::Color(0, 0, 0, 0));
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(1);
        circle.setPosition(origin.x - 8, origin.y - 8);

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
    
    for( size_t k(0); k < m_geom.getFacesCount(); k++ )
    {
        Face& face = m_geom.getFace(k);

        Triangle triangle = face.getTriangle();

        Color c1 = m_vertexColor[face.v1.getIndice()],
              c2 = m_vertexColor[face.v2.getIndice()],
              c3 = m_vertexColor[face.v3.getIndice()];
        
        if( debugModeEnabled )
        {
	        sf::VertexArray lines(sf::LinesStrip, 4);

			lines[0].position = sf::Vector2f(triangle.p1.x, triangle.p1.y);
			lines[1].position = sf::Vector2f(triangle.p2.x, triangle.p2.y);
			lines[2].position = sf::Vector2f(triangle.p3.x, triangle.p3.y);
			lines[3].position = sf::Vector2f(triangle.p1.x, triangle.p1.y);

			lines[0].color = sf::Color::White;
			lines[1].color = sf::Color::White;
			lines[2].color = sf::Color::White;
			lines[3].color = sf::Color::White;

			target.draw(lines);
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

	for( size_t k(0); k < m_geom.getLiaisonsCount(); k++ )
    {
        Segment segment = m_geom.getLiaison(k).getSegment();

	    Color color = m_outlineColor;

	    sf::VertexArray line(sf::Lines, 2);

	    line[0].position = sf::Vector2f(segment.p1.x, segment.p1.y);
		line[1].position = sf::Vector2f(segment.p2.x, segment.p2.y);

		line[0].color = debugModeEnabled ? sf::Color::White : sf::Color(color.r, color.g, color.b, color.a);
		line[1].color = debugModeEnabled ? sf::Color::White : sf::Color(color.r, color.g, color.b, color.a);

		target.draw(line);
	}

    for( size_t k(0); k < m_geom.getVerticesCount(); k++ )

        if( m_pointSize > 0 )
        {
            Point point = m_geom.convertToGlobal(m_geom.getVertex(k).getCoords());
            Color color = m_vertexColor[k];

            sf::CircleShape circle(m_pointSize);
            
			circle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
			circle.setPosition(point.x, point.y);

			target.draw(circle);
        }
}

}
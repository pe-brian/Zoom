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
m_isVertexShowed(false),
m_isLiaisonShowed(true),
m_isFaceShowed(true),
m_isFaceOwnColor(true),
m_defaultVertexColor(Color::White),
m_defaultLiaisonColor(Color::White),
m_defaultFaceColor(Color::White),
m_defaultLiaisonWidth(1),
m_defaultVertexSize(1)
{
    for( size_t k(0); k < m_geom.getVerticesCount(); k++ )
        onVertexAdded();

    for( size_t k(0); k < m_geom.getLiaisonsCount(); k++ )
        onLiaisonAdded();

    for( size_t k(0); k < m_geom.getFacesCount(); k++ )
        onFaceAdded();

 	setVertexColor(m_defaultVertexColor);
    setLiaisonColor(m_defaultLiaisonColor);
    setFaceColor(m_defaultFaceColor);

    m_geom.addObserver(*this);
}

////////////////////////////////////////////////////////////
Geom& Shape::getGeom()
{
    return m_geom;
}

////////////////////////////////////////////////////////////
void Shape::onVertexAdded()
{
    m_vertexInfos.push_back({m_isVertexShowed, m_defaultVertexColor, m_defaultVertexSize});
}

////////////////////////////////////////////////////////////
void Shape::onLiaisonAdded()
{
    m_liaisonInfos.push_back({m_isLiaisonShowed, m_defaultLiaisonColor, m_defaultLiaisonWidth});
}

////////////////////////////////////////////////////////////
void Shape::onFaceAdded()
{
    m_faceInfos.push_back({m_isFaceShowed, m_isFaceOwnColor, m_defaultFaceColor});
}

////////////////////////////////////////////////////////////
void Shape::onVertexRemoved(size_t indice)
{
    m_vertexInfos.erase(m_vertexInfos.begin() + indice);
}

////////////////////////////////////////////////////////////
void Shape::onLiaisonRemoved(size_t indice)
{
     m_liaisonInfos.erase(m_liaisonInfos.begin() + indice);
}

////////////////////////////////////////////////////////////
void Shape::onFaceRemoved(size_t indice)
{
     m_faceInfos.erase(m_faceInfos.begin() + indice);
}

////////////////////////////////////////////////////////////
void Shape::onErasing()
{
     m_vertexInfos.clear();
     m_liaisonInfos.clear();
     m_faceInfos.clear();
}

////////////////////////////////////////////////////////////
void Shape::setVertexColor(const Color& color)
{
    for( auto& info : m_vertexInfos )
        info.color = color;

    m_defaultVertexColor = color;
}
    
////////////////////////////////////////////////////////////
void Shape::setVertexColor(size_t indice, const Color& color)
{
    m_vertexInfos[indice].color = color;
}

////////////////////////////////////////////////////////////
void Shape::setLiaisonColor(const Color& color)
{
    for( auto& info : m_liaisonInfos )
        info.color = color;

    m_defaultLiaisonColor = color;
}

////////////////////////////////////////////////////////////
void Shape::setLiaisonColor(size_t indice, const Color& color)
{
    m_liaisonInfos[indice].color = color;
}

////////////////////////////////////////////////////////////
void Shape::setFaceColor(const Color& color)
{
    for( auto& info : m_faceInfos )
        info.color = color;

    m_defaultFaceColor = color;
}

////////////////////////////////////////////////////////////
void Shape::setFaceColor(size_t indice, const Color& color)
{
    m_faceInfos[indice].color = color;
}

////////////////////////////////////////////////////////////
void Shape::setVertexSize(Uint16 size)
{
    for( auto& info : m_vertexInfos )
        info.size = size;

    m_defaultVertexSize = size;
}

////////////////////////////////////////////////////////////
void Shape::setVertexSize(size_t indice, Uint16 size)
{
    m_vertexInfos[indice].size = size;
}

////////////////////////////////////////////////////////////
void Shape::setLiaisonWidth(Uint16 width)
{
    for( auto& info : m_liaisonInfos )
        info.width = width;

    m_defaultLiaisonWidth = width;
}

////////////////////////////////////////////////////////////
void Shape::setLiaisonWidth(size_t indice, Uint16 width)
{
    m_liaisonInfos[indice].width = width;
}

////////////////////////////////////////////////////////////
void Shape::showVertex(bool showed)
{
    for( auto& info : m_vertexInfos )
        info.showed = showed;

    m_isVertexShowed = showed;
}

////////////////////////////////////////////////////////////
void Shape::showVertex(size_t indice, bool showed)
{
    m_vertexInfos[indice].showed = showed;
}

////////////////////////////////////////////////////////////
void Shape::showLiaison(bool showed)
{
    for( auto& info : m_liaisonInfos )
        info.showed = showed;

    m_isLiaisonShowed = showed;
}

////////////////////////////////////////////////////////////
void Shape::showLiaison(size_t indice, bool showed)
{
    m_liaisonInfos[indice].showed = showed;
}

////////////////////////////////////////////////////////////
void Shape::showFace(bool showed)
{
    for( auto& info : m_faceInfos )
        info.showed = showed;

    m_isFaceShowed = showed;
}

////////////////////////////////////////////////////////////
void Shape::showFace(size_t indice, bool showed)
{
    m_faceInfos[indice].showed = showed;
}

////////////////////////////////////////////////////////////
void Shape::useOwnFaceColor(bool used)
{
    for( auto& info : m_faceInfos )
        info.ownColor = used;

    m_isFaceOwnColor = used;
}

////////////////////////////////////////////////////////////
void Shape::useOwnFaceColor(size_t indice, bool used)
{
    m_faceInfos[indice].ownColor = used;
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
        if( m_faceInfos[k].showed )
        {
            Face& face = m_geom.getFace(k);

            Triangle triangle = face.getTriangle();

            Color color = m_faceInfos[k].color;
            
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

    			array[0].color = sf::Color(color.r, color.g, color.b, color.a);
    			array[1].color = sf::Color(color.r, color.g, color.b, color.a);
    			array[2].color = sf::Color(color.r, color.g, color.b, color.a);
            
            	target.draw(array);
            }
        }
    }

	for( size_t k(0); k < m_geom.getLiaisonsCount(); k++ )
    {
        if( m_liaisonInfos[k].showed )
        {
            Segment segment = m_geom.getLiaison(k).getSegment();

    	    Color color = m_vertexInfos[k].color;

    	    sf::VertexArray line(sf::Lines, 2);

    	    line[0].position = sf::Vector2f(segment.p1.x, segment.p1.y);
    		line[1].position = sf::Vector2f(segment.p2.x, segment.p2.y);

    		line[0].color = debugModeEnabled ? sf::Color::White : sf::Color(color.r, color.g, color.b, color.a);
    		line[1].color = debugModeEnabled ? sf::Color::White : sf::Color(color.r, color.g, color.b, color.a);

    		target.draw(line);
        }
	}

    for( size_t k(0); k < m_geom.getVerticesCount(); k++ )

        if( m_vertexInfos[k].showed )

            if( m_vertexInfos[k].size > 0 )
            {
                Point point = m_geom.convertToGlobal(m_geom.getVertex(k).getCoords());
                Color color = m_vertexInfos[k].color;

                sf::CircleShape circle(m_vertexInfos[k].size);
                
    			circle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    			circle.setPosition(point.x, point.y);

    			target.draw(circle);
            }
}

}
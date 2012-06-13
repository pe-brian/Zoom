////////////////////////////////////////////////////////////
///
/// Zoom C++ library
/// Copyright (C) 2011-2012 Pierre-Emmanuel BRIAN (zinlibs@gmail.com)
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
#include <Zoost/Converter.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Shape::Shape(Geom& geom) :
m_geom(geom),
m_isVertexShowed(false),
m_isLiaisonShowed(true),
m_isFaceShowed(true),
m_isFaceColorEnabled(true),
m_defaultVertexColor(Color::White),
m_defaultLiaisonColor(Color::White),
m_defaultFaceColor(Color::White),
m_defaultLiaisonWidth(1),
m_defaultVertexSize(1),
m_needUpdate(true),
m_debugMode(false)
{
    for( size_t k(0); k < m_geom.getVerticesCount(); k++ )
        onVertexAdded();

    for( size_t k(0); k < m_geom.getLiaisonsCount(); k++ )
        onLiaisonAdded();

    for( size_t k(0); k < m_geom.getFacesCount(); k++ )
        onFaceAdded();

 	setVerticesColor(m_defaultVertexColor);
    setLiaisonsColor(m_defaultLiaisonColor);
    setFacesColor(m_defaultFaceColor);

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
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::onLiaisonAdded()
{
    m_liaisonInfos.push_back({m_isLiaisonShowed, m_defaultLiaisonColor, m_defaultLiaisonWidth});
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::onFaceAdded()
{
    m_faceInfos.push_back({m_isFaceShowed, m_isFaceColorEnabled, m_defaultFaceColor});
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::onVertexRemoved(size_t indice)
{
    m_vertexInfos.erase(m_vertexInfos.begin() + indice);
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::onLiaisonRemoved(size_t indice)
{
     m_liaisonInfos.erase(m_liaisonInfos.begin() + indice);
     m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::onFaceRemoved(size_t indice)
{
     m_faceInfos.erase(m_faceInfos.begin() + indice);
     m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::onErasing()
{
     m_vertexInfos.clear();
     m_liaisonInfos.clear();
     m_faceInfos.clear();
     m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setVerticesColor(const Color& color)
{
    for( auto& info : m_vertexInfos )
        info.color = color;

    m_defaultVertexColor = color;
    m_needUpdate = true;
}
    
////////////////////////////////////////////////////////////
void Shape::setVertexColor(size_t indice, const Color& color)
{
    m_vertexInfos[indice].color = color;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setLiaisonsColor(const Color& color)
{
    for( auto& info : m_liaisonInfos )
        info.color = color;

    m_defaultLiaisonColor = color;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setLiaisonColor(size_t indice, const Color& color)
{
    m_liaisonInfos[indice].color = color;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setFacesColor(const Color& color)
{
    for( auto& info : m_faceInfos )
        info.color = color;

    m_defaultFaceColor = color;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setFaceColor(size_t indice, const Color& color)
{
    m_faceInfos[indice].color = color;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setVerticesSize(Uint16 size)
{
    for( auto& info : m_vertexInfos )
        info.size = size;

    m_defaultVertexSize = size;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setVertexSize(size_t indice, Uint16 size)
{
    m_vertexInfos[indice].size = size;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setLiaisonsWidth(Uint16 width)
{
    for( auto& info : m_liaisonInfos )
        info.width = width;

    m_defaultLiaisonWidth = width;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setLiaisonWidth(size_t indice, Uint16 width)
{
    m_liaisonInfos[indice].width = width;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::showVertices(bool showed)
{
    for( auto& info : m_vertexInfos )
        info.showed = showed;

    m_isVertexShowed = showed;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::showVertex(size_t indice, bool showed)
{
    m_vertexInfos[indice].showed = showed;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::showLiaisons(bool showed)
{
    for( auto& info : m_liaisonInfos )
        info.showed = showed;

    m_isLiaisonShowed = showed;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::showLiaison(size_t indice, bool showed)
{
    m_liaisonInfos[indice].showed = showed;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::showFaces(bool showed)
{
    for( auto& info : m_faceInfos )
        info.showed = showed;

    m_isFaceShowed = showed;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::showFace(size_t indice, bool showed)
{
    m_faceInfos[indice].showed = showed;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::enableFacesColor(bool enabled)
{
    for( auto& info : m_faceInfos )
        info.enableColor = enabled;

    m_isFaceColorEnabled = enabled;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::enableFaceColor(size_t indice, bool enabled)
{
    m_faceInfos[indice].enableColor = enabled;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::setDebugMode(bool enabled)
{
    m_debugMode = enabled;
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
bool Shape::getDebugMode()
{
    return m_debugMode;
}

////////////////////////////////////////////////////////////
void Shape::update() const
{
    if( m_needUpdate )
    {
        m_vertexArray.clear();
        m_vertexArrayDebug.clear();

        if( m_debugMode )
        {
            for( size_t k(0); k < m_geom.getFacesCount(); k++ )
            {
                Face& face = m_geom.getFace(k);

                Vector2d p1 = face.v1.getCoords();
                Vector2d p2 = face.v2.getCoords();
                Vector2d p3 = face.v3.getCoords();
                    
                sf::VertexArray lines(sf::LinesStrip, 4);

                lines[0].position = sf::Vector2f(p1.x, p1.y);
                lines[1].position = sf::Vector2f(p2.x, p2.y);
                lines[2].position = sf::Vector2f(p3.x, p3.y);
                lines[3].position = sf::Vector2f(p1.x, p1.y);

                lines[0].color = sf::Color::White;
                lines[1].color = sf::Color::White;
                lines[2].color = sf::Color::White;
                lines[3].color = sf::Color::White;

                m_vertexArray.push_back(lines);
            }

            for( size_t k(0); k < m_geom.getLiaisonsCount(); k++ )
            {
                Liaison& liaison = m_geom.getLiaison(k);

                Vector2d p1 = liaison.v1.getCoords();
                Vector2d p2 = liaison.v2.getCoords();

                sf::VertexArray line(sf::Lines, 2);

                line[0].position = sf::Vector2f(p1.x, p1.y);
                line[1].position = sf::Vector2f(p2.x, p2.y);

                line[0].color = sf::Color::White;
                line[1].color = sf::Color::White;

                m_vertexArray.push_back(line);
            }

            const Rect& rect = m_geom.getGlobalBounds();
            Point origin = m_geom.convertToGlobal(m_geom.getOrigin());

            sf::VertexArray circle(sf::LinesStrip, 10);

            double angus = 0;
                
            for( size_t k(0); k < 10; k++ )
            {
                circle[k].position = sf::Vector2f(origin.x + std::cos(angus) * 11, origin.y + std::sin(angus) * 11);
                circle[k].color = sf::Color::Red;
                angus+=.698131701f;
            }

            m_vertexArrayDebug.push_back(circle);

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

            m_vertexArrayDebug.push_back(lines);
        }

        else
        {
            for( size_t k(0); k < m_geom.getFacesCount(); k++ )
            {
                if( m_faceInfos[k].showed )
                {
                    Face& face = m_geom.getFace(k);

                    Vector2d p1 = face.v1.getCoords();
                    Vector2d p2 = face.v2.getCoords();
                    Vector2d p3 = face.v3.getCoords();
                    
                    sf::VertexArray array(sf::Triangles, 3);

                    array[0].position = sf::Vector2f(p1.x, p1.y);
                    array[1].position = sf::Vector2f(p2.x, p2.y);
                    array[2].position = sf::Vector2f(p3.x, p3.y);

                    array[0].color = m_faceInfos[k].color;
                    array[1].color = m_faceInfos[k].color;
                    array[2].color = m_faceInfos[k].color;
                    
                    m_vertexArray.push_back(array);
                }
            }

            for( size_t k(0); k < m_geom.getLiaisonsCount(); k++ )
            {
                if( m_liaisonInfos[k].showed )
                {
                    Liaison& liaison = m_geom.getLiaison(k);

                    Vector2d a = liaison.v1.getCoords();
                    Vector2d b = liaison.v2.getCoords();

                    double angle = std::atan((b.y - a.y) / (b.x - a.x));
                    double width = m_liaisonInfos[k].width;

                    sf::VertexArray line(sf::Quads, 4);

                    line[0].position = sf::Vector2f(a.x + width * std::cos(angle + toRads( 90)), a.y + width * std::sin(angle + toRads( 90)));
                    line[1].position = sf::Vector2f(a.x + width * std::cos(angle + toRads(270)), a.y + width * std::sin(angle + toRads(270)));
                    line[2].position = sf::Vector2f(b.x + width * std::cos(angle + toRads(270)), b.y + width * std::sin(angle + toRads(270)));
                    line[3].position = sf::Vector2f(b.x + width * std::cos(angle + toRads( 90)), b.y + width * std::sin(angle + toRads( 90)));

                    line[0].color = m_vertexInfos[k].color;
                    line[1].color = m_vertexInfos[k].color;
                    line[2].color = m_vertexInfos[k].color;
                    line[3].color = m_vertexInfos[k].color;

                    m_vertexArray.push_back(line);
                }
            }

            for( size_t k(0); k < m_geom.getVerticesCount(); k++ )

                if( m_vertexInfos[k].showed )

                    if( m_vertexInfos[k].size > 0 )
                    {
                        Point point = m_geom.getVertex(k).getCoords();

                        sf::VertexArray circle(sf::TrianglesFan, 40);

                        circle[0].position = sf::Vector2f(point.x, point.y);
                        circle[0].color = m_vertexInfos[k].color;

                        double angus;
                            
                        for( size_t k(1); k < 40; k++ )
                        {
                            circle[k].position = sf::Vector2f(point.x + std::cos(angus) * m_vertexInfos[k].size, point.y + std::sin(angus) * m_vertexInfos[k].size);
                            circle[k].color = m_vertexInfos[k].color;

                            angus+=.157079633f;
                        }

                        m_vertexArray.push_back(circle);
                    }
                }

        m_needUpdate = false;
    }
}

////////////////////////////////////////////////////////////
void Shape::onTransformUpdated()
{
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::onVertexMoved()
{
    m_needUpdate = true;
}

////////////////////////////////////////////////////////////
void Shape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    double* values = m_geom.getTransform().getValues();

    sf::Transform defaultTransform = states.transform;

    states.transform = sf::Transform(static_cast<float>(values[0]), static_cast<float>(values[1]), static_cast<float>(values[2]),
                                     static_cast<float>(values[3]), static_cast<float>(values[4]), static_cast<float>(values[5]),
                                     static_cast<float>(values[6]), static_cast<float>(values[7]), static_cast<float>(values[8]));

    update();

    for( auto& vertexArray : m_vertexArray )
        target.draw(vertexArray, states);

    if( m_debugMode )
    {
        states.transform = defaultTransform;

        for( auto& vertexArray : m_vertexArrayDebug )
            target.draw(vertexArray, states);
    }
}

}
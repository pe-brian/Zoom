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

////////////////////////////////////////////////////////////
// Many thanks for Naisse Grégoire
// the original author of this code
////////////////////////////////////////////////////////////

#include <Zoom/Sprite3d.hpp>
#include <math.h>

namespace zin
{

////////////////////////////////////////////////////////////
Sprite3d::Sprite3d() {}

////////////////////////////////////////////////////////////
Sprite3d::~Sprite3d() {}

////////////////////////////////////////////////////////////
void Sprite3d::draw(sf::RenderTarget& target, ShaderPack& shaderPack)
{
    sf::Sprite sprite = *this;

    shaderPack.screen.setView(target.getView());

    shaderPack.normalShader.setParameter("normal", normal);
    shaderPack.normalShader.setParameter("heightmap", heightmap);
    shaderPack.normalShader.setParameter("height_factor", height * fabs(getScale().y));
    shaderPack.normalShader.setParameter("image_ratio", sf::Vector2f(1.f / getGlobalBounds().width, 1.f / height));
    shaderPack.normalShader.setParameter("z_pos", Pos3d.z);
    shaderPack.normalShader.setParameter("flipx", getScale().x > 0 ? 1 : -1);

    shaderPack.screen.draw(sprite, &shaderPack.normalShader);

    shaderPack.heightmapScreen.setView(target.getView());

    sprite.setTexture(heightmap);

    shaderPack.heightmapShader.setParameter("diffuse", diffuse);
    shaderPack.heightmapShader.setParameter("height_factor", height);
    shaderPack.heightmapShader.setParameter("z_pos", Pos3d.z);

    shaderPack.heightmapScreen.draw(sprite, &shaderPack.heightmapShader);
}

////////////////////////////////////////////////////////////
void Sprite3d::generateAmbientShadow(sf::RenderTarget& target, ShaderPack& shaderPack, const sf::Vector3f& light)
{
    const int W = heightmap.getSize().x + (int)((height + Pos3d.z) * std::fabs(light.x / light.z) + 1);
    const int H = heightmap.getSize().y + (int)((height + Pos3d.z) * std::fabs(light.y / 2.0 / light.z) + 1)
                                          + (int)((height + Pos3d.z) * std::sqrt(3) / 2.0 + 1);

    const int X = std::min(0.f, -light.x * (height + Pos3d.z) / light.z);
    const int Y = std::min(0.f, -light.y * (height + Pos3d.z) / light.z);

    sf::Uint8* shadowMapPix = new sf::Uint8[W * H * 4];

    const sf::Uint8* localHeightmap = imgHeightmap.getPixelsPtr();

    for( size_t x = 0 ; x < heightmap.getSize().x ; x++ )

        for( size_t y = 0 ; y < heightmap.getSize().y ; y ++ )
        {
            unsigned int x_p = x;

            if( getScale().x < 0 )
                x_p = heightmap.getSize().x - x - 1;

            float c = localHeightmap[y * heightmap.getSize().x * 4 + x_p * 4 + 2];

            if( localHeightmap[y * heightmap.getSize().x * 4 + x_p * 4 + 3] > 192 )
            {
                c *= 255 / (float)localHeightmap[y * heightmap.getSize().x * 4 + x_p * 4 + 3];

                float h = height * (float)c / 255 + Pos3d.z;

                sf::Vector2f p(x - X, y - Y);

                p.y += h*sqrt(3)/2;

                p.x -= light.x * h / light.z;
                p.y -= light.y * h / 2.f / light.z;

                p.x = (int)p.x;
                p.y = (int)p.y;

                if( p.x >= 0 && p.y >= 0 && p.x < W && p.y < H )
                {
                    unsigned int n = p.y * W * 4 + p.x * 4;
                    shadowMapPix[n] = 0;
                    shadowMapPix[n + 1] = 0;

                    if( c > shadowMapPix[n + 2] )
                        shadowMapPix[n + 2] = c;

                    shadowMapPix[n + 3] = 255;
                }
            }
        }

    shadowMapImg.create(W, H);
    shadowMapImg.update(shadowMapPix);

    shadowMap.setTexture(shadowMapImg);
    shadowMap.setPosition(sf::Vector2f(X, Y));

    delete[] shadowMapPix;
}

////////////////////////////////////////////////////////////
void Sprite3d::drawAmbientShadow(sf::RenderTarget& target, ShaderPack& shaderPack)
{
    sf::RenderTexture& renderTexture = shaderPack.shadowScreen;
    sf::View view = target.getView();
    view.setSize(renderTexture.getSize().x, renderTexture.getSize().y);
    renderTexture.setView(view);

    shaderPack.heightmapShader.setParameter("height_factor", height * fabs(getScale().y));
    shaderPack.heightmapShader.setParameter("z_pos", Pos3d.z);
    shaderPack.heightmapShader.setParameter("heightmap_screen", renderTexture.getTexture());
    shaderPack.heightmapShader.setParameter("screen_ratio", sf::Vector2f(1.f / renderTexture.getSize().x, 1.f / renderTexture.getSize().y));

    sf::Sprite sprite = shadowMap;
    sprite.move(getPosition());
    renderTexture.draw(sprite, &shaderPack.heightmapShader);
    renderTexture.display();

    shaderPack.heightmapShader.setParameter("heightmap_screen", shaderPack.heightmapScreen.getTexture());
    shaderPack.heightmapShader.setParameter("screen_ratio", sf::Vector2f(1.f / target.getSize().x, 1.f / target.getSize().y));
}

////////////////////////////////////////////////////////////
void Sprite3d::load(const sf::String& diffuseFilePath, const sf::String& normalFilePath, const sf::String& heightmapFilePath)
{
    diffuse.loadFromFile(diffuseFilePath);
    normal.loadFromFile(normalFilePath);
    heightmap.loadFromFile(heightmapFilePath);

    imgHeightmap = heightmap.copyToImage();

    diffuse.setRepeated(true);
    normal.setRepeated(true);
    heightmap.setRepeated(true);

    setTexture(diffuse);

    height = 160;
    Pos3d.z = 0;
 }

////////////////////////////////////////////////////////////
void Sprite3d::setPosition(float x, float y)
{
    sf::Sprite::setPosition(x ,y);

    Pos3d.x = x;
    Pos3d.y = y;
}

////////////////////////////////////////////////////////////
void Sprite3d::setPosition(float x, float y, float z)
{
    sf::Sprite::setPosition(x, y);

    Pos3d.x = x;
    Pos3d.y = y;
    Pos3d.z = z;
}

}
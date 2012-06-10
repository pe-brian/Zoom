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

#include <Zoom/Color.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) :
r(red),
g(green),
b(blue),
a(alpha) {}

////////////////////////////////////////////////////////////    
Color Color::getFromWebCode(const std::string& webColor)
{
	Uint8 r = 0, g = 0, b = 0;

	if( webColor.size() == 7 && webColor[0] == '#' )
	{
		std::istringstream(webColor.substr(1, 2)) >> std::hex >> r;
		std::istringstream(webColor.substr(3, 2)) >> std::hex >> g;
		std::istringstream(webColor.substr(5, 2)) >> std::hex >> b;
	}
	
	return Color(r, g, b);
}

////////////////////////////////////////////////////////////

// Red colors

const Color Color::IndianRed = Color(205, 92, 92);
const Color Color::LightCoral = Color(240, 128, 114);
const Color Color::Salmon = Color(250, 128, 114);
const Color Color::DarkSalmon = Color(233, 150, 122);
const Color Color::LightSalmon = Color(255, 160, 122);
const Color Color::Red = Color(255, 0, 0);
const Color Color::Crimson = Color(220, 20, 60);
const Color Color::FireBrick = Color(178, 34, 34);
const Color Color::DarkRed = Color(139, 0, 0);

// Pink colors

const Color Color::Pink = Color(255, 192, 203);
const Color Color::LightPink = Color(0, 0, 0);
const Color Color::HotPink = Color(0, 0, 0);
const Color Color::DeepPink = Color(0, 0, 0);
const Color Color::MediumVioletRed = Color(0, 0, 0);	
const Color Color::PaleVioletRed = Color(0, 0, 0);

// Orange colors

const Color Color::Coral = Color(0, 0, 0);
const Color Color::Tomato = Color(0, 0, 0);
const Color Color::OrangeRed = Color(0, 0, 0);
const Color Color::DarkOrange = Color(0, 0, 0);
const Color Color::Orange = Color(255, 165, 0);

// Yellow colors

const Color Color::Gold = Color(0, 0, 0);
const Color Color::Yellow = Color(255, 255, 0);
const Color Color::LightYellow = Color(0, 0, 0);
const Color Color::LemonChiffon = Color(0, 0, 0);
const Color Color::LightGoldenrodYellow = Color(0, 0, 0);
const Color Color::PapayaWhip = Color(0, 0, 0);
const Color Color::Moccasin = Color(0, 0, 0);
const Color Color::PeachPuff = Color(0, 0, 0);
const Color Color::PaleGoldenrod = Color(0, 0, 0);
const Color Color::Khaki = Color(0, 0, 0);
const Color Color::DarkKhaki = Color(0, 0, 0);

// Purple colors

const Color Color::Lavender = Color(0, 0, 0);
const Color Color::Thistle = Color(0, 0, 0);
const Color Color::Plum = Color(0, 0, 0);
const Color Color::Violet = Color(0, 0, 0);
const Color Color::Orchid = Color(0, 0, 0);
const Color Color::Fuchsia = Color(0, 0, 0);
const Color Color::Magenta = Color(0, 0, 0);
const Color Color::MediumOrchid = Color(0, 0, 0);
const Color Color::MediumPurple = Color(0, 0, 0);
const Color Color::BlueViolet = Color(0, 0, 0);
const Color Color::DarkViolet = Color(0, 0, 0);
const Color Color::DarkOrchid = Color(0, 0, 0);
const Color Color::DarkMagenta = Color(0, 0, 0);
const Color Color::Purple = Color(0, 0, 0);
const Color Color::Indigo = Color(0, 0, 0);
const Color Color::SlateBlue = Color(0, 0, 0);
const Color Color::DarkSlateBlue = Color(0, 0, 0);

// Green colors

const Color Color::GreenYellow = Color(0, 0, 0);
const Color Color::Chartreuse = Color(0, 0, 0);
const Color Color::LawnGreen = Color(0, 0, 0);
const Color Color::Lime = Color(0, 0, 0);
const Color Color::LimeGreen = Color(0, 0, 0);
const Color Color::PaleGreen = Color(152, 251, 152);
const Color Color::LightGreen = Color(0, 0, 0);
const Color Color::MediumSpringGreen = Color(0, 0, 0);
const Color Color::SpringGreen = Color(0, 255, 127);
const Color Color::MediumSeaGreen = Color(0, 0, 0);
const Color Color::SeaGreen = Color(0, 0, 0);
const Color Color::ForestGreen = Color(0, 0, 0);
const Color Color::Green = Color(0, 255, 0);
const Color Color::DarkGreen = Color(0, 100, 0);
const Color Color::YellowGreen = Color(0, 0, 0);
const Color Color::OliveDrab = Color(0, 0, 0);
const Color Color::Olive = Color(0, 0, 0);
const Color Color::DarkOliveGreen = Color(0, 0, 0);
const Color Color::MediumAquamarine = Color(0, 0, 0);
const Color Color::DarkSeaGreen = Color(0, 0, 0);
const Color Color::LightSeaGreen = Color(0, 0, 0);
const Color Color::DarkCyan = Color(0, 0, 0);
const Color Color::Teal = Color(0, 0, 0);

// Blue/Cyan colors

const Color Color::Aqua = Color(0, 0, 0);
const Color Color::Cyan = Color(0, 255, 255);
const Color Color::LightCyan = Color(0, 0, 0);
const Color Color::PaleTurquoise = Color(0, 0, 0);
const Color Color::Aquamarine = Color(0, 0, 0);
const Color Color::Turquoise = Color(0, 0, 0);
const Color Color::MediumTurquoise = Color(0, 0, 0);
const Color Color::DarkTurquoise = Color(0, 0, 0);
const Color Color::CadetBlue = Color(0, 0, 0);
const Color Color::SteelBlue = Color(0, 0, 0);
const Color Color::LightSteelBlue = Color(0, 0, 0);
const Color Color::PowderBlue = Color(0, 0, 0);
const Color Color::LightBlue = Color(0, 0, 0);
const Color Color::SkyBlue = Color(0, 0, 0);
const Color Color::LightSkyBlue = Color(0, 0, 0);
const Color Color::DeepSkyBlue = Color(0, 0, 0);
const Color Color::DodgerBlue = Color(0, 0, 0);
const Color Color::CornflowerBlue = Color(0, 0, 0);
const Color Color::MediumSlateBlue = Color(0, 0, 0);
const Color Color::RoyalBlue = Color(0, 0, 0);
const Color Color::Blue = Color(0, 0, 255);
const Color Color::MediumBlue = Color(0, 0, 0);
const Color Color::DarkBlue = Color(0, 0, 0);
const Color Color::Navy = Color(0, 0, 0);
const Color Color::MidnightBlue = Color(0, 0, 0);

// Brown colors

const Color Color::Cornsilk = Color(0, 0, 0);
const Color Color::BlanchedAlmond = Color(0, 0, 0);
const Color Color::Bisque = Color(0, 0, 0);
const Color Color::NavajoWhite = Color(0, 0, 0);
const Color Color::Wheat = Color(0, 0, 0);
const Color Color::BurlyWood = Color(0, 0, 0);
const Color Color::Tan = Color(0, 0, 0);
const Color Color::RosyBrown = Color(0, 0, 0);
const Color Color::SandyBrown = Color(0, 0, 0);
const Color Color::Goldenrod = Color(0, 0, 0);
const Color Color::DarkGoldenrod = Color(0, 0, 0);
const Color Color::Peru = Color(0, 0, 0);
const Color Color::Chocolate = Color(0, 0, 0);
const Color Color::SaddleBrown = Color(0, 0, 0);
const Color Color::Sienna = Color(0, 0, 0);
const Color Color::Brown = Color(150, 75, 0);
const Color Color::Maroon = Color(0, 0, 0);

// White colors

const Color Color::Translucent = Color(0, 0, 0, 0);
const Color Color::White = Color(255, 255, 255);
const Color Color::Snow = Color(0, 0, 0);
const Color Color::Honeydew = Color(0, 0, 0);
const Color Color::MintCream = Color(0, 0, 0);
const Color Color::Azure = Color(0, 0, 0);
const Color Color::AliceBlue = Color(0, 0, 0);
const Color Color::GhostWhite = Color(0, 0, 0);
const Color Color::WhiteSmoke = Color(0, 0, 0);
const Color Color::Seashell = Color(0, 0, 0);
const Color Color::Beige = Color(0, 0, 0);
const Color Color::OldLace = Color(0, 0, 0);
const Color Color::FloralWhite = Color(0, 0, 0);
const Color Color::Ivory = Color(0, 0, 0);
const Color Color::AntiqueWhite = Color(0, 0, 0);
const Color Color::Linen = Color(0, 0, 0);
const Color Color::LavenderBlush = Color(0, 0, 0);
const Color Color::MistyRose = Color(0, 0, 0);

// Gray colors

const Color Color::Gainsboro = Color(0, 0, 0);
const Color Color::LightGrey = Color(0, 0, 0);
const Color Color::Silver = Color(0, 0, 0);
const Color Color::DarkGray = Color(0, 0, 0);
const Color Color::Gray = Color(0, 0, 0);
const Color Color::DimGray = Color(0, 0, 0);
const Color Color::LightSlateGray = Color(0, 0, 0);
const Color Color::SlateGray = Color(0, 0, 0);
const Color Color::DarkSlateGray = Color(0, 0, 0);
const Color Color::Black = Color(0, 0, 0);

}
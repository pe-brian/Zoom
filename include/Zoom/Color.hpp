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

#ifndef ZOOM_COLOR_HPP
#define ZOOM_COLOR_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <sstream>
#include <Zoom/Config.hpp>

namespace zin
{
	
class ZOOM_API Color
{
public:

    ////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////
    Color(Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0, Uint8 alpha = 255);
    
    ////////////////////////////////////////////////////////////
    // Get a color from a web color code
    ////////////////////////////////////////////////////////////
    static Color getFromWebCode(const std::string& webCode);

    ////////////////////////////////////////////////////////////
    // Static data
    ////////////////////////////////////////////////////////////
	static const Color IndianRed;
	static const Color LightCoral;
	static const Color Salmon;
	static const Color DarkSalmon;
	static const Color LightSalmon;
	static const Color Crimson;
    static const Color Red;
    static const Color FireBrick;
    static const Color DarkRed;
    static const Color Pink;
    static const Color LightPink;
    static const Color HotPink;
    static const Color DeepPink;
    static const Color MediumVioletRed;
    static const Color PaleVioletRed;
    static const Color Coral;
    static const Color Tomato;
    static const Color OrangeRed;
    static const Color DarkOrange;
    static const Color Orange;
    static const Color Gold;
    static const Color Yellow;
    static const Color LightYellow;
    static const Color LemonChiffon; 
    static const Color LightGoldenrodYellow;
    static const Color PapayaWhip;
    static const Color Moccasin;
    static const Color PeachPuff;
    static const Color PaleGoldenrod;
    static const Color Khaki;
    static const Color DarkKhaki;
    static const Color Lavender;
    static const Color Thistle;
    static const Color Plum;
    static const Color Violet;
    static const Color Orchid;
    static const Color Fuchsia;
    static const Color Magenta;
    static const Color MediumOrchid;
    static const Color MediumPurple;
    static const Color BlueViolet;
    static const Color DarkViolet;
    static const Color DarkOrchid;
    static const Color DarkMagenta;
    static const Color Purple;
    static const Color Indigo;
    static const Color SlateBlue;
    static const Color DarkSlateBlue;
    static const Color GreenYellow;
    static const Color Chartreuse;
    static const Color LawnGreen;
    static const Color Lime;
    static const Color LimeGreen;
    static const Color PaleGreen;
    static const Color LightGreen;
    static const Color MediumSpringGreen;
    static const Color SpringGreen;
    static const Color MediumSeaGreen;
    static const Color SeaGreen;
    static const Color ForestGreen;
    static const Color Green;
    static const Color DarkGreen;
    static const Color YellowGreen;
    static const Color OliveDrab;
    static const Color Olive;
    static const Color DarkOliveGreen;
    static const Color MediumAquamarine;
    static const Color DarkSeaGreen;
    static const Color LightSeaGreen;
    static const Color DarkCyan;
    static const Color Teal;
    static const Color Aqua;
    static const Color Cyan;
    static const Color LightCyan;
    static const Color PaleTurquoise;
    static const Color Aquamarine;
    static const Color Turquoise;
    static const Color MediumTurquoise;
    static const Color DarkTurquoise;
    static const Color CadetBlue;
    static const Color SteelBlue;
    static const Color LightSteelBlue;
    static const Color PowderBlue;
    static const Color LightBlue;
    static const Color SkyBlue;
    static const Color LightSkyBlue;
    static const Color DeepSkyBlue;
    static const Color DodgerBlue;
    static const Color CornflowerBlue;
    static const Color MediumSlateBlue;
    static const Color RoyalBlue;
    static const Color Blue;
    static const Color MediumBlue;
    static const Color DarkBlue;
    static const Color Navy;
    static const Color MidnightBlue;
    static const Color Cornsilk;
    static const Color BlanchedAlmond;
    static const Color Bisque;
    static const Color NavajoWhite;
    static const Color Wheat;
    static const Color BurlyWood;
    static const Color Tan;
    static const Color RosyBrown;
    static const Color SandyBrown;
    static const Color Goldenrod;
    static const Color DarkGoldenrod;
    static const Color Peru;
    static const Color Chocolate;
    static const Color SaddleBrown;
    static const Color Sienna;
    static const Color Brown;
    static const Color Maroon;
    static const Color Translucent;
    static const Color White;
    static const Color Snow;
    static const Color Honeydew;
    static const Color MintCream;
    static const Color Azure;
    static const Color AliceBlue;
    static const Color GhostWhite;
    static const Color WhiteSmoke;
    static const Color Seashell;
    static const Color Beige;
    static const Color OldLace;
    static const Color FloralWhite;
    static const Color Ivory;
    static const Color AntiqueWhite;
    static const Color Linen;
    static const Color LavenderBlush;
    static const Color MistyRose;
    static const Color Gainsboro;
    static const Color LightGrey;
    static const Color Silver;
    static const Color DarkGray;
    static const Color Gray;
    static const Color DimGray;
    static const Color LightSlateGray;
    static const Color SlateGray;
    static const Color DarkSlateGray;
    static const Color Black;

	Uint8 r, g, b, a;
};

}

#endif // ZOOM_COLOR_HPP

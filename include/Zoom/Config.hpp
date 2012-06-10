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
/////////////////////////////////////////////////////////////

#ifndef ZOOM_CONFIG_HPP
#define ZOOM_CONFIG_HPP


////////////////////////////////////////////////////////////
// Define the ZOOM version
////////////////////////////////////////////////////////////
#define ZOOM_VERSION_MAJOR 1
#define ZOOM_VERSION_MINOR 0

////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(ZOOM_SYSTEM_WINDOWS) && !defined(ZOOM_STATIC)
    #ifdef ZOOM_EXPORTS

     // From DLL side, we must export
        #define ZOOM_API __declspec(dllexport)

    #else

     // From client application side, we must import
        #define ZOOM_API __declspec(dllimport)

    #endif

 // For Visual C++ compilers, we also need to turn off this annoying C4251 warning.
 // You can read lots ot different things about it, but the point is the code will
 // just work fine, and so the simplest way to get rid of this warning is to disable it
    #ifdef _MSC_VER

        #pragma warning(disable : 4251)

    #endif

#else

    // Other platforms and static build don't need these export macros

    #define ZOOM_API

#endif

////////////////////////////////////////////////////////////
// Define portable fixed-size types
////////////////////////////////////////////////////////////
namespace zin
{
    // All "common" platforms use the same size for char, short and int
    // (basically there are 3 types for 3 sizes, so no other match is possible),
    // we can use them without doing any kind of check

    // 8 bits integer types
    typedef signed   char Int8;
    typedef unsigned char Uint8;

    // 16 bits integer types
    typedef signed   short Int16;
    typedef unsigned short Uint16;

    // 32 bits integer types
    typedef signed   int Int32;
    typedef unsigned int Uint32;

    // 64 bits integer types
    #if defined(_MSC_VER)
        typedef signed   __int64 Int64;
        typedef unsigned __int64 Uint64;
    #else
        typedef signed   long long Int64;
        typedef unsigned long long Uint64;
    #endif

} // namespace Zin

#endif // ZOOM_CONFIG_HPP
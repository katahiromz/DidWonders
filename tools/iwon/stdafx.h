////////////////////////////////////////////////////////////////////////////

#if !defined(__cplusplus) || (__cplusplus < 199711L)
    #error Modern C++ compiler required! You lose.
#endif

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#undef __STRICT_ANSI__

#ifndef __NO_INLINE__
    #define __NO_INLINE__   // https://github.com/g-truc/glm/issues/300
#endif

////////////////////////////////////////////////////////////////////////////

#include <cstdlib>          // C standard library
#include <cstring>          // C string
#include <cassert>          // for assert

#include <iostream>         // for std::cout, std::cerr
#include <fstream>          // for std::ifstream
#include <sstream>          // for std::stringstream
#include <iomanip>          // for std::setfill, std::setw
#include <vector>           // for std::vector
#include <string>           // for std::string
#include <map>              // for std::map
#include <unordered_map>    // for std::unordered_map
#include <set>              // for std::set
#include <algorithm>        // for std::sort, std::unique
#include <new>              // for std::bad_alloc

////////////////////////////////////////////////////////////////////////////

#include <memory>
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;
using std::make_shared;

////////////////////////////////////////////////////////////////////////////

#include <windows.h>

////////////////////////////////////////////////////////////////////////////

#include "Location.h"       // CR_Location
#include "Main.h"
#include "TypeSystem.h"
#include "StringAssortNew.h"

////////////////////////////////////////////////////////////////////////////

#define EXTENDS_MOBJECT
#include "TextToText.hpp"

////////////////////////////////////////////////////////////////////////////

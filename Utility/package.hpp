#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

//Debugging
#if DEBUG
#include <assert.h>
#else
#ifdef assert
#undef assert
#endif
#define assert(x) { }
#endif

//Some standard headers from C and C++
#include <math.h>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <vector>
#include <bitset>

//OpenGL-specific
#include <GL/glew.h>
#include <GL/gl.h>

//Patterns
#include "tSingleton.hpp"
#include "tOptional.hpp"

//Math
#include "tMath.hpp"
#include "tVector.hpp"
#include "tMatrix.hpp"
#include "tRect.hpp"

//System Time, Input, and Audio
#include "tTimer.hpp"
#include "tInputEvent.hpp"
//#include "tSound.h"

//OpenGL helper classes
#include "tSurface.hpp"
#include "tTexture.hpp"
#include "tShader.hpp"
#include "tProgram.hpp"

//Advanced OpenGL Helper classes
#include "tViewport.hpp"
#include "tAutosizeViewport.hpp"
#include "tSpriteFont.hpp"
#include "tSpriteBatch.hpp"
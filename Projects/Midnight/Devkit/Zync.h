// Copyright (c) 2013 Loren Hoffman
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <sstream>
#include <iostream>
#include <assert.h>
#include <map>
#include <vector>
#include <math.h>

// Libraries
//

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <SOIL.h>

// Configurations
//

#define ASSET_DIR "Assets/"

// Debug system extensions
//

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define FULL_DEBUG_MESSAGE __FILENAME__ << ":" << __LINE__ << " "

#ifdef _DEBUG
	#define DEBUG_PREFIX FULL_DEBUG_MESSAGE
#else
	#ifndef NDEBUG
		#define DEBUG_PREFIX FULL_DEBUG_MESSAGE
	#else
		#define DEBUG_PREFIX ""
	#endif
#endif

#define LogMessage(X) {std::stringstream ss; ss << DEBUG_PREFIX << X; debug.Log(ss.str());}
#define LogWarning(X) {std::stringstream ss; ss << DEBUG_PREFIX << X; debug.Warning(ss.str());}
#define LogError(X) {std::stringstream ss; ss << DEBUG_PREFIX <<  X; debug.Error(ss.str());}

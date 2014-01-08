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

struct Vec2
{
	float x;
	float y;

	Vec2(float _x = 0.f, float _y = 0.f)
		: x(_x)
		, y(_y)
	{}

	void Set(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

struct Rect
{
	float x;
	float y;
	float width;
	float height;
};

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color(float _r = 0.f, float _g = 0.f, float _b = 0.f, float _a = 1.f)
		: r(_r)
		, g(_g)
		, b(_b)
		, a(_a)
	{}
};
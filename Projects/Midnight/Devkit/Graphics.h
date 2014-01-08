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

enum Anchor
{
	E_BOTTOMLEFT,
	E_LEFT,
	E_TOPLEFT,
	E_BOTTOM,
	E_CENTER,
	E_TOP,
	E_BOTTOMRIGHT,
	E_RIGHT,
	E_TOPRIGHT,
	NumAnchors
};

struct DrawOperation;
struct Texture;

class Graphics
{
public:
	Graphics()
		: _drawOperations(2000)
		, _drawCount(0)
	{}

	~Graphics()
	{}

	void Initialize(int pixelSize)
	{
		_pixelSize = (float)pixelSize;

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}

	int GetPixelSize() const
	{
		return _pixelSize;
	}

	void CleanUp()
	{
		_drawOperations.clear();
		_textureMap.clear();
	}

	void SetClearColor(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	Texture* GetTexture(const std::string& textureName)
	{
		TextureMap::iterator tex = _textureMap.find(textureName);
		if(tex != _textureMap.end())
		{
			return &tex->second;
		}

		return this->LoadTexture(textureName);
	}

	void Draw(Texture* texture, float x, float y, Anchor anchor = E_BOTTOMLEFT, float angle = 0.f)
	{
		debug.Assert(texture != NULL, "Null texture cannot be used for Draw");

		if(_drawCount == _drawOperations.capacity())
		{
			_drawOperations.reserve(_drawOperations.capacity() * 2);
		}

		DrawOperation& op = _drawOperations[_drawCount++];
		op.Reset();
		op.texture = texture;
		op.position.x = x;
		op.position.y = y;
		op.anchor = anchor;
		op.angle = angle;
	}

	void Render()
	{
		int width, height;
		system.GetScreenSize(&width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.f, width, 0.f, height, 1.f, -1.f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glScalef(_pixelSize, _pixelSize, 1.f);

		for(int index = 0; index < _drawCount; ++index)
		{
			DrawOperation& op = _drawOperations[index];

			float x = op.position.x;
			float y = op.position.y;
			float w = op.texture->width;
			float h = op.texture->height;
			float hw = w * 0.5f;
			float hh = h * 0.5f;

			glPushMatrix();

			// Position
			glTranslatef(x, y, 0.f);

			// Rotation
			glRotatef(op.angle, 0.f, 0.f, 1.f);

			// Anchor translation
			switch(op.anchor)
			{
				case E_LEFT:        glTranslatef(0.f, -hh, 0.f); break;
				case E_TOPLEFT:     glTranslatef(0.f,  -h, 0.f); break;
				case E_BOTTOM:      glTranslatef(-hw, 0.f, 0.f); break;
				case E_CENTER:      glTranslatef(-hw, -hh, 0.f); break;
				case E_TOP:         glTranslatef(-hw,  -h, 0.f); break;
				case E_BOTTOMRIGHT: glTranslatef( -w, 0.f, 0.f); break;
				case E_RIGHT:       glTranslatef( -w, -hh, 0.f); break;
				case E_TOPRIGHT:    glTranslatef( -w,  -h, 0.f); break;
				default: break;
			}

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, op.texture->id);

			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex3f(0.f, 0.f, 0.f);
				glTexCoord2f(0, 1);
				glVertex3f(0.f, h, 0.f);
				glTexCoord2f(1, 1);
				glVertex3f(w, h, 0.f);
				glTexCoord2f(1, 0);
				glVertex3f(w, 0.f, 0.f);
			glEnd();

			glPopMatrix();
		}

		_drawCount = 0;
	}

private:
	Texture* LoadTexture(const std::string& textureName)
	{
		// Check for already loaded (this check should compile out)
		assert(_textureMap.find(textureName) == _textureMap.end());

		// Get the full asset path
		std::string fullPath = ASSET_DIR + textureName;

		// Load the image
		unsigned int id = SOIL_load_OGL_texture(
			fullPath.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
		);

		// If it loaded succesfully set up a Texture
		if(id != 0)
		{
			_textureMap[textureName].Set(id);
		}

		// Error if it didn't load
		if(_textureMap.find(textureName) == _textureMap.end())
		{
			LogError("Failed to load texture: " << textureName);
		}

		// Return the texture
		return &_textureMap[textureName];
	}

	typedef std::map<std::string, Texture> TextureMap;
	TextureMap _textureMap;

	typedef std::vector<DrawOperation> DrawOperations;
	DrawOperations _drawOperations;

	int _drawCount;
	float _pixelSize;
};

struct Texture
{
	unsigned int id;
	int width;
	int height;

	Texture()
		: id(0)
		, width(0)
		, height(0)
	{}

	~Texture()
	{
		if(id != 0)
		{
			glDeleteTextures(1, &id);
			id = 0;
		}
	}

	void Set(unsigned int id)
	{
		debug.Assert(id > 0, "Cannot set a texture with zero id");

		this->id = id;

		// Bind
		glBindTexture(GL_TEXTURE_2D, this->id);

		// Set sampling
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Get width and height
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &this->width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &this->height);

		// Clear bind
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

struct DrawOperation
{
	Texture* texture;
	Vec2 position;
	Anchor anchor;
	float angle;

	DrawOperation()
		: texture(NULL)
	{}

	void Reset()
	{
		texture = NULL;
		position.Set(0.f, 0.f);
		anchor = E_BOTTOMLEFT;
		angle = 0.f;
	}
};
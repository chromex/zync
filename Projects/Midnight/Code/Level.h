// Story
// * Load textures in ctor
// * Textures owned by graphics
// * Queue up draw

class Level : public Scene
{
public:
	Level()
	{
		graphics.SetClearColor(Color(0.2f, 0.2f, 0.2f));
		_texture = graphics.GetTexture("dude.png");
	}

	virtual void Update()
	{
		graphics.Draw(_texture, 50, 50);
		graphics.Draw(_texture, 175, 100);

		// anchor options for the draw call
		// rotation
		// scale
	}

private:
	Texture* _texture;
};
// Story
// * Add draw scale
// * Add player input callbacks OR use state queries

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
		float x = system.GetWidth() / 2.f;
		float y = system.GetHeight() / 2.f;

		graphics.Draw(_texture, x + 50 * sin(system.GetTime()), y, E_CENTER, system.GetTime() * 150.f);
		graphics.Draw(_texture, x, y + 25 * sin(system.GetTime()), E_BOTTOM, system.GetTime() * -120.f);

		// scale
	}

private:
	Texture* _texture;
};
#include <Zync.h>

struct zync
{
	// Zync systems
	#include <Debug.h>
	#include <Maths.h>
	#include <Graphics.h>
	#include <Scene.h>
	#include <System.h>

	// Midnight systems
	#include "Level.h"

	// Globals
	static Debug debug;
	static Graphics graphics;
	static System system;
};

zync::Debug zync::debug;
zync::Graphics zync::graphics;
zync::System zync::system;

int main(void)
{
	zync::system.Setup(640, 480, 4, "Midnight");
	zync::system.Run(new zync::Level);
	zync::graphics.CleanUp();
}
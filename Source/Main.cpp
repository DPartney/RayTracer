#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"

int main(int, char**)
{
	std::cout << "Hello World";

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("main", 400, 300);
	Canvas canvas(400, 300, renderer);


	Random rng = Random();
	rng.seedRandom((unsigned int)time(nullptr));

	bool quit = false;
	while (!quit)
	{
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++)  canvas.DrawPoint({ rng.random(0, 400), rng.random(0, 300) }, { rng.random01(), rng.random01(), rng.random01(), 1 });
		canvas.Update();
		renderer.PresentCanvas(canvas);

		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}
#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

int main(int, char**)
{
	std::cout << "Hello World";

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("main", 800, 600);
	Canvas canvas(400, 300, renderer);


	Random rng = Random();
	rng.seedRandom((unsigned int)time(NULL));

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene = { color3_t{ 0, 1, 1}, color3_t{0, 1, 0} }; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

	for (auto i = 0; i < 10; i++)
	{
		auto sphere = std::make_unique<Sphere>(glm::vec3{ rng.random(-2, 2), rng.random(-2, 2), rng.random(-2, 2) }, 0.1f, material);
		scene.AddObject(std::move(sphere));
	}

	bool quit = false;
	while (!quit)
	{
		/*
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++)  canvas.DrawPoint({ rng.random(0, 400), rng.random(0, 300) }, { rng.random01(), rng.random01(), rng.random01(), 1 });
		canvas.Update();
		renderer.PresentCanvas(canvas);

		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);

		canvas.Update();
		renderer.PresentCanvas(canvas);
		*/
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

		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}
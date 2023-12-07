#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitScene03(Scene& scene, const Canvas& canvas);

int main(int, char**)
{
	std::cout << "Hello World";

	const int width = 800;
	const int height = 600;
	const int samples = 250;
	const int depth = 5;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("main", width, height);
	Canvas canvas(width, height, renderer);

	seedRandom((unsigned int)time(NULL));

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	scene.SetCamera(camera);

	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	std::shared_ptr<Material> material;

	InitScene01(scene, canvas);

	// Render Scene
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
	canvas.Update();

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
		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto mesh = std::make_unique<Mesh>(std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2)));
	mesh->Load("Models/cube.obj", glm::vec3{ 0, 0.5f, -5 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ 1 }, glm::vec3{ 0 }, glm::vec3{ -1 }, std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2)));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	//scene.AddObject(std::move(triangle));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 0, 1, 0.5f }));
	mesh->Load("Models/cube.obj", glm::vec3{ 0, 0.5f, -2 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}

void InitScene03(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 100.0f, aspectRatio);
	scene.SetCamera(camera);

	auto leftWall = std::make_unique<Plane>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 1,0,0 }));
	scene.AddObject(std::move(leftWall));

	auto rightWall = std::make_unique<Plane>(glm::vec3{ 2, 0, 0 }, glm::vec3{ -1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0,1,0 }));
	scene.AddObject(std::move(rightWall));

	auto backWall = std::make_unique<Plane>(glm::vec3{ 0, 0, -2 }, glm::vec3{ 0, 0, 1 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(backWall));

	auto floor = std::make_unique<Plane>(glm::vec3{ 0, -2, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(floor));

	auto celing = std::make_unique<Plane>(glm::vec3{ 0, 2, 0 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(celing));

	auto cube = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 0, 1 }));
	cube->Load("models/cube.obj", glm::vec3{ -1, -1.5, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(cube));

	auto sphere = std::make_unique<Sphere>(glm::vec3{ 1, -1.5, 1 }, 0.5f, std::make_shared<Lambertian>(color3_t{ 0, 0.25f, 0.5f }));
	// add sphere to the scene
	scene.AddObject(std::move(sphere));

	auto light = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 5));
	light->Load("models/cube.obj", glm::vec3{ 0, 2, 0 }, glm::vec3{ 0, 0, 0 });
	scene.AddObject(std::move(light));
}

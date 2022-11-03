#include "Engine.h" 
#include <iostream> 

int main(int argc, char** argv)
{
	LOG("*-Application Started-*");

	neu::InitializeMemory();

	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	LOG("*-Engine Initialized-*");

	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	LOG("*-Window Initialized-*");

	// load scene 
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/textures.scn");



	glm::mat4 model { 1 };
	glm::mat4 projection = glm::perspective(45.0f, (neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight()), 0.01f, 100.0f);
	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 3 };
	float speed = 3;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		//glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3{0,0,0},glm::vec3 {0,1,0});
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		auto actor = scene->GetActorFromName("Spot");
		if (actor)
		{
			actor->m_transform.rotation.y += neu::g_time.deltaTime * 90.0f;
		}

		/*auto material = neu::g_resources.Get<neu::Material>("Materials/multi.mtrl");
		if (material)
		{
			material->uv_offset.x += neu::g_time.deltaTime;
		}*/

		scene->Update();

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}
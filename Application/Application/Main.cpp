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
	neu::g_gui.Initialize(neu::g_renderer);

	LOG("*-Window Initialized-*");

	// load scene 
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/cubemap.scn");

	glm::mat4 model { 1 };
	glm::mat4 projection = glm::perspective(45.0f, (neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight()), 0.01f, 100.0f);
	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 3 };
	float speed = 3;

	glm::vec3 pos = {0,0,0};

	glm::vec3 rot{ 0,0,0 };

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		//glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3{0,0,0},glm::vec3 {0,1,0});
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		auto actor = scene->GetActorFromName("Model");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave
			actor->m_transform.position = pos;
		}

		ImGui::Begin("Hello!");

		ImGui::Button("Press Me!");
		ImGui::SliderFloat("X", &pos[0], -5.0f, 5.0f);
		ImGui::SliderFloat("Y", &pos[1], -5.0f, 5.0f);
		ImGui::SliderFloat("Z", &pos[2], -5.0f, 5.0f);


		ImGui::End();

		scene->Update();

		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);

		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}
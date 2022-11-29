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

	// create framebuffer texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(512, 512);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	//create framebuffer
	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");

	// load scene 
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/rtt.scn");

	glm::mat4 model { 1 };
	glm::mat4 projection = glm::perspective(45.0f, (neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight()), 0.01f, 100.0f);
	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 3 };
	float speed = 3;

	glm::vec3 pos = {0,0,0};
	float ri = 1.0f;
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

		auto program = neu::g_resources.Get<neu::Program>("shaders/fx/refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}

		ImGui::Begin("Hello!");

		ImGui::Button("Press Me!");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat3("Refraction", &ri, 0.01f, 1, 3);

		ImGui::End();

		scene->Update();

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

		// render pass 1
		glViewport(0, 0, 512, 512);
		framebuffer->Bind();

		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);

		framebuffer->Unbind();

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(true);
			}
		}

		// render bind 2
		glViewport(0, 0, 800, 600);

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
#include "Engine.h" 
#include <iostream> 

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
										    
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
										    
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
										    
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
										    
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
										    
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f
};

int main(int argc, char** argv)
{
	LOG("*-Application Starter-*");

	neu::InitializeMemory();

	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	LOG("*-Engine Initialized-*");

	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	LOG("*-Window Initialized-*");

	// create vertex buffer
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// create vertex array
	std::shared_ptr<neu::VertexBuffer> vb = neu::g_resources.Get<neu::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vb->SetAttribute(2, 3, 6 * sizeof(float), 3 * sizeof(float));

	// create program
	std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("Shaders/basic.prog", GL_PROGRAM);
	program->Link();
	program->Use();

	// create material 
	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/box.mtrl");
	material->Bind();

	//material->GetProgram()->SetUniform("tint", glm::vec3(1, 0, 0));
	material->GetProgram()->SetUniform("scale", 0.5f);

	glm::mat4 model { 1 };
	glm::mat4 projection = glm::perspective(45.0f, neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight(), 0.01f, 100.0f);
	glm::vec3 cameraPosition = glm::vec3{ 0, 2, 3 };
	float speed = 3;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;
		
		//Uniforms

		//add input to move camera

		//glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3{0,0,0},glm::vec3 {0,1,0});
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		model = glm::eulerAngleXYZ(0.0f, neu::g_time.time, 0.0f);//has never worked

		//move left or right (x)
		if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::KeyState::Held) cameraPosition.x -= speed * neu::g_time.deltaTime;
		if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held) cameraPosition.x += speed * neu::g_time.deltaTime;

		//move up or down (y)
		if (neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::KeyState::Held) cameraPosition.y += speed * neu::g_time.deltaTime;
		if (neu::g_inputSystem.GetKeyState(neu::key_down) == neu::InputSystem::KeyState::Held) cameraPosition.y -= speed * neu::g_time.deltaTime;

		//rotate around (z)
		if (neu::g_inputSystem.GetKeyState(neu::key_minus) == neu::InputSystem::KeyState::Held) cameraPosition.z -= speed * neu::g_time.deltaTime;
		if (neu::g_inputSystem.GetKeyState(neu::key_plus) == neu::InputSystem::KeyState::Held) cameraPosition.z += speed * neu::g_time.deltaTime;

		//material->GetProgram()->SetUniform("scale", std::sin(neu::g_time.time * 3));

		glm::mat4 mvp = projection * view * model;
		material->GetProgram()->SetUniform("mvp", mvp);

		neu::g_renderer.BeginFrame();

		vb->Draw();

		//for loop(all transforms)
		//{
		//	// update transform rotation
		//	transforms[i].rotation += <glm::vec3 to rotate by>;

		//	// create mvp matrix
		//	glm::mat4 mvp = projection * view * (glm::mat4)transforms[i];
		//	material->GetProgram()-> <set uniform for mvp>;

		//	<draw vertex buffer>;
		//}

		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();

	return 0;
}
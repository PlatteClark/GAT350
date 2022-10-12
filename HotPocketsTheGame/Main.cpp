#include "Engine.h" 
#include <iostream> 

float points[] = {
	 0.0f,  0.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	-0.5f,  0.0f, 0.0f,

	-0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f

};

glm::vec3 colors[] = {
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 0},
	{0, 0, 1},
	{0, 1, 1},
	{1, 1, 1}
};

int main(int argc, char** argv)
{
	squampernaut::InitializeMemory();

	squampernaut::SetFilePath("../Assets");

	squampernaut::Engine::Instance().Initialize();
	squampernaut::Engine::Instance().Register();

	squampernaut::g_renderer.CreateWindow("Game", 800, 600, false);

	// create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);
	
	// create color vertex buffer
	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader

	std::shared_ptr<squampernaut::Shader> vs = squampernaut::g_resources.Get<squampernaut::Shader>("Shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<squampernaut::Shader> fs = squampernaut::g_resources.Get<squampernaut::Shader>("Shaders/basic.frag", GL_FRAGMENT_SHADER);
	
	//GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vs, 1, &vertex_shader, NULL);
	//glCompileShader(vs);
	//GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fs, 1, &fragment_shader, NULL);
	//glCompileShader(fs);

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs->m_shader);
	glAttachShader(program, vs->m_shader);
	glLinkProgram(program);
	glad_glUseProgram(program);

	GLint uniform1 = glGetUniformLocation(program, "scale");
	GLint uniform2 = glGetUniformLocation(program, "tint");
	GLint uniform3 = glGetUniformLocation(program, "transform");

	glUniform3f(uniform2, 1, 1, 1);

	glm::mat4 mx{ 1 };


	bool quit = false;
	while (!quit)
	{
		squampernaut::Engine::Instance().Update();

		if (squampernaut::g_inputSystem.GetKeyState(squampernaut::key_escape) == squampernaut::InputSystem::KeyState::Pressed) quit = true;
		
		glUniform1f(uniform1, std::sin(squampernaut::g_time.time * 1));
		mx = glm::eulerAngleXYZ(0.0f, 0.0f, squampernaut::g_time.time);
		glUniformMatrix4fv(uniform3, 1, GL_FALSE, glm::value_ptr(mx));

		squampernaut::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		squampernaut::g_renderer.EndFrame();
	}

	squampernaut::Engine::Instance().Shutdown();
	return 0;
}
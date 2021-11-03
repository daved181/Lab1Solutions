// GL Extension Wrangler
#include <GL/glew.h>
#include <cmath>
// http://www.glfw.org/faq.html#what-is-glfw
//OpenGL doesn't have a way of creating window, this does it in an OS-independent way
#include <GLFW/glfw3.h>
#include <cstdlib>  
#include <iostream>
#include "readfile.hpp"

//-------------------------------------------------------------------------//
// You can store the rotation angles here, for example
float g_rotation[2] = {0.0f, 0.0f};
//-------------------------------------------------------------------------//

void MUL_4x4 (GLfloat (*C)[4], const GLfloat (*A)[4], const GLfloat (*B)[4])
{
	//-------------------------------------------------------------------------//
	// YOUR CODE GOES HERE
	// Compute C = A x B
	//-------------------------------------------------------------------------//
	for (int I = 0; I < 4; ++I)
	{
		for (int J = 0; J < 4; ++J)
		{
			float SumElements = 0.0f;
			for (int K = 0; K < 4; ++K)
			{
				SumElements += A[I][K] * B[K][J];
			}
			C[I][J] = SumElements;
		}
	}
}

void invertMatrix (float (*C)[4], const float (*A)[4])
{
	// Compute C = A^(-1) for a transformation matrix.
	

	// Optional, only if you want to play with a more exciting view
	// transform than a simple translation.
  
	// (The rotation part can be inverted separately from the
	// translation part and the last row is the same.)
}


void checkShaderCompileError(GLint shaderID)
{
	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
 
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::string errorLog;
		errorLog.resize(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		std::cout << "shader compilation failed:" << std::endl;
		std::cout << errorLog << std::endl;
		return;
	}
	else
		std::cout << "shader compilation success." << std::endl;
    
	return;
}



  
static void error_callback(int error, const char* description)
{
	std::cerr << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
    
	if ((key == GLFW_KEY_R) && action == GLFW_PRESS)
	{
		//implement reloading of the shaders on the fly
		std::string vertex_shader_str = readFile("../lab1-6_vs.glsl");
		std::string fragment_shader_str = readFile("../lab1-6_fs.glsl");

		const char* vertex_shader_src = vertex_shader_str.c_str();
		const char* fragment_shader_src = fragment_shader_str.c_str();

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader_src, NULL);
		glCompileShader(vs);
		checkShaderCompileError(vs);

		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader_src, NULL);
		glCompileShader(fs);
		checkShaderCompileError(fs);

		GLuint shader_program = glCreateProgram();
		glAttachShader(shader_program, fs);
		glAttachShader(shader_program, vs);
		glLinkProgram(shader_program);
		glDeleteShader(vs);
		glDeleteShader(fs);
		glUseProgram(shader_program);
	} 

	//-------------------------------------------------------------------------//
	// YOUR CODE GOES HERE
	// Update rotation angle here, for example
	//-------------------------------------------------------------------------//

	if ((key == GLFW_KEY_RIGHT) && ((action == GLFW_PRESS) || action == GLFW_REPEAT)) {
		g_rotation[1] = g_rotation[1] + 0.1f;
	}
	if ((key == GLFW_KEY_LEFT) && ( (action == GLFW_PRESS) || action==GLFW_REPEAT) ) {
		g_rotation[1] = g_rotation[1] - 0.1f;
	}
	if ((key == GLFW_KEY_UP) && ( (action == GLFW_PRESS) || action==GLFW_REPEAT) ) {
		g_rotation[0] = g_rotation[0] - 0.1f;
	}
	if ((key == GLFW_KEY_DOWN) && ( (action == GLFW_PRESS) || action==GLFW_REPEAT) ) {
		g_rotation[0] = g_rotation[0] + 0.1f;
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


int main(int argc, char const *argv[])
{
	// start GL context and O/S window using the GLFW helper library
  
	glfwSetErrorCallback(error_callback);
	if( !glfwInit() )
		exit(EXIT_FAILURE);
  
	GLFWwindow* window = glfwCreateWindow (640, 480, "Hello Cube", NULL, NULL);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
	int w_height = 600;
	int w_width = 800;

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent (window);
                                  
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit ();

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"


	//-------------------------------------------------------------------------//
	// COPY FROM lab1-5
	// Geometry, VBO, EBO, VAO
	// load and compile shaders  "../lab1-6_vs.glsl" and "../lab1-6_fs.glsl"
	//-------------------------------------------------------------------------//
	GLfloat cube_vertices[] = {
		
		-0.5, 0.5,   -0.5,
		-0.5, -0.5,  -0.5,
		0.5,  -0.5,  -0.5,
		0.5,  0.5,   -0.5,
		
		0.5, -0.5,  0.5,
		0.5,  0.5,  0.5,
		-0.5, -0.5, 0.5,
		-0.5,  0.5,  0.5
	};

	GLushort cube_elements[] = {
		// front
		0, 1, 3,
		1, 2, 3,
		// right
		2, 5, 3,
		2, 4, 5,
		// back
		4, 7, 5,
		4, 6, 7,
		// left
		6, 0, 7,
		6, 1, 0,
		// bottom
		0, 5, 7,
		0, 3, 5,
		// top
		6, 2, 1,
		6, 4, 2
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	//-------------------------------------------------------------------------//
	// load and compile shaders  "../lab1-6_vs.glsl" and "../lab1-6_fs.glsl"
	// See corresponding code from the previous tasks.
	//-------------------------------------------------------------------------//
	std::string vertex_shader_str = readFile("../lab1-6_vs.glsl");
	std::string fragment_shader_str = readFile("../lab1-6_fs.glsl");

	const char* vertex_shader_src = vertex_shader_str.c_str();
	const char* fragment_shader_src = fragment_shader_str.c_str();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader_src, NULL);
	glCompileShader(vs);
	checkShaderCompileError(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader_src, NULL);
	glCompileShader(fs);
	checkShaderCompileError(fs);

	GLuint shader_program = glCreateProgram();
	//-------------------------------------------------------------------------//
	// attach and link vertex and fragment shaders into a shader program
	// See corresponding code from the previous tasks.
	//-------------------------------------------------------------------------//
	glAttachShader(shader_program, fs);
	glAttachShader(shader_program, vs);
	glLinkProgram(shader_program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glUseProgram(shader_program);

	float n=1.0;
	float f=100.0;

	while (!glfwWindowShouldClose (window)) 
	{
    
		glfwGetFramebufferSize(window, &w_width , &w_height ); //you might need this for correcting the aspect ratio

		//-----------------------------------------------------------------------//
		// YOUR CODE GOES HERE
		// Define the projection matrix, rotation matrices, model matrix, etc.

		float A = -(f + (n)) / (f - (n));
		float B = 2.0f * f * (n) / (f - (n));
		GLfloat projectionMatrix[4][4] = {  {1,0,0,0},
										    {0,1,0,0},
											{0,0,A,-B},
											{0,0,-1,0}, };
		GLfloat rotate_y[4][4] = { {cos(g_rotation[1]), 0, sin(g_rotation[1]), 0},
								 {0, 1, 0, 0},
								 {-sin(g_rotation[1]), 0, cos(g_rotation[1]), 0},
								 {0, 0, 0, 1} };
		GLfloat rotate_x[4][4] = { {1, 0, 0, 0}, 
								 {0, cos(g_rotation[0]), -sin(g_rotation[0]), 0}, 
								 {0, sin(g_rotation[0]), cos(g_rotation[0]), 0}, 
								 {0, 0, 0, 1} };
    
		GLfloat modelMatrix[4][4];
		MUL_4x4(modelMatrix, rotate_x, rotate_y);
    
		GLfloat viewMatrix[4][4] = {{1,0,0,0},
									{0,1,0,0},
									{0,0,1,2},
									{0,0,0,1}, };
		GLfloat inverseViewMatrix[4][4] = { {1,0,0,0},
											{0,1,0,0},
											{0,0,1,-2},
											{0,0,0,1}, };
		//invertMatrix(inverseViewMatrix, viewMatrix);
  
		GLfloat modelViewMatrix[4][4];
		MUL_4x4(modelViewMatrix, inverseViewMatrix, modelMatrix);
    
		GLfloat modelViewProjectionMatrix[4][4];
		MUL_4x4(modelViewProjectionMatrix, projectionMatrix, modelViewMatrix);
    
    
		//---------------------
		// --------------------------------------------------//
		// YOUR CODE GOES HERE
		// Send your modelViewProjection matrix to your vertex shader as a uniform
		//-----------------------------------------------------------------------//
		glUniformMatrix4fv(glGetUniformLocation(shader_program, "new_position"),1, GL_TRUE, *modelViewProjectionMatrix);
    
		// update other events like input handling 
		glfwPollEvents ();
    
		// clear the drawing surface
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//-----------------------------------------------------------------------//
		// Issue an appropriate glDraw*() command.
		//-----------------------------------------------------------------------//
		glDrawElements(GL_TRIANGLES, sizeof(cube_elements) / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

		glfwSwapBuffers (window);
	}

	// close GL context and any other GLFW resources
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.hpp"
#include "objloader.hpp"

#define 	GLFW_KEY_A   65
#define 	GLFW_KEY_D   68
#define 	GLFW_KEY_ARROW_UP	265
#define 	GLFW_KEY_ARROW_DOWN		264

void keyPressed(GLFWwindow* window, int key, int scancode, int acton, int mods);


int main(void)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //resize
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);


	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited movement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it is closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glDisable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile shaders
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");


	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Load the texture
	//GLuint Texture = loadDDS("uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	//GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	bool res = loadOBJ("resources/naves/naveLouca.obj", vertices, uvs, normals);

	if (res) {
		printf("loaded\n");
	}
	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	std::vector<glm::vec3> vertices2;
	std::vector<glm::vec2> uvs2;
	std::vector<glm::vec3> normals2;

	bool res2 = loadOBJ("resources/hangar/hangar.obj", vertices2, uvs2, normals2);
	if (res2) {
		printf("loaded\n");
	}

	GLuint vertexbuffer2;
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);

	GLuint uvbuffer2;
	glGenBuffers(1, &uvbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glBufferData(GL_ARRAY_BUFFER, uvs2.size() * sizeof(glm::vec2), &uvs2[0], GL_STATIC_DRAW);



	float xAxis = 0.0f;
	float yAxis = 0.0f;
	float zAxis = 0.0f;
	float xAxis2 = 4.0f;
	float yAxis2 = 3.0f;
	float zAxis2 = 3.0f;
	glfwSetKeyCallback(window, keyPressed);
	do {
		
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input

		
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			xAxis -= 1.0f;

		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			xAxis += 1.0f;
	
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			yAxis -= 1.0f;

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			yAxis += 1.0f;

		}
		if (glfwGetKey(window, GLFW_KEY_ARROW_UP) == GLFW_PRESS) {
			zAxis += 1.0f;

		}
		if (glfwGetKey(window, GLFW_KEY_ARROW_DOWN) == GLFW_PRESS) {
			zAxis -= 1.0f;

		}
		//xAxis2 += 1;
		if (xAxis > 80.0f) {
			//xAxis = 4.0f;
		}

		//yAxis2 += 1;
		if (yAxis > 80.0f) {
			//yAxis = 3.0f;
		}

		///zAxis2 += 1;
		if (zAxis > 80.0f) {
			//zAxis = 3.0f;
		}
		// MVP Matrices
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 View = glm::lookAt(
			glm::vec3(xAxis2, yAxis2, zAxis2),  // Camera position
			glm::vec3(0, 0, 0),  // Look at origin
			glm::vec3(0, 1, 0)   // Up vector
		);
		glm::mat4 Model = glm::mat4(1.0f);

		
		Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.f, 1.0f, 1.f));// .005 .005 .005
		Model = glm::translate(Model, glm::vec3(xAxis, 3.0f, yAxis));
		


		
		// Move the object further away along the Z-axis (e.g., from 3 to 6)
		//Model = glm::rotate(Model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//Model = glm::rotate(Model, glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//Model = glm::rotate(Model, glm::radians(-24.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//Model = glm::scale(Model, glm::vec3(0.5f, 0.5f, 0.5f));
		//Model = glm::scale(Model, glm::vec3(0.5f, 0.5f, 0.5f));

		//Model = glm::translate(Model, glm::vec3(-4,-3,3));

		glm::mat4 MVP = Projection * View * Model;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		//glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);


		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);


		//HANGAR 1
		// MVP for the second model
		glm::mat4 Model2 = glm::mat4(1.0f);
		Model2 = glm::translate(Model2, glm::vec3(-8.0f, 0.0f, -1.0f)); // Adjust position
		Model2 = glm::scale(Model2, glm::vec3(0.005f, 0.005f, 0.005f)); // Adjust scale

		glm::mat4 MVP2 = Projection * View * Model2;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);

		// Bind buffers and draw the second model
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		//HANGAR 2
		// MVP for the second model
		glm::mat4 Model3 = glm::mat4(1.0f);
		Model3 = glm::translate(Model3, glm::vec3(-2.0f, 0.0f, -6.0f)); // Adjust position
		Model3 = glm::rotate(Model3, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		Model3 = glm::scale(Model3, glm::vec3(0.005f, 0.005f, 0.005f)); // Adjust scale

		glm::mat4 MVP3 = Projection * View * Model3;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);

		// Bind buffers and draw the second model
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		printf("x: %f\n", xAxis);
		printf("y: %f\n", yAxis);
		printf("z: %f\n", zAxis);
	} // Check if the ESC key was pressed or the window was closed
	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);

	glDeleteBuffers(1, &vertexbuffer2);
	glDeleteBuffers(1, &uvbuffer2);



	glDeleteProgram(programID);
	//glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}



void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	printf("key: %d\n",key);
	
}
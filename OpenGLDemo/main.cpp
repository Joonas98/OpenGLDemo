#include <stdio.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include <iostream>
#include <windows.h>
#include <thread>

void PlayMusic()
{
	PlaySound(TEXT("Song1.wav"), NULL, SND_SYNC);
	printf("Music started");
}

void StopMusic()
{
	PlaySound(NULL, 0, 0);
	printf("Music stopped");
}

GLFWwindow* InitWindow()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW Failed.");
		return NULL;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		1024,
		768,
		"Kaunis OpenGL ohjelma",
		NULL, NULL);

	//Jos ikkunan luonti failaa
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open window.");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();

	//Jos GLEW jutut failaa
	if (err != GLEW_OK)
	{
		fprintf(stderr, "%s\n", glewGetErrorString(err));
		fprintf(stderr, "GLEW Failed.");
		glfwTerminate();
		return NULL;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	return window;
}

//Näppäimistön lukemista
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Scene scene;
	//std::cout << key << std::endl;

	//SYVYYS
	if (key == GLFW_KEY_W)
	{
		std::cout << "W is pressed!" << std::endl;
		scene.Subx3();
	}

	if (key == GLFW_KEY_S)
	{
		std::cout << "S is pressed!" << std::endl;
		scene.Addx3();
	}
	// SIVUTTAIN
	if (key == GLFW_KEY_A)
	{
		std::cout << "A is pressed!" << std::endl;
		scene.Subx1();
	}

	if (key == GLFW_KEY_D)
	{
		std::cout << "D is pressed!" << std::endl;
		scene.Addx1();
	}
	// KORKEUS
	if (key == GLFW_KEY_E)
	{
		std::cout << "E is pressed!" << std::endl;
		scene.Addx2();
	}

	if (key == GLFW_KEY_C)
	{
		std::cout << "C is pressed!" << std::endl;
		scene.Subx2();
	}
	//FOV
	if (key == GLFW_KEY_KP_ADD)
	{
		std::cout << "KP_PLUS is pressed!" << std::endl;
		scene.AddFov();
		std::cout << scene.fov << std::endl;
	}

	if (key == GLFW_KEY_KP_SUBTRACT)
	{
		std::cout << "KP_SUBTRACT is pressed!" << std::endl;
		scene.SubFov();
		std::cout << scene.fov << std::endl;
	}

}



int main(void)
{
	// Create window.
	GLFWwindow* window = InitWindow();
	if (window == NULL)
	{
		return -1;
	}
	glClearColor(0.5f, 0.0f, 0.5f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwSetKeyCallback(window, keyCallback);

	Scene scene;
	scene.LoadScene("data\\camping.scene");

	//Toinen thread soittamaan musiikkia
	std::thread thread_obj(PlayMusic);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.DrawScene();

		//	float fl = scene.fov;
		//	printf("%f\n", fl);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	scene.Clear();
	glfwTerminate();
}

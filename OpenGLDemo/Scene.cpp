#include <stdio.h>
#include <fstream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "Scene.h"

using namespace std;

int x1 = 4;
int x2 = 3;
int x3 = 8;
float fov = 90.0f;

Scene::Scene()
{
	m_shaderID = LoadShaders(
		"VertexShader.glsl",
		"FragmentShader.glsl");



	m_viewMatrixID = glGetUniformLocation(m_shaderID, "vm");
	m_projectionMatrixID = glGetUniformLocation(m_shaderID, "pm");
	m_lightAmountID = glGetUniformLocation(m_shaderID, "lightAmo");
	m_lightDirectionID = glGetUniformLocation(m_shaderID, "lightDir");

	//Radians kohtaan FOV
	//Runtime muutokset ei vaikuta
	m_projectionMatrix = glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 100.0f);
	m_viewMatrix = glm::lookAt(
		glm::vec3(4, 3, 10),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));

	// HARDCODED, REMOVE! DEBUG ONLY!
	m_light.Rotate(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_startTime = glfwGetTime();
}

Scene::~Scene()
{

}

bool Scene::LoadScene(string filePath)
{
	ifstream file(filePath.c_str(), ios::in);
	if (!file.is_open())
	{
		return false;
	}

	unsigned int count = 0;
	file.read(reinterpret_cast<char*>(&count), sizeof(count));
	printf("Number of meshes: %d\n", count);

	for (int i = 0; i < count; ++i)
	{
		string modelName = "";
		unsigned int size = 0;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));

		char* buf = new char[size + 1];
		file.read(buf, size + 1);
		modelName.append(buf, size);
		delete[] buf;
		printf("Model name: %s\n", modelName.c_str());

		string modelFile = "";
		size = 0;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));

		buf = new char[size + 1];
		file.read(buf, size + 1);
		modelFile.append(buf, size);
		delete[] buf;
		printf("Model file: %s\n", modelFile.c_str());

		string texFile = "";
		size = 0;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));

		buf = new char[size + 1];
		file.read(buf, size + 1);
		texFile.append(buf, size);
		delete[] buf;
		printf("Texture file: %s\n", texFile.c_str());

		float px = 0.0f;
		file.read(reinterpret_cast<char*>(&px), sizeof(px));
		float py = 0.0f;
		file.read(reinterpret_cast<char*>(&py), sizeof(py));
		float pz = 0.0f;
		file.read(reinterpret_cast<char*>(&pz), sizeof(pz));
		printf("Mesh location: %f, %f, %f\n", px, py, pz);

		float a = 0.0f;
		file.read(reinterpret_cast<char*>(&a), sizeof(a));
		float rx = 0.0f;
		file.read(reinterpret_cast<char*>(&rx), sizeof(rx));
		float ry = 0.0f;
		file.read(reinterpret_cast<char*>(&ry), sizeof(ry));
		float rz = 0.0f;
		file.read(reinterpret_cast<char*>(&rz), sizeof(rz));
		printf("Mesh rotation: %f, %f, %f, %f\n", a, rx, ry, rz);

		string p = string(m_appFilePath);
		p.append("data\\");
		p.append(modelFile);
		string t = string(m_appFilePath);
		t.append("data\\");
		t.append(texFile);
		Mesh m(p, t, m_shaderID);
		m_meshes.push_back(m);
		m_meshes[m_meshes.size() - 1].Rotate(a, glm::vec3(rx, ry, rz));
		m_meshes[m_meshes.size() - 1].Translate(glm::vec3(px, py, pz));
	}
	file.close();
}

void Scene::DrawScene()
{
	m_light.UpdateMatrix();
	glUseProgram(m_shaderID);
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &m_viewMatrix[0][0]);
	glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &m_projectionMatrix[0][0]);
	glUniform1f(m_lightAmountID, m_light.m_amount); //
	glm::vec3 d = m_light.Forward();				//
	glUniform3f(m_lightDirectionID, d.x, d.y, d.z); //
	for (int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i].DrawMesh();
	}

	//Radians kohtaan fov
	m_projectionMatrix = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	//Kameran liikkuminen / rotaatio
	m_deltaTime = glfwGetTime() - m_startTime;
	m_viewMatrix = glm::lookAt(
		glm::vec3(x1, x2, x3),  //glm::vec3(x1, x2, m_deltaTime),
		glm::vec3(x1, x2, 0),     //glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));	//glm::vec3(0, 1, 0));

}

//Tyhjentäminen
void Scene::Clear()
{
	printf("Clearing scene\n");
	for (int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i].Clear();
	}
	m_meshes.clear();
	glDeleteProgram(m_shaderID);
}

//Input funktiot
void Scene::Addx1()
{
	++x1;
}

void Scene::Subx1()
{
	--x1;
}

void Scene::Addx2()
{
	++x2;
}

void Scene::Subx2()
{
	--x2;
}

void Scene::Addx3()
{
	++x3;
}

void Scene::Subx3()
{
	--x3;
}

void Scene::AddFov()
{
	fov = fov + 15;
}

void Scene::SubFov()
{
	fov = fov - 15;
}


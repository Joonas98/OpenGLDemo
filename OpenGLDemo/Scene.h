#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Light.h"

class Scene
{
public:
	Scene();
	~Scene();
	bool LoadScene(std::string filePath);
	void DrawScene();
	void Clear();
	void Addx1();
	void Subx1();
	void Addx2();
	void Subx2();
	void Addx3();
	void Subx3();
	void AddFov();
	void SubFov();

	float fov = 45.0f;

private:
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	GLuint m_viewMatrixID;
	GLuint m_projectionMatrixID;
	GLuint m_shaderID;
	GLuint m_lightAmountID;
	GLuint m_lightDirectionID;
	std::vector<Mesh> m_meshes;
	Light m_light;
	std::string m_appFilePath = "C:\\Users\\jsuur\\Desktop\\OpenGLDemo\\OpenGLDemo\\";
	double m_deltaTime = 0.0;
	double m_startTime = 0.0;
};

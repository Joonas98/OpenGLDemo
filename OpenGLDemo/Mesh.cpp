#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLEW/glew.h>
#include "objloader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "texture.hpp"

Mesh::Mesh(std::string file, std::string texFile, GLuint shader)
{
	m_file = file;
	m_translateMatrix = glm::mat4(1.0f);
	m_rotationMatrix = glm::mat4(1.0f);
	m_shader = shader;

	m_modelMatrixID = glGetUniformLocation(shader, "mm");
	m_itMatrixID = glGetUniformLocation(shader, "it");
	m_textureID = glGetUniformLocation(shader, "mainTex");
	Load(texFile);
}

Mesh::~Mesh()
{

}

void Mesh::Clear()
{
	printf("Clearing mesh\n");
	m_vertices.clear();
	m_uvs.clear();
	m_normals.clear();

	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_vuv);
	glDeleteBuffers(1, &m_vno);
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::DrawMesh()
{
	UpdateMatrix();
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_matrix[0][0]);

	//glm::mat3 invTranspose = glm::transpose(glm::inverse(glm::mat3(m_matrix)));
	//glUniformMatrix3fv(m_itMatrixID, 1, GL_FALSE, &invTranspose[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_mainTex);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glBindVertexArray(0);
}

void Mesh::Load(std::string texFile)
{
	loadOBJ(m_file.c_str(), m_vertices, m_uvs, m_normals);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		m_vertices.size() * sizeof(glm::vec3),
		&m_vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &m_vuv);
	glBindBuffer(GL_ARRAY_BUFFER, m_vuv);
	glBufferData(
		GL_ARRAY_BUFFER,
		m_uvs.size() * sizeof(glm::vec2),
		&m_uvs[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &m_vno);
	glBindBuffer(GL_ARRAY_BUFFER, m_vno);
	glBufferData(
		GL_ARRAY_BUFFER,
		m_normals.size() * sizeof(glm::vec3),
		&m_normals[0],
		GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_vuv);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_vno);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glBindVertexArray(0);

	printf("Loading texture %s\n", texFile.c_str());
	m_mainTex = loadDDS(texFile.c_str());
	glUniform1i(m_textureID, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_mainTex);
}
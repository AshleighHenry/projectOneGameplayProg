#pragma once

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif
#include <stdio.h>
#include <string.h>
#include <Cube.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace glm;

class Player
{
public:
	Player();
	~Player();
	vec3 getPosition();
	void setPosition(vec3 position);
	void processEvents(sf::Event t_event);
	void update();
	// Returns the first element of the array
	GLfloat* getVertex();
	// 3 Vertices
	int getVertexCount();

	// Returns the first element of the array
	GLfloat* getColor();
	// 3 Colors RGB
	int getColorCount();

	// Returns the first element of the array
	GLfloat* getUV();
	// 3 Colors RGB
	int getUVCount();
	// Returns the first element of the array
	GLfloat* getIndex();
	// 3 Colors RGB
	int getIndexCount();
private:
	// Cube Elements
	GLfloat vertex[ARRAY_SIZE(vertices)];
	GLfloat color[ARRAY_SIZE(colors)];
	GLfloat uv[ARRAY_SIZE(uvs)];
	GLfloat index[ARRAY_SIZE(indices)];
	vec3 position;

	bool m_jump = false; 
	bool m_fall = false; 
	float m_jumpStartHeight;
	float m_jumpHeight = 0;
	const int MAX_JUMP = 3; // max height player can jump 


};


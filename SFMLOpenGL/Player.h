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
	sf::RectangleShape getCollisionBox();
	vec3 getPreviousPosition() const;

	void jump();
	void fall();
	bool getJump();
	void stopJump(); // sets fall to true when no collision is detected under the player. 
	bool getFall();
	void stopFall();
	void moveRight();
	bool ded = false;
private:
	// Cube Elements
	GLfloat vertex[ARRAY_SIZE(vertices)];
	GLfloat color[ARRAY_SIZE(colors)];
	GLfloat uv[ARRAY_SIZE(uvs)];
	GLfloat index[ARRAY_SIZE(indices)];
	vec3 position;
	vec3 m_previousPosition; // previousPosition of cube to check if collision happens on top or on the side of the cube. 
	bool m_jump = false;
	bool m_fall = false;
	bool m_right = false;
	float m_rightSpeed = 0.25;
	float m_jumpStartHeight = 0;
	float m_jumpHeight = 0;
	float m_totalJumpLength = 0;
	const int MAX_JUMP_HEIGHT = 5; // max height player can jump 
	sf::RectangleShape m_collisionFace;
	vec3 m_gravity{ 0.0f, -0.0000098f, 0.0f };
	vec3 m_initialVelocity{ 0.2f, 1.0f,0.0f };
	vec3 m_velocity{ 0.0f,0.0f,0.0f };
	bool m_stopMove = false;


};


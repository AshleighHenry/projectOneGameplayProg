#include "Player.h"

Player::Player()
{
	// Copy the Cube contents into GameObject
	memcpy(this->vertex, vertices, sizeof(this->vertex));
	memcpy(this->color, colors, sizeof(this->color));
	memcpy(this->uv, uvs, sizeof(this->uv));

	// Copy UV's to all faces
	for (int i = 1; i < 6; i++)
		memcpy(&uv[i * 4 * 2], &uv[0], 2 * 4 * sizeof(GLfloat));

	memcpy(this->index, indices, sizeof(this->index));

	this->position = vec3();
	m_collisionFace.setPosition(position.x, position.y);
	m_collisionFace.setSize(sf::Vector2f( 2, 2));
}


vec3 Player::getPosition() { return this->position; }
void Player::setPosition(vec3 position) { this->position = position; }

void Player::processEvents(sf::Event t_event)
{
	if (t_event.type == sf::Event::KeyPressed)
	{
		if (t_event.key.code == sf::Keyboard::Space && (m_jump == false) && (m_fall == false))
		{

			m_jump = true;
			m_jumpStartHeight = position.y;
			m_jumpHeight = m_jumpStartHeight;
		}

		if (t_event.key.code == sf::Keyboard::Right)
		{
			position.x += 0.25;
		}
		else if (t_event.key.code == sf::Keyboard::Left)
		{
			position.x -= 0.25;
		}
	}
}

void Player::update()
{
	m_previousPosition = position; // previous position set before movement
	if (m_jump)
	{
		m_jumpHeight += 0.25;
		if (m_jumpHeight < MAX_JUMP)
		{
			position.y += 0.25;
		}
		else if (m_jumpHeight >= MAX_JUMP)
		{
			m_fall = true;
			m_jump = false; 
		}
	}
	if (m_fall)
	{
		m_jumpHeight -= 0.25;
		if (MAX_JUMP - m_jumpHeight < 3)
		{
			
			position.y -= 0.25;
		}
		else
		{
			m_fall = false;
		}
		
		
	}

	m_collisionFace.setPosition(position.x, position.y); // setposition of collision box every frame 
}

// Returns the first element of the Vertex array
GLfloat* Player::getVertex() { return this->vertex; }
// 3 Vertices
int Player::getVertexCount() { return ARRAY_SIZE(vertex) / 3; }

// Returns the first element of the Color array
GLfloat* Player::getColor() { return this->color; }
// 4 Colors RGBA
int Player::getColorCount() { return ARRAY_SIZE(color) / 4; }

// Returns the first element of the UV array
GLfloat* Player::getUV() { return this->uv; }
// 3 Colors RGB
int Player::getUVCount() { return ARRAY_SIZE(uv); }

// Returns the first element of the Index array
GLfloat* Player::getIndex() { return this->index; }
// 3 Colors RGB
int Player::getIndexCount() { return ARRAY_SIZE(index) / 3; }

sf::RectangleShape Player::getCollisionBox()
{
	return sf::RectangleShape(m_collisionFace);
}

vec3 Player::getPreviousPosition() const
{
	return vec3(m_previousPosition);
}

void Player::resetJump()
{
	m_jump = false;
	m_fall = false;
	m_jumpHeight = 0;
	m_jumpStartHeight = 0;
}

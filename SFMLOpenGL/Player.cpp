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
void Player::setPosition(vec3 position) 
{ 
	this->position = position; 
}

void Player::processEvents(sf::Event t_event)
{
	if (t_event.key.code == sf::Keyboard::Space && m_jump == false && m_fall == false)
		{
			m_jump = true;
		}
	if (t_event.key.code == sf::Keyboard::Right)
	{
		m_right = true;
	}
	if (t_event.type == sf::Event::KeyReleased)
	{
		m_right = false; 
	}
	
}

void Player::update()
{
	m_previousPosition = position; // previous position set before movement
	if (m_jump)
	{
		jump();
	}
	
	if (m_right)
	{
		moveRight();
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


void Player::jump()
{
	m_jumpStartHeight = position.y;
	
	if (m_totalJumpLength == MAX_JUMP_HEIGHT)
	{
		m_jump = false;
		m_fall = true;
		m_totalJumpLength = 0;
		m_jumpStartHeight = 0;
	}
	position.y += 0.25;
	m_totalJumpLength += 0.25;
}

void Player::fall()
{
	if (m_fall == true)
	{
		if (position.y == 0)
		{
			m_fall = false;
		}
		position.y -= 0.25;
	}
}

bool Player::getJump()
{
	return m_jump;
}

void Player::changeFall()
{
	if (m_jump)
	{
		m_jump = false;
		m_totalJumpLength = 0;
		m_jumpStartHeight = 0;
	}
	m_fall = false;
}

bool Player::getFall()
{
	return m_fall;
}

void Player::moveRight()
{
	position.x += m_rightSpeed; // 0.25 for test
}

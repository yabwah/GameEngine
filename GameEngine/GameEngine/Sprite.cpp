#include "Sprite.h"



Sprite::Sprite():m_vboID(0),m_height(0.0f),m_width(0.0f)
{
}


Sprite::~Sprite()
{
	if (m_vboID != 0)
	{
		glDeleteBuffers(1, &m_vboID);

	}
}

void Sprite::init(Position a_pos, float a_width, float a_height)
{
	m_pos = a_pos;
	m_width = a_width;
	m_height = a_height;

	if (m_vboID == 0)
	{
		glGenBuffers(1, &m_vboID);
	}

	Position vertexData[6];

	vertexData[0].x = m_pos.x + m_width;
	vertexData[0].y = m_pos.y + m_height;

	vertexData[1].x = m_pos.x;
	vertexData[1].y = m_pos.y + m_height;

	vertexData[2].x = m_pos.x;
	vertexData[2].y = m_pos.y;

	vertexData[3].x = m_pos.x + m_width;
	vertexData[3].y = m_pos.y + m_height;

	vertexData[4].x = m_pos.x + m_width;
	vertexData[4].y = m_pos.y;

	vertexData[5].x = m_pos.x;
	vertexData[5].y = m_pos.y;


	glBindBuffer(GL_ARRAY_BUFFER , m_vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw()
{

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

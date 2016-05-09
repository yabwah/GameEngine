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


	Vertex vertexData[6];

	vertexData[0].position.x = m_pos.x + m_width;
	vertexData[0].position.y = m_pos.y + m_height;

	vertexData[1].position.x = m_pos.x;
	vertexData[1].position.y = m_pos.y + m_height;
				
	vertexData[2].position.x = m_pos.x;
	vertexData[2].position.y = m_pos.y;
				
	vertexData[3].position.x = m_pos.x + m_width;
	vertexData[3].position.y = m_pos.y + m_height;
				
	vertexData[4].position.x = m_pos.x + m_width;
	vertexData[4].position.y = m_pos.y;
				
	vertexData[5].position.x = m_pos.x;
	vertexData[5].position.y = m_pos.y;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 255;
	vertexData[1].color.g = 255;
	vertexData[1].color.b = 0;
	vertexData[1].color.a = 255;

	vertexData[4].color.r = 0;
	vertexData[4].color.g = 255;
	vertexData[4].color.b = 255;
	vertexData[4].color.a = 255;

	glBindBuffer(GL_ARRAY_BUFFER , m_vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw()
{

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex,position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE,GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

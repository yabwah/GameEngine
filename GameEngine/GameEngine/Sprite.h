#pragma once

#include<GL/glew.h>
#include<stddef.h>

#include "Position.h"
#include "Vertex.h"


class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(Position a_pos, float a_width, float a_height);
	void draw();

private:
	Position m_pos;
	float m_width;
	float m_height;
	GLuint m_vboID;
};


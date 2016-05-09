#pragma once

#include<GL/glew.h>
#include<string>
#include<fstream>
#include<vector>

#include "Errors.h"

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileshaders(const std::string& a_vertexShaderfilePath, const std::string& a_fragmentShaderFilePath);
	void linkShaders();
private:

	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
	
	void compileShader(const std::string a_filePath, GLuint a_id);
	
};


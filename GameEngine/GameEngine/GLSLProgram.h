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
	void addAttribute(const std::string& a_attName);
	void use();
	void unUse();

	GLuint getUniformLocation(const std::string& a_uniformName);
private:

	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
	int m_numAttributes;
	void compileShader(const std::string a_filePath, GLuint a_id);
	
};


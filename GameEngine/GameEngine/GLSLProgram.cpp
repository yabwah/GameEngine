#include "GLSLProgram.h"



GLSLProgram::GLSLProgram():m_programID(0), m_fragmentShaderID(0), m_vertexShaderID(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileshaders(const std::string & a_vertexShaderfilePath, const std::string & a_fragmentShaderFilePath)
{
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (m_vertexShaderID == 0)
	{
		fatalError("Could not create vertex shader!");
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (m_vertexShaderID == 0)
	{
		fatalError("Could not create fragment shader!");
	}

	compileShader(a_vertexShaderfilePath, m_vertexShaderID);
	compileShader(a_fragmentShaderFilePath, m_fragmentShaderID);
	
}

void GLSLProgram::compileShader(const std::string a_filePath, GLuint a_id)
{

	std::ifstream vertexFile(a_filePath);
	if (vertexFile.fail())
	{
		fatalError("could not open shader file at path: " + a_filePath);
	}

	
	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}
	vertexFile.close();

	const char* cfile = fileContents.c_str();

	glShaderSource(GL_VERTEX_SHADER, 1, &cfile, nullptr);

	glCompileShader(a_id);

	GLint success = 0;
	glGetShaderiv(a_id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{

		GLint maxLength = 0;
		glGetShaderiv(a_id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(a_id, maxLength, &maxLength, &errorLog[0]);

		std::string err;
		err.copy(&errorLog[0], errorLog.size());

		fatalError("Error compiling shader \nPath : " + a_filePath + "\nError : " + err);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(a_id); // Don't leak the shader.

	}
}

void GLSLProgram::linkShaders()
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	m_programID = glCreateProgram();

	//Attach our shaders to our program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	//Link our program
	glLinkProgram(m_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

		std::string err;
		err.copy(&errorLog[0], errorLog.size());

		fatalError("Error linking shading program \nError : " + err);

		//We don't need the program anymore.
		glDeleteProgram(m_programID);
		//Don't leak shaders either.
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		//Use the infoLog as you see fit.

		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);

}

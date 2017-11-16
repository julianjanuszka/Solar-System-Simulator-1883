#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

bool Shader::load()
{
	if (!compile(filenamev, GL_VERTEX_SHADER)) { return false; }
	if (!compile(filenamef, GL_FRAGMENT_SHADER)) { return false; }
	program = glCreateProgram();
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);
	glLinkProgram(program);
	GLint succuess;
	glGetShaderiv(program, GL_LINK_STATUS, &succuess);
	if (succuess != 0) {
		return true;
	}
	else {
		GLint loglength;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &loglength);
		GLchar* chararray = new GLchar[loglength];
		glGetShaderInfoLog(program, loglength, 0, chararray);
		printf(chararray);
		delete[] chararray;
		return false;
	}


}
char * Shader::readBinaryFile(std::string filename)
{
	std::ifstream instream(filename, std::ios::binary); //opens in binary mode
	if (!instream.is_open())return nullptr;

	//get length
	instream.seekg(0, std::ios::end);//go to end of file
	int length = instream.tellg(); //how far we are
	instream.seekg(0, std::ios::beg); //go tobeginning

									  //read it all at once
	char* bytes = new char[length + 1];
	bytes[length] = '\0';
	instream.read(bytes, length);

	//close it
	instream.close();

	return bytes;
}
bool Shader::compile(string filename, GLenum shadertype) {
	char* contents;
	contents = readBinaryFile(filename);
	GLint succuess;
	if (contents == nullptr) { printf("Error Loading file"); return 0; }
	if (shadertype == GL_VERTEX_SHADER) {
		vprogram = glCreateShader(shadertype);
		glShaderSource(vprogram, 1, &contents, 0);
		delete[] contents;
		glCompileShader(vprogram);
		glGetShaderiv(vprogram, GL_COMPILE_STATUS, &succuess);
	}
	else if (shadertype == GL_FRAGMENT_SHADER) {
		fprogram = glCreateShader(shadertype);
		glShaderSource(fprogram, 1, &contents, 0);
		delete[] contents;
		glCompileShader(fprogram);
		glGetShaderiv(fprogram, GL_COMPILE_STATUS, &succuess);
	}
	else {

		return 0;
	}
	//check if loaded/compiled right
	if (succuess != 0) {
		return true;
	}
	else {
		GLint loglength;
		glGetShaderiv(fprogram, GL_INFO_LOG_LENGTH, &loglength);
		GLchar* chararray = new GLchar[loglength];
		glGetShaderInfoLog(fprogram, loglength, 0, chararray);
		printf(chararray);
		delete[] chararray;
		return false;
	}
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::unload()
{
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);

}

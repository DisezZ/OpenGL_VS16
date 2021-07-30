#include <shader.h>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR:SHADER:FILE_NOT_SUCCESFULLY_READED" << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER:VERTEX:COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER:FRAGMENT:COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER:PROGRAM:LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::use()
{
    glUseProgram(programID);
}

void Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, glm::vec2 vec)
{
    glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &vec[0]);
}

void Shader::setVec3(const std::string& name, glm::vec3 vec)
{
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &vec[0]);
}

void Shader::setVec4(const std::string& name, glm::vec4 vec)
{
    glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &vec[0]);
}

void Shader::setMat2(const std::string& name, glm::mat2 mat)
{
    glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, glm::mat3 mat)
{
    glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, glm::mat4 mat)
{
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
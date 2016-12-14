//
// Created by Luca Zanconi on 14/12/16.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string name)
{
    this->name = name;
}

ShaderProgram::ShaderProgram(const std::string &name, const std::string &vertexSource,
                             const std::string &fragmentSource)
{
    this->name = name;
    initShader(vertexSource, fragmentSource);
}

ShaderProgram::~ShaderProgram()
{
    std::string msg = "ShaderProgram " + name + " destroyed!";
    __android_log_write(ANDROID_LOG_DEBUG, "Native", msg.c_str());
}

void ShaderProgram::initShader(const std::string &vertexSource, const std::string &fragmentSource)
{
    int vertexShaderHandle = addShader(GL_VERTEX_SHADER, vertexSource);
    int fragmentShaderHandle = addShader(GL_FRAGMENT_SHADER, fragmentSource);

    shaderProgramHandle = glCreateProgram();
    glAttachShader(shaderProgramHandle, vertexShaderHandle);
    glAttachShader(shaderProgramHandle, fragmentShaderHandle);

    GLint linkStatus;
    glLinkProgram(shaderProgramHandle);
    glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(shaderProgramHandle, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(shaderProgramHandle, infoLogLength, NULL, infoLog);

        std::string errorMsg = "Shader Link Error!\nShaderProgram: " + name + "\n" + infoLog;
        __android_log_write(ANDROID_LOG_ERROR, "Native", errorMsg.c_str());

        delete [] infoLog;
        glDeleteProgram(shaderProgramHandle);
    }

    glDeleteShader(vertexShaderHandle);
    glDeleteShader(fragmentShaderHandle);
}

int ShaderProgram::addShader(int type, const std::string &source)
{
    int shaderHandle = glCreateShader(type);
    const char *chrSource = source.c_str();
    glShaderSource(shaderHandle, 1, &chrSource, NULL);

    GLint compileStatus;
    glCompileShader(shaderHandle);
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar  *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shaderHandle, infoLogLength, NULL, infoLog);

        std::string shaderType;
        switch (type)
        {
            case GL_VERTEX_SHADER:
                shaderType = "VertexShader";
                break;

            case GL_FRAGMENT_SHADER:
                shaderType = "FragmentShader";
                break;
        }

        std::string errorMsg = "Shader Compilation Error!\nShaderProgram: " + name + "\nShaderType: " + shaderType + "\n" + infoLog;
        __android_log_write(ANDROID_LOG_ERROR, "Native", errorMsg.c_str());

        delete [] infoLog;

        return 0;
    }

    return shaderHandle;
}

GLuint ShaderProgram::getHandle()
{
    return shaderProgramHandle;
}
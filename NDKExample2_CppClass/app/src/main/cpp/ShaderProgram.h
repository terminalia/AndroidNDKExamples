//
// Created by Luca Zanconi on 14/12/16.
// A simple C++ class that load a ShaderProgram
// Vertex and Fragment shader sources come from Java
//

#ifndef NDKEXAMPLE2_CPPCLASS_SHADERPROGRAM_H
#define NDKEXAMPLE2_CPPCLASS_SHADERPROGRAM_H

#include <android/log.h>
#include <string>
#include <sstream>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class ShaderProgram
{
private:
    GLuint shaderProgramHandle;
    std::string name;

public:
    ShaderProgram(const std::string name);
    ShaderProgram(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource);
    ~ShaderProgram();

    void initShader(const std::string &vertexSource, const std::string &fragmentSource);
    GLuint getHandle();

private:
    int addShader(int type, const std::string &source);

};


#endif //NDKEXAMPLE2_CPPCLASS_SHADERPROGRAM_H

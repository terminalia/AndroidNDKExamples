//
// Created by Luca Zanconi on 14/12/16.
// The C layer that let Java communicate with ShaderProgram class
//

#include <jni.h>
#include <string>
#include "ShaderProgram.h"

ShaderProgram basicShader("Basic Shader");

//Init the shader program passing vertex and fragment sources from Java code
extern "C"
void Java_tests_mistwork_ndkexample2_1cppclass_ES20Renderer_loadShader(JNIEnv *env, jobject obj, jstring vertexSource, jstring fragmentSource)
{
    const char *chrVertexSource = env->GetStringUTFChars(vertexSource, false);
    const char *chrFragmentSource = env->GetStringUTFChars(fragmentSource, false);

    basicShader.initShader(chrVertexSource, chrFragmentSource);

    env->ReleaseStringUTFChars(vertexSource, chrVertexSource);
    env->ReleaseStringUTFChars(fragmentSource, chrFragmentSource);
}

//Return shader program handle 
extern "C"
jint Java_tests_mistwork_ndkexample2_1cppclass_ES20Renderer_getShaderProgramHandle(JNIEnv *env, jobject obj)
{
    return basicShader.getHandle();
}



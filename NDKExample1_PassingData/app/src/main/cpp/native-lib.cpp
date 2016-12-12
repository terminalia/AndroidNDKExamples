#include <jni.h>
#include <string>
#include <sstream>
#include <android/log.h>

/**
 * --------------------------------------------------------------------------------------------------
 * JAVA TO JNI methods
 */

//Pass Java String to native code
extern "C"
void Java_mistwork_com_ndkexample1_1passingdata_MainActivity_stringFromJAVA(JNIEnv *env, jobject obj, jstring msg)
{
    const char *chrStr = env->GetStringUTFChars(msg, false);
    std::string result(chrStr);
    __android_log_write(ANDROID_LOG_DEBUG, "Native", result.c_str());
    env->ReleaseStringUTFChars(msg, chrStr);
}

//Pass float value to native code
extern "C"
void Java_mistwork_com_ndkexample1_1passingdata_MainActivity_floatFromJAVA(JNIEnv *env, jobject obj, jfloat value)
{
    float result = value;
    std::stringstream ss;
    ss << result;

    __android_log_write(ANDROID_LOG_DEBUG, "Native", ss.str().c_str());
}

//Pass float array to native code
extern "C"
void Java_mistwork_com_ndkexample1_1passingdata_MainActivity_floatArrayFromJAVA(JNIEnv *env, jobject obj, jfloatArray array)
{
    jsize len = env->GetArrayLength(array);
    jfloat *body = env->GetFloatArrayElements(array, false);

    float result[len];
    for (int i=0; i<len; i++) {
        result[i] = body[i];
    }

    for (int i=0; i<len; i++) {
        std::stringstream ss;
        ss << result[i];
        __android_log_write(ANDROID_LOG_DEBUG, "Native", ss.str().c_str());
    }

    env->ReleaseFloatArrayElements(array, body, 0);
}

//Pass Java String array to native code
extern "C"
void Java_mistwork_com_ndkexample1_1passingdata_MainActivity_stringArrayFromJAVA(JNIEnv *env, jobject obj, jobjectArray array)
{
    jsize len = env->GetArrayLength(array);
    std::string *result = new std::string[len];
    for (int i=0; i<len; i++) {
        jstring jstr = (jstring)(env->GetObjectArrayElement(array, i));
        const char *chrStr = env->GetStringUTFChars(jstr, 0);
        result[i] = std::string(chrStr);
        env->ReleaseStringUTFChars(jstr, chrStr);
    }

    for (int i=0; i<len; i++) {
        __android_log_write(ANDROID_LOG_DEBUG, "Native", result[i].c_str());
    }

    delete[] result;
}

/**
 * --------------------------------------------------------------------------------------------------
 * JNI TO JAVA methods
 */

//Passing string to Java code
extern "C"
jstring Java_mistwork_com_ndkexample1_1passingdata_MainActivity_stringFromJNI(JNIEnv *env, jobject obj)
{
    std::string hello = "Hello from Native!";
    return env->NewStringUTF(hello.c_str());
}

//Passing float to Java code
extern "C"
jfloat Java_mistwork_com_ndkexample1_1passingdata_MainActivity_floatFromJNI(JNIEnv *env, jobject obj)
{
    float result = 33.4f;
    return result;
}

//Passing float array to Java code
extern "C"
jfloatArray Java_mistwork_com_ndkexample1_1passingdata_MainActivity_floatArrayFromJNI(JNIEnv *env, jobject obj)
{
    float array[] = { 1.0f, 2.0f, 3.0f, 4.0f};
    jfloatArray result = env->NewFloatArray(4);
    env->SetFloatArrayRegion(result, 0, 4, array);

    return result;
}

//Passing string array to Java code
extern "C"
jobjectArray Java_mistwork_com_ndkexample1_1passingdata_MainActivity_stringArrayFromJNI(JNIEnv *env, jobject obj)
{
    char *games[] = {"Final Fantasy XV", "The Last Guardian", "Shadow Of The Colossus", "Dragon Quest VII"};
    jobjectArray result;
    result = env->NewObjectArray(4, env->FindClass("java/lang/String"), 0);

    for (int i=0; i<4; i++) {
        jstring  str = env->NewStringUTF(games[i]);
        env->SetObjectArrayElement(result, i, str);
    }


    return result;
}
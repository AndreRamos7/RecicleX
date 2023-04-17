#include <jni.h>
#include <string>
#include <iostream>
#include "include/wisardpkg.hpp"
namespace wp = wisardpkg;
using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_reciclex_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    string baseOut = wp::Base64::encode("Hello base64");
    wp::Wisard w(3, {
            {"bleachingActivated", true}
    });
    vector<vector<int>> X(2);
    vector<string> y(2);

    X[0] = {1,1,1,0,0,0};
    X[1] = {1,1,1,0,0,1};
    y[0] = 'a';
    y[1] = 'b';
    w.train(X,y);

    auto out = w.classify(X);

    std::string hello = "Hello from C++ " + out[1];
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_reciclex_MainActivity_process(
        JNIEnv* env,
        jobject mainActivityInstance) {

    const jclass mainActivityCls = env->GetObjectClass(mainActivityInstance);
    const jmethodID jmethodId = env->GetMethodID(mainActivityCls,
                                                 "processInJava",
                                                 "()Ljava/lang/String;");
    if(jmethodId == nullptr){
        return env->NewStringUTF("");
    }
    const jobject result = env->CallObjectMethod(mainActivityInstance, jmethodId);
    const std::string java_msg = env->GetStringUTFChars((jstring) result, JNI_FALSE);
    const std::string c_msg = "Result from Java => ";
    const std::string msg = c_msg + java_msg;
    return env->NewStringUTF((msg.c_str()));
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_reciclex_MainActivity2_kTstringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++ kt";
    return env->NewStringUTF(hello.c_str());
}
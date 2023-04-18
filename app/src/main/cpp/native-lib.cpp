#include <jni.h>
#include <string>
#include <iostream>
#include "include/wisardpkg.hpp"
//#include "android/bitmap.h"
namespace wp = wisardpkg;
using namespace std;

wp::Wisard w(3, {
        {"bleachingActivated", true},
        {"base", 256}
});


extern "C" JNIEXPORT jstring JNICALL
Java_com_reciclex_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    string baseOut = wp::Base64::encode("Hello base64");

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

vector<vector<int>> transformar(jintArray jOA){
    //jOA.
    //jint *i = env->GetIntArrayElements(jOA, NULL);
    vector<vector<int>> X(2);

    X[0] = {1,1,1,0,0,0};
    X[1] = {1,1,1,0,0,1};
    return X;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_reciclex_MainActivity2_classificarImagemWisard(JNIEnv *env, jobject thiz,
                                                        jintArray jOA) {

    //jclass clazz = env->GetObjectClass (jOA);
    //jfieldID fid = env->GetFieldID (clazz, "myArray", "[I");
    // ================================================


    jint arrayLength = (env)->GetArrayLength(jOA);
    vector<vector<int>> X(1/*arrayLength*/);
    int *pix;
    jint i, sum = 0;
    pix = {(env)->GetIntArrayElements(jOA, NULL)};
    //X[0] = pix;
    string hello = to_string(sum);


    vector<int> v1;
    for (i = 0; i < arrayLength; i++) {
        v1.push_back(pix[i]);
        //hello.append(to_string(pix[i]));
        //hello.append(", ");
    }
    X.push_back(v1);
    //cout << "sum:::: = " << sum <<endl;
    //auto out = w.classify(X);


    (env)->ReleaseIntArrayElements(jOA, pix, 0);
    //string hello = "classificando Imagem Wisard = " + out[0];
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_reciclex_MainActivity2_treinarWisard(JNIEnv *env, jobject thiz) {

    vector<vector<int>> X(2);
    vector<string> y(2);

    X[0] = {1,1,1,0,0,0};
    X[1] = {1,1,1,0,0,1};
    y[0] = 'a';
    y[1] = 'b';
    w.train(X,y);

    std::string hello = "treinando Wisard..." ;
    return env->NewStringUTF(hello.c_str());
}
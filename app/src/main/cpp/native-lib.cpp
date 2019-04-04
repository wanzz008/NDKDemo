#include <jni.h>
#include <string>
#include <stdlib.h>


// 原文：https://blog.csdn.net/carson_ho/article/details/73250163
/*
 如果本地代码是C++（.cpp或者.cc），要使用extern "C" { }把本地方法括进去
        JNIEXPORT jstring JNICALL中的JNIEXPORT 和 JNICALL不能省
        关于方法名Java_scut_carson_1ho_ndk_1demo_MainActivity_getFromJNI
        格式 = Java _包名 _ 类名_Java需要调用的方法名
        Java必须大写
        对于包名，包名里的.要改成_，_要改成_1
 */

extern "C" JNIEXPORT jstring JNICALL
Java_com_wzz_ndkdemo_MainActivity_stringFromJNI( JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_wzz_ndkdemo_MainActivity_string_1From_1JNI(JNIEnv *env, jobject instance) {

    // 参数说明
    // 1. JNIEnv：代表了VM里面的环境，本地的代码可以通过该参数与Java代码进行操作
    // 2. obj：定义JNI方法的类的一个本地引用（this）


    return env->NewStringUTF("hhh");  // 上述代码是返回一个String类型的"Hello i am from JNI!"字符串
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_wzz_ndkdemo_JNITest_stringFromJNI(JNIEnv *env, jobject instance) {

    return env->NewStringUTF("从c返回的string");
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_wzz_ndkdemo_JNITest_stringFromJNI1(JNIEnv *env, jclass type) {

    // TODO


    return env->NewStringUTF("hhh");
}extern "C"
JNIEXPORT void JNICALL
Java_com_wzz_ndkdemo_JNITest_stringFromJNI2(JNIEnv *env, jclass type) {



}

// 该函数GetMethodID最后一个形参是该形参列表的签名。
// 通过JNIEnv对象的CallVoidMethod来完成方法的回调,最后一个形参是可变参数。
extern "C"
JNIEXPORT void JNICALL
Java_com_wzz_ndkdemo_JNITest_test1(JNIEnv *env, jobject obj) {

    //回调JNITest中的无参方法noParamMethod

    jclass clazz = env ->FindClass("com/wzz/ndkdemo/JNITest");
    if (clazz == NULL) {
        printf("find class Error");
        return;
    }
    jmethodID id = env ->GetMethodID( clazz, "noParamMethod", "()V"); //  public void noParamMethod() {}
    if (id == NULL) {
        printf("find method Error");
        return;
    } else{
        printf("find noParamMethod success");
    }
    env ->CallVoidMethod( obj, id );


}

// 对于成员函数，是以 "(*)+" 形式表示函数: [有哪些传入参数，传入参数的类型，返回值的类型。]
// "()" 中的字符表示传入参数的类型，后面的+则代表返回值。
// 例如："()V" 就表示 void Func();
// "(II)V" 表示 void Func(int, int);
//"(Ljava/lang/String;Ljava/lang/String;)I" 表示 int Func(String,String)

extern "C"
JNIEXPORT void JNICALL
Java_com_wzz_ndkdemo_JNITest_test2(JNIEnv *env, jobject obj ) {

    //回调JNITest中的有参方法paramMethod
    jclass clazz = env ->FindClass("com/wzz/ndkdemo/JNITest");
    if (clazz == NULL) {
        printf("find class Error");
        return;
    }

    jmethodID id = env ->GetMethodID( clazz, "paramMethod", "(I)V"); // public void paramMethod(int number) {}
    if (id == NULL) {
        printf("find method Error");
        return;
    }
    env ->CallVoidMethod( obj, id , 5 );

}

// 注意获取方法名的方法是GetStaticMethodID，调用方法的函数名是CallStaticVoidMethod，并且由于是静态方法，不应该传入jobject参数，而直接是jclass.
extern "C"
JNIEXPORT void JNICALL
Java_com_wzz_ndkdemo_JNITest_test3(JNIEnv *env, jobject obj ) {

    jclass clazz = env ->FindClass( "com/wzz/ndkdemo/JNITest" );
    if (clazz == NULL) {
        printf("find class Error");
        return;
    }
    jmethodID id = env ->GetStaticMethodID( clazz, "staticMethod", "()V");
    if (id == NULL) {
        printf("find method Error");
        return;
    }

    env ->CallStaticVoidMethod( clazz, id );

}
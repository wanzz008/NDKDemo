package com.wzz.ndkdemo;

import android.util.Log;

//     原文：https://blog.csdn.net/wzhseu/article/details/79683045

/**
 * 使用CMake方式生成.so
 * 1、创建项目时，选择生成c++项目，会自动创建cpp文件夹：包含.cpp文件和CMakeLists.txt
 * 2、新建JNITest类，定义native方法，根据提示会自动在cpp文件里生成方法
 * 3、在app-> build.gradle中添加两处配置：1、指定CMake文件的位置  2、配置.so支持的CPU平台
 * 4、Make Project，则会在cpp文件夹下生成libs文件夹，里面包含.so  （\app\build\intermediates\cmake\debug此目录下也有）
 */
public class JNITest {


    // Used to load the 'native-lib' library on application startup.
    // 步骤1:加载生成的so库文件
    // 注意要跟.so库文件名相同
    static {
        System.loadLibrary("native-lib");
    }

    private static String TAG ="wzz------";

    // 步骤2:定义在JNI中实现的方法

    public native void test1();

    public native void test2();

    public native void test3();

    public native String stringFromJNI();

    public static native String stringFromJNI1();

    public static native void stringFromJNI2();

    // cpp里通过反射调用此方法
    public void noParamMethod() {
        Log.i(TAG, "无参的Java方法被调用了");
    }

    public void paramMethod(int number) {
        Log.i(TAG, "有参的Java方法被调用了" + number + "次");
    }

    public static void staticMethod() {
        Log.i(TAG, "静态的Java方法被调用了");
    }



}

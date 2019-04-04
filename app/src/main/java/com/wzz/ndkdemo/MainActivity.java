package com.wzz.ndkdemo;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    JNITest jni ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        jni = new JNITest();

        TextView textView = findViewById(R.id.sample_text);
        textView.setText( jni.stringFromJNI() ); // 从.cpp中返回字符串

    }

    // JNI调用Java
    //不同于JNI调用C，JNI调用Java的过程不是单独存在的。而是编写native方法，Java先通过JNI调用该方法，在方法内部再去回调类中对应的Java方法。步骤有些类似于Java中的反射。这里写定义三个点击事件，三个Native方法，三种Java的方法类型，根据相关的Log判断是否成功。

    // 通过jni调用java里的无参方法
    public void test1(View view) {
        jni.test1();
    }
    public void test2(View view) {
        jni.test2();
    }
    public void test3(View view) {
        jni.test3();
    }
}

# 编译本地库时我们需要的最小的cmake版本
cmake_minimum_required(VERSION 3.4.1)


#使用CMakeLists.txt同样可以指定so库的输出路径,但一定要在add_library之前设置，否则不会生效:
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI}) #指定路径
#生成的so库在和CMakeLists.txt同级目录下的libs文件夹下
#如果只是在自己的项目中使用，CMake的方式在打包APK的时候会自动将cpp文件编译成so文件拷贝进去。如果要提供给外部使用时，Make Project，之后在libs目录下就可以看到生成的对应配置的相关CPU平台的.so文件。



# 相当于Android.mk
add_library( # Sets the name of the library. 设置编译生成本地库的名字
        # 生成的so库名称，此处生成的so文件名称是libnative-lib.so
        native-lib

        # Sets the library as a shared library. 库的类型
        # STATIC：静态库，是目标文件的归档文件，在链接其它目标的时候使用
        # SHARED：动态库，会被动态链接，在运行时被加载
        # MODULE：模块库，是不会被链接到其它目标中的插件，但是可能会在运行时使用dlopen-系列的函数动态链接
        SHARED

        # Provides a relative path to your source file(s).  编译文件的路径
        # 资源文件，可以多个，
        # 资源路径是相对路径，相对于本CMakeLists.txt所在目录 src/main/cpp/native-lib.cpp
        native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# 从系统查找依赖库 (# 添加一些我们在编译我们的本地库的时候需要依赖的一些库，这里是用来打log的库)
find_library( # Sets the name of the path variable.
        # android系统每个类型的库会存放一个特定的位置，而log库存放在log-lib中
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        # android系统在c环境下打log到logcat的库
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

# 配置库的链接（依赖关系） || # 关联自己生成的库和一些第三方库或者系统库
target_link_libraries( # Specifies the target library.
        # 配置库的链接（依赖关系）
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        # 依赖于
        ${log-lib})

#需要注意的是，如果我们不在c源代码文件中输出日志到logcat，那么我们是不需要依赖log库的，也就是说find_library、target_link_libraries不是必须的。
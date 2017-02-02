//
// Created by alex on 31.01.17.
//

#include <JNIHelper.h>
#include "FileReader.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include "rhbuilder.h"
#include <jni.h>

std::string name;


FileReader::FileReader()
{

}
FileReader::~FileReader() { }

TSPLINE::TSplinePtr FileReader::read_file()
{

    std::string file_name = name;
    std::string dir_name = "rhino\/"+file_name+".tsm";
    ndk_helper::JNIHelper& helper = *ndk_helper::JNIHelper::GetInstance();
    std::vector<uint8_t> buffer_ref;
    const char* fileName = dir_name.c_str();
    helper.ReadFile(fileName, &buffer_ref);

    std::stringbuf bf(std::string(buffer_ref.begin(), buffer_ref.end()));
    std::istream is(&bf);


    RhBuilderPtr reader = makePtr<RhBuilder>(file_name, &is);
    TSPLINE::TSplinePtr spline = reader->findTSpline();
    return spline;
}

extern "C"
jstring
Java_alex_t_1spline_t_1spline_TsplineNativeActivity2_stringFromJNI(JNIEnv* env, jobject thiz, jstring z) {
    char s[100];
    s[0] = 0;
    const char *aa = env->GetStringUTFChars( z, 0 );
    strcat(s, aa);
    name = s;
    return env->NewStringUTF(s);
}
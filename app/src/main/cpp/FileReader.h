//
// Created by alex on 31.01.17.
//

#ifndef T_SPLINE_FILEREADER_H
#define T_SPLINE_FILEREADER_H

#include <jni.h>
#include <android/asset_manager.h>
#include "rhbuilder.h"
#include "tspline.h"

class FileReader{
public:
    FileReader();
    ~FileReader();

    TSPLINE::TSplinePtr read_file();

private:

};
#endif //T_SPLINE_FILEREADER_H

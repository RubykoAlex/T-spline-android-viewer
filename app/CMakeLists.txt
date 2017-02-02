#
# Copyright (C) The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.4.1)

# build native_app_glue as a static lib
#add_library(app-glue STATIC
#            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -fexceptions -fno-rtti -landroid -O2")

# build the ndk-helper library
set(ndk_helper_dir src/main/cpp/ndk_helper)
add_subdirectory(${ndk_helper_dir} ndk_helper)


set(tspline_dir src/main/cpp/tspline)
set(newmat_dir src/main/cpp/newmat)
set(root_dir src/main/cpp)
set(rhbuilder_dir src/main/cpp/rhbuilder)

# now build app's shared lib
add_library(main SHARED
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
            ${root_dir}/TsplineNativeActivity.cpp
            ${root_dir}/TsplineRenderer.cpp
            ${root_dir}/mouse.cpp
            ${root_dir}/simple.cpp )

add_library(main2 SHARED
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
            ${root_dir}/TsplineNativeActivity2.cpp
            ${root_dir}/TsplineRenderer2.cpp
            ${root_dir}/FileReader.cpp)

target_include_directories(main PRIVATE
                           ${ANDROID_NDK}/sources/android/cpufeatures
                           ${ANDROID_NDK}/sources/android/native_app_glue
                           ${ndk_helper_dir}
                           ${root_dir}
                           ${tspline_dir}
                           ${newmat_dir}
                           ${rhbuilder_dir})

target_include_directories(main2 PRIVATE
                           ${ANDROID_NDK}/sources/android/cpufeatures
                           ${ANDROID_NDK}/sources/android/native_app_glue
                           ${ndk_helper_dir}
                           ${root_dir}
                           ${tspline_dir}
                           ${newmat_dir}
                           ${rhbuilder_dir})
include_directories(${newmat_dir}/ ${tspline_dir}/ ${rhbuilder_dir}/)
add_library(newmat-lib
            SHARED
               ${newmat_dir}/bandmat.cpp
               ${newmat_dir}/cholesky.cpp
               ${newmat_dir}/evalue.cpp
               ${newmat_dir}/fft.cpp
               ${newmat_dir}/hholder.cpp
               ${newmat_dir}/jacobi.cpp
               ${newmat_dir}/myexcept.cpp
               ${newmat_dir}/newmat1.cpp
               ${newmat_dir}/newmat2.cpp
               ${newmat_dir}/newmat3.cpp
               ${newmat_dir}/newmat4.cpp
               ${newmat_dir}/newmat5.cpp
               ${newmat_dir}/newmat6.cpp
               ${newmat_dir}/newmat7.cpp
               ${newmat_dir}/newmat8.cpp
               ${newmat_dir}/newmat9.cpp
               ${newmat_dir}/newmatex.cpp
               ${newmat_dir}/newmatnl.cpp
               ${newmat_dir}/newmatrm.cpp
               ${newmat_dir}/solution.cpp
               ${newmat_dir}/sort.cpp
               ${newmat_dir}/submat.cpp
               ${newmat_dir}/svd.cpp
               ${newmat_dir}/newfft.cpp
               ${newmat_dir}/nm_misc.cpp)


add_library(tspline-lib
            SHARED
                ${tspline_dir}/utils.cpp
                ${tspline_dir}/basis.cpp
            	${tspline_dir}/convert.cpp
            	${tspline_dir}/splbase.cpp
            	${tspline_dir}/tspline.cpp
            	${tspline_dir}/factory.cpp
           		${tspline_dir}/virtual.cpp
     			${tspline_dir}/tjunction.cpp
     			${tspline_dir}/multiplicity.cpp
            	${tspline_dir}/visitor.cpp
            	${tspline_dir}/finder.cpp
            	${tspline_dir}/extractor.cpp
            	${tspline_dir}/editor.cpp
            	${tspline_dir}/derivator.cpp
            	${tspline_dir}/cross.cpp
            	${tspline_dir}/trimesh.cpp
            	${tspline_dir}/tessellator.cpp
            	${tspline_dir}/validator.cpp
            	)

add_library(rhbuilder-lib
            SHARED
            ${rhbuilder_dir}/rhparser.cpp
            ${rhbuilder_dir}/rhspreader.cpp
            ${rhbuilder_dir}/rhbuilder.cpp)

# add lib dependencies
target_link_libraries(main
                      android
                   #   app-glue
                      atomic
                      EGL
                      GLESv2
                      log
                      ndk-helper
                      tspline-lib
                      newmat-lib
                      rhbuilder-lib)

target_link_libraries(main2
                      android
                   #   app-glue
                      atomic
                      EGL
                      GLESv2
                      log
                      ndk-helper
                      tspline-lib
                      newmat-lib
                      rhbuilder-lib)
target_link_libraries( tspline-lib
                       newmat-lib)

target_link_libraries( rhbuilder-lib
                        tspline-lib
                        newmat-lib)
# T-spline-android-viewer
T-spline android viewer allows to read *.tsm files and display T-spline models on an android devices


Author: Oleksandr Zavalnyi


Overview:

This application is built on the T-SPLINE kernel (written in C++). The kernel reads a T-Splines mesh file (*.tsm), converts it into the T-spline model and generates its trimesh representation on an android device. Using OpenGL API the trimesh data can be further displayed on the device screen. 


Used sources:

1. T-SPLINE Library: https://github.com/GrapeTec/T-SPLINE.git 
          
2. Android NDK samples with Android Studio (teapots): https://github.com/googlesamples/android-ndk.git


Structure:

1. Input t-mesh files (*.tsm) are put in the assets folder.

2. Main used libraries:  newmat-lib (used for calculations),
                         tspline-lib (T-SPLINE kernel),
                         rhbuilder-lib (used for parsing of T-Splines mesh fines and converting them into T-spline models)
 
 
 
 
Minimum requirements:

Android Studio 2.2 or higher with the Android plugin for Gradle version 2.2.0 or higher. To setup Android Studio to use native code check https://developer.android.com/studio/projects/add-native-code.html



Usage:

1. "Show demo" button: displays hard coded T-spline model

2. "File name" field: here the file name you want to load have to be specified. It should be one of the files from assets/rhino     folder (you do not need to write ".tsm" at the end of the file name)

3. "Load model" button: loads and displays the model specified in the  "File name" field

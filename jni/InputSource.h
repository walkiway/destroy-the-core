/*
 * InputSource.h
 *
 *  Created on: Nov 24, 2010
 *      Author: Ryan Maloney
 */

#ifndef INPUTSOURCE_H_
#define INPUTSOURCE_H_

#include <jni.h>

extern "C"
{
JNIEXPORT void
JNICALL Java_com_errantgames_input_InputSource_nativeKeyPress(JNIEnv* env,
    jobject thiz, jint keySymbol);

JNIEXPORT void
JNICALL Java_com_errantgames_input_InputSource_nativeKeyRelease(JNIEnv* env,
    jobject thiz, jint keySymbol);

JNIEXPORT void
JNICALL Java_com_errantgames_input_InputSource_nativeTouchPressDown(JNIEnv* env,
    jobject thiz, jfloat x, jfloat y);
}
#endif /* INPUTSOURCE_H_ */

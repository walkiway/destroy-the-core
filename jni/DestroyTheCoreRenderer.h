#ifndef __DESTROYTHECORE_RENDERER_H_INCLUDED__
#define __DESTROYTHECORE_RENDERER_H_INCLUDED__

#include <jni.h>

extern "C"
{
JNIEXPORT void
JNICALL Java_com_errantgames_DestroyTheCoreRenderer_nativeInitGL(
    JNIEnv* env, jobject thiz);

JNIEXPORT void
JNICALL Java_com_errantgames_DestroyTheCoreRenderer_nativeResize(
    JNIEnv* env, jobject thiz, jint width, jint height);

JNIEXPORT void
JNICALL Java_com_errantgames_DestroyTheCoreRenderer_nativeGetStatus(
    JNIEnv* env, jobject thiz, jobject status);

JNIEXPORT void
JNICALL Java_com_errantgames_DestroyTheCoreRenderer_nativeSendEvent(
    JNIEnv* env, jobject thiz, jobject event);

JNIEXPORT void
JNICALL Java_com_errantgames_DestroyTheCoreRenderer_nativeDrawIteration(
    JNIEnv* env, jobject thiz);
}

#endif

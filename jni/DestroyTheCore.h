#ifndef __DESTROYTHECORE_H_INCLUDED__
#define __DESTROYTHECORE_H_INCLUDED__

#include <jni.h>

extern "C"
{
JNIEXPORT void JNICALL Java_com_errantgames_DestroyTheCore_nativeSetApkPath(
    JNIEnv* env, jobject thiz, jstring apkFilePath);

JNIEXPORT void JNICALL Java_com_errantgames_DestroyTheCore_nativeAddResource(
    JNIEnv* env, jobject thiz, jstring bundle, jstring resourceName, jlong startOffset, jlong fileLength);

JNIEXPORT void JNICALL Java_com_errantgames_DestroyTheCore_nativeOnCreate(
    JNIEnv* env, jobject thiz);

JNIEXPORT void JNICALL Java_com_errantgames_DestroyTheCore_nativeOnPause(
    JNIEnv* env, jobject thiz);

JNIEXPORT void JNICALL Java_com_errantgames_DestroyTheCore_nativeOnResume(
    JNIEnv* env, jobject thiz);

JNIEXPORT void JNICALL Java_com_errantgames_DestroyTheCore_nativeOnDestroy(
    JNIEnv* env, jobject thiz);
}

#endif

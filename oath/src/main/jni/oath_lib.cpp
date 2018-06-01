#include <jni.h>
#include <string>
#include <stdlib.h>
#include "oath/oath.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_lianluo_smartlock_utils_PwUtils_getOfflinePw(JNIEnv *env, jclass type, jstring secret_) {
    const char *secret = env->GetStringUTFChars(secret_, 0);
    time_t now = time(0);
    char result[16];

    char first[8];
    oath_totp_generate(secret, strlen(secret), now, 30, 0, 8, first);
    for (int i = 0; i < 8; i++) {
        result[i] = first[i];
    }

    char second[8];
    oath_totp_generate(secret, strlen(secret), now+30, 30, 0, 8, second);
    for (int i = 0; i < 8; i++) {
        result[8+i] = second[i];
    }
    env->ReleaseStringUTFChars(secret_, secret);

    return env->NewStringUTF(result);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_lianluo_smartlock_utils_PwUtils_getOfflineTime(JNIEnv *env, jclass type, jstring secret_) {
    const char *secret = env->GetStringUTFChars(secret_, 0);
    char result[16];

    time_t now = time(0);
    char otp[8];
    oath_totp_generate(secret, strlen(secret), now, 30, 0, 8, otp);
    for (int i = 0; i < 8; i++) {
        result[i] = otp[i];
    }

    long num = now-1483200000;

    for(int i = 0; i < 8; i++) {
     int temp = num & 0x0000000F;
        result[15-i] = (temp < 10) ? ('0' +temp) : ('a' + temp -10);
        num = num >> 4; //右移4位
    }

    env->ReleaseStringUTFChars(secret_, secret);
    return env->NewStringUTF(result);
}
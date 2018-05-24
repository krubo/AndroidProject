package com.ainanmu.nmbase

import android.util.Log

/**
 * Created by krubo on 2018/5/24.
 */

private fun createLog(stackTrace: StackTraceElement, log: String) = "${stackTrace.methodName}(${stackTrace.fileName}:${stackTrace.lineNumber})${log}"

fun v(log: String) {
    val stackTrace = Throwable().stackTrace[1]
    Log.v(stackTrace.fileName, createLog(stackTrace, log))
}

fun d(log: String) {
    val stackTrace = Throwable().stackTrace[1]
    Log.d(stackTrace.fileName, createLog(stackTrace, log))
}

fun i(log: String) {
    val stackTrace = Throwable().stackTrace[1]
    Log.i(stackTrace.fileName, createLog(stackTrace, log))
}

fun w(log: String) {
    val stackTrace = Throwable().stackTrace[1]
    Log.w(stackTrace.fileName, createLog(stackTrace, log))
}

fun e(log: String) {
    val stackTrace = Throwable().stackTrace[1]
    Log.e(stackTrace.fileName, createLog(stackTrace, log))
}

fun wtf(log: String) {
    val stackTrace = Throwable().stackTrace[1]
    Log.wtf(stackTrace.fileName, createLog(stackTrace, log))
}
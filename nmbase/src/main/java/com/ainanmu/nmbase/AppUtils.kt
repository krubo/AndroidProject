package com.ainanmu.nmbase

import android.app.ActivityManager
import android.content.Context

import android.app.Service
import android.support.v7.app.AppCompatActivity

/**
 * Created by krubo on 2018/5/24.
 */

val Context.versionName get() = packageManager.getPackageInfo(packageName, 0).versionName

val Context.versionCode get() = packageManager.getPackageInfo(packageName, 0).versionCode

val AppCompatActivity.versionName get() = packageManager.getPackageInfo(packageName, 0).versionName

val AppCompatActivity.versionCode get() = packageManager.getPackageInfo(packageName, 0).versionCode

fun <T : Service> T.isRunning(context: Context?) = {
    val manager: ActivityManager = context?.getSystemService(Context.ACTIVITY_SERVICE) as ActivityManager
    var serviceInfos: List<ActivityManager.RunningServiceInfo> = manager.getRunningServices(Integer.MAX_VALUE)
    for (serviceInfo in serviceInfos) {
        if (serviceInfo.service.className == javaClass.name) true
    }
    false
}

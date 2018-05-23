package com.ainanmu.nmbase

import android.support.v7.app.AppCompatActivity
import android.widget.Toast

/**
 * Created by krubo on 2018/5/23.
 */
fun AppCompatActivity.showToast(resId: Int, duration: Int = Toast.LENGTH_SHORT) {
    Toast.makeText(this, resId, duration).show()
}

fun AppCompatActivity.showToast(text: CharSequence?, duration: Int = Toast.LENGTH_SHORT) {
    Toast.makeText(this, text, duration).show()
}

fun android.app.Fragment.showToast(resId: Int, duration: Int = Toast.LENGTH_SHORT) {
    Toast.makeText(activity, resId, duration).show()
}

fun android.app.Fragment.showToast(text: CharSequence?, duration: Int = Toast.LENGTH_SHORT) {
    Toast.makeText(activity, text, duration).show()
}

fun android.support.v4.app.Fragment.showToast(resId: Int, duration: Int = Toast.LENGTH_SHORT) {
    Toast.makeText(activity, resId, duration).show()
}

fun android.support.v4.app.Fragment.showToast(text: CharSequence?, duration: Int = Toast.LENGTH_SHORT) {
    Toast.makeText(activity, text, duration).show()
}
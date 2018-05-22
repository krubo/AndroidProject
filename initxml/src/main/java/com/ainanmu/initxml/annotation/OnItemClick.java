package com.ainanmu.initxml.annotation;

import android.support.annotation.IdRes;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;

import static java.lang.annotation.ElementType.METHOD;
import static java.lang.annotation.RetentionPolicy.CLASS;

/**
 * Created by krubo on 2018/5/11.
 */
@Retention(CLASS)
@Target(METHOD)
public @interface OnItemClick {

    @IdRes int value();
}

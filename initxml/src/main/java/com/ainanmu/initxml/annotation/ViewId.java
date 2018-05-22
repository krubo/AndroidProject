package com.ainanmu.initxml.annotation;

import android.support.annotation.IdRes;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;

import static java.lang.annotation.ElementType.FIELD;
import static java.lang.annotation.RetentionPolicy.RUNTIME;

/**
 * Created by krubo on 2018/5/11.
 */

@Retention(RUNTIME)
@Target(FIELD)
public @interface ViewId {

    @IdRes int value();
}

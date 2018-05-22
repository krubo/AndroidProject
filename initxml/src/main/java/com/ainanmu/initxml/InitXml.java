package com.ainanmu.initxml;

import android.app.Activity;
import android.view.View;

import com.ainanmu.initxml.annotation.ViewId;

import java.lang.reflect.Field;

/**
 * Created by krubo on 2018/5/14.
 */

public class InitXml {

    public <T extends Activity> void regist(T t) {
        Field[] fields = t.getClass().getDeclaredFields();
        Field.setAccessible(fields, true);
        for (Field field : fields) {
            if (field.getAnnotation(ViewId.class) != null) {
                int resId = field.getAnnotation(ViewId.class).value();
                try {
                    View v = (View) field.get(t);
                    v = t.findViewById(resId);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public void regist(View view) {

    }

}

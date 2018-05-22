package com.ainanmu.nmdb

import android.database.sqlite.SQLiteDatabase

/**
 * Created by krubo on 2018/5/22.
 */
interface DBCallback {
    /**
     * 创建数据库，创建表
     */
    fun onCreate(sqLiteDatabase: SQLiteDatabase);

    /**
     * 版本升级
     */
    fun onUpgrade(sqLiteDatabase: SQLiteDatabase, oldVersion: Int, newVersion: Int);
}
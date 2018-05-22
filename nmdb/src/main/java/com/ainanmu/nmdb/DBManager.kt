package com.ainanmu.nmdb

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import java.lang.reflect.Field

/**
 * Created by krubo on 2018/5/22.
 */
object DBManager {
    var sqLiteDatabase: SQLiteDatabase? = null

    /**
     * 实例化
     */
    fun newInstance(context: Context, dbName: String?, version: Int, callback: DBCallback?) {
        sqLiteDatabase = object : SQLiteOpenHelper(context, dbName, null, version) {
            override fun onCreate(sqLiteDatabase: SQLiteDatabase) {
                callback!!.onCreate(sqLiteDatabase)
            }

            override fun onUpgrade(sqLiteDatabase: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
                callback!!.onUpgrade(sqLiteDatabase, oldVersion, newVersion)
            }
        }.writableDatabase;
    }

    /**
     * 创建表
     * @param clss 创建表的实体类
     */
    fun createTable(db: SQLiteDatabase?, vararg clss: Class<*>) {
        for (cls in clss) {
            val fields = cls.declaredFields
            Field.setAccessible(fields, true)
            if (cls.isAnnotation) continue
            var sql = "";
            for (field in fields) {
                sql = if (field.getAnnotation(DBField::class.java) != null) {
                    if (sql.equals("")) "$sql ${field.name} varchar(100)" else "$sql, ${field.name} varchar(100)"
                } else sql
            }
            if (sql.equals("")) continue
            sql = "CREATE TABLE ${cls.getAnnotation(DBTableName::class.java).tableName} ($sql);"
            db!!.execSQL(sql)
        }
    }

}
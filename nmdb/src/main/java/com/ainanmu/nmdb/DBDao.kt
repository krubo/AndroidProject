package com.ainanmu.nmdb

import android.content.ContentValues
import android.database.Cursor
import java.lang.reflect.Field
import java.util.ArrayList

/**
 * Created by krubo on 2018/5/22.
 */
open class DBDao<T>(val cls: Class<T>) {

    private fun getContentVlues(t: T): ContentValues {
        val fields = cls.declaredFields
        Field.setAccessible(fields, true)
        var values = ContentValues()
        for (field in fields) {
            if (field.getAnnotation(DBField::class.java) != null) {
                val value = field.get(t)
                values.put(field.name, "$value")
            }
        }
        return values
    }

    /**
     * 插入单条数据
     */
    fun insert(t: T) {
        DBManager.sqLiteDatabase!!.insert(cls.getAnnotation(DBTableName::class.java).tableName,
                null, getContentVlues(t))
    }

    /**
     * 拆入一组数据
     */
    fun insert(list: Array<T>) {
        DBManager.sqLiteDatabase!!.beginTransaction()
        for (t in list) {
            insert(t)
        }
        DBManager.sqLiteDatabase!!.endTransaction()
    }

    /**
     * 根据条件取出数据
     */
    fun query(selection: String? = null, selectionArgs: Array<String>? = null,
              groupBy: String? = null, having: String? = null, orderBy: String? = null): ArrayList<T> {
        var list = ArrayList<T>()
        DBManager.sqLiteDatabase!!.beginTransaction()
        var cursor: Cursor? = null
        cursor = DBManager.sqLiteDatabase!!.query(cls.getAnnotation(DBTableName::class.java).tableName,
                null, selection, selectionArgs, groupBy, having, orderBy)
        while (cursor!!.moveToNext()) {
            val t = cls.newInstance()
            val fields = cls.declaredFields
            Field.setAccessible(fields, true)
            for (field in fields) {
                if (field.getAnnotation(DBField::class.java) == null) continue
                val type = field.type
                val value = cursor!!.getString(cursor!!.getColumnIndex(field.name))
                when (type) {
                    String::class.java -> field.set(t, value)
                    Byte::class.java -> field.set(t, value.toByteOrNull())
                    Boolean::class.java -> field.setBoolean(t, if (value == null) false else value.toBoolean())
                    Int::class.java -> field.setInt(t, value.toIntOrNull()!!)
                    Long::class.java -> field.setLong(t, value.toLongOrNull()!!)
                    Short::class.java -> field.set(t, value.toShortOrNull())
                    Float::class.java -> field.setFloat(t, value.toFloatOrNull()!!)
                    Double::class.java -> field.setDouble(t, value.toDoubleOrNull()!!);
                }
            }
            list.add(t)
        }
        DBManager.sqLiteDatabase!!.endTransaction()
        cursor!!.close()
        return list
    }

    /**
     * 修改单条数据
     */
    fun update(t: T, whereClause: String, whereArgs: Array<String>) {
        DBManager.sqLiteDatabase!!.update(cls.getAnnotation(DBTableName::class.java).tableName,
                getContentVlues(t), whereClause, whereArgs)

    }

    /**
     * 删除单条数据
     */
    fun delete(t: T) {
        var fields = cls.declaredFields
        Field.setAccessible(fields, true)
        var whereClause: String = "";
        var whereArgs = ArrayList<String>()
        for (field in fields) {
            if (field.getAnnotation(DBField::class.java) == null) continue
            val value = field.get(t)
            val name = field.name
            whereClause = if (whereClause.equals("")) "$name=?" else "$whereClause and $name=?"
            whereArgs.add(if (value == null) "" else "$value")
        }
        if (whereArgs.size == 0) return
        delete(t, whereClause, whereArgs.toTypedArray())
    }

    /**
     * 删除单条数据
     */
    fun delete(t: T, whereClause: String, whereArgs: Array<String>) {
        DBManager.sqLiteDatabase!!.delete(cls.getAnnotation(DBTableName::class.java).tableName,
                whereClause, whereArgs)
    }

    /**
     * 删除所有数据
     */
    fun deleteAll() {
        DBManager.sqLiteDatabase!!.delete(cls.getAnnotation(DBTableName::class.java).tableName, null, null)
    }

    /**
     * 删除当前表
     */
    fun dropTable() {
        execSQL("DROP TABLE ${cls.getAnnotation(DBTableName::class.java).tableName}")
    }

    /**
     * 检查表是否为空
     */
    fun isEmptyTable() = {
        var cursor: Cursor? = DBManager.sqLiteDatabase!!.query(cls.getAnnotation(DBTableName::class.java).tableName,
                null, null, null, null, null, null);
        var size = cursor!!.count
        cursor!!.close()
        size == 0
    }

    /**
     * 执行sql语句
     */
    fun execSQL(sql: String?) = DBManager.sqLiteDatabase!!.execSQL(sql)

}
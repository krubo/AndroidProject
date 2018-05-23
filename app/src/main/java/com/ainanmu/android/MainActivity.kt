package com.ainanmu.android

import android.database.sqlite.SQLiteDatabase
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.ainanmu.nmbase.*
import com.ainanmu.nmdb.*
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()
        DBManager.newInstance(
                context = baseContext, dbName = "Persion", version = 1,
                callback = object : DBCallback {

                    override fun onCreate(sqLiteDatabase: SQLiteDatabase) {
                        DBManager.createTable(sqLiteDatabase, Persion::class.java)
                    }

                    override fun onUpgrade(sqLiteDatabase: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
                    }

                }
        )

        var dao = PersionDao();
        var persion = Persion();
        persion.age = 15;
        persion.name = "wangsi"
        dao.insert(persion)
        var persions = dao.query()
        for (persion in persions) {
            println(persion.toString())
        }

        val str: String? = null

        main_click_me.setOnClickListener { showToast(text = str?.getString()) }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    @DBTableName(tableName = "persion")
    class Persion {
        @DBField
        var name = ""
        @DBField
        var age = 0

        override fun toString() = "name:$name, age:$age"
    }

    class PersionDao : DBDao<Persion>(cls = Persion::class.java) {

    }
}

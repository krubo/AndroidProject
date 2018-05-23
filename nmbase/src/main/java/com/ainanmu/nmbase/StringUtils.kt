package com.ainanmu.nmbase

import java.util.regex.Pattern

/**
 * Created by krubo on 2018/5/23.
 */
fun String.getString() = if (isNullOrEmpty()) "" else this

fun String.getStringByTrim() = if (isNullOrEmpty()) "" else trim()

fun match(regex: String?, text: String?) = Pattern.compile(regex).matcher(text).matches()

//是否是邮箱
fun String.isEmail() = match(regex = "^([a-zA-Z0-9_\\-\\.]+)@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.)" +
        "|(([a-zA-Z0-9\\-]+\\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\\]?)\$", text = this)

//是否是ip地址
fun String.isIpAddr() = {
    var num = "(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)"
    match(regex = "^$num\\.$num\\.$num\\.$num \$", text = this)
}

//是否是网址
fun String.isUrl() = match(regex = "http(s)?://([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?", text = this)

//是否是邮编
fun String.isPostalcode() = match(regex = "^\\d{6}$", text = this)

//是否是手机号
fun String.isPhone() = match(regex = "^[1]+[3,4,5,6,7,8]+\\d{9}$", text = this)

//是否是电话
fun String.isTelephone() = match(regex = "^(\\d{3,4}-)?\\d{6,8}$", text = this)

//是否是身份证号
fun String.isIDcard() = match(regex = "(^\\d{18}$)|(^\\d{15}$)", text = this)

//是否是整数
fun String.isInt() = match(regex = "^[0-9]*$", text = this)

//是否是数字（可带小数点）
fun String.isDecimal() = if ("0.0" == this || "0" == this) false else match(regex = "\\d+(\\.\\d+)?", text = this)

//判断是否是Emoji
fun Char.isEmoji() = !(toInt() == 0x0 || toInt() == 0x9 || toInt() == 0xA ||
        toInt() == 0xD || (toInt() >= 0x20 && toInt() <= 0xD7FF) ||
        (toInt() >= 0xE000 && toInt() <= 0xFFFD) || (toInt() >= 0x10000 && toInt() <= 0x10FFFF))

//是否是中文
fun Char.isChinese() =
        when (Character.UnicodeBlock.of(this)) {
            Character.UnicodeBlock.CJK_UNIFIED_IDEOGRAPHS,
            Character.UnicodeBlock.CJK_COMPATIBILITY_IDEOGRAPHS,
            Character.UnicodeBlock.CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A,
            Character.UnicodeBlock.GENERAL_PUNCTUATION,
            Character.UnicodeBlock.CJK_SYMBOLS_AND_PUNCTUATION,
            Character.UnicodeBlock.HALFWIDTH_AND_FULLWIDTH_FORMS
            -> true
            else -> false
        }




package com.lianluo.smartlock.utils;

/**
 * Created by krubo on 2018/5/31.
 */

public class PwUtils {

    static {
        System.loadLibrary("pw_lib");
    }

    private native static String getOfflinePw(String secret);

    public native static String getOfflineTime(String secret);

    public static String getOfflinePassword(String secret) {
        String pw = getOfflinePw(secret);
        return mixPw(pw.substring(0, 8)) + mixPw(pw.substring(8, 16));
    }

    private static String mixPw(String pw) {
        byte[] seed_key = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00, 0x03, 0x04};
        byte seed_c = 0;
        byte[] key_data = new byte[10];
        for (int i = 0; i < 8; i++) {
            int c = Integer.parseInt(pw.substring(i, i+1));
            if (c < 8) {
                key_data[i] = (byte) (c ^ seed_key[i]);
            } else {
                key_data[i] = (byte) c;
            }
        }

        for (int i = 0; i < 8; i++) {
            if (key_data[i] < 8 && i < 4) {
                seed_c = key_data[i];
                i = 3;
            }
            if (i > 3 && key_data[i] < 8) {
                key_data[i] ^= seed_c;
            }
        }
        String result = "";
        for (int i = 0; i < 8; i++) {
            result = result + key_data[i];
        }
        return result;
    }
}

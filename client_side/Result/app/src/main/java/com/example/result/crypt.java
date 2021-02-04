package com.example.result;

// import package current.project;


/*
add this to build.gradle dependencies:
    implementation 'com.cossacklabs.com:themis:0.13.1'

ERROR:
    Sometimes when working with Android projects in Release configuration you might get the following runtime error:
    Java.Lang.IncompatibleClassChangeError: no non-static method "Lcom/cossacklabs/themis/SecureCellSeal;.decrypt([B[B)[B"
    [orion.mobile]   at Java.Interop.JniEnvironment+InstanceMethods.GetMethodID (Java.Interop.JniObjectReference type, System.String name, System.String signature) [0x0005b] in <42d2b7086f0a46efb99253c5db1ecca9>:0
    [orion.mobile]   at Android.Runtime.JNIEnv.GetMethodID (System.IntPtr kls, System.String name, System.String signature) [0x00007] in <3080427739614e60a939a88bf3f838d5>:0
    [orion.mobile]   at Com.Cossacklabs.Themis.SecureCell+ISealInvoker.Decrypt (System.Byte[] p0, System.Byte[] p1) [0x00017] in <cd618986d1ce4194b63cdd3366dad291>:0
    [orion.mobile]   at Themis.Droid.CellSealDroid.UnwrapData (Themis.ISecureCellData cipherTextData, System.Byte[] context) [0x0007e] in <a492e7118e094c3296442a386fe5d80e>:0
    [orion.mobile]    --- End of inner exception stack trace --

SOLUTION:
    An easy solution is to add the following two lines to the proguard.cfg file of your Android app project:
        -keep class com.cossacklabs.themis.**
        -keep class com.cossacklabs.themis.** {*;}
 */

import android.util.Base64;

import com.cossacklabs.themis.InvalidArgumentException;
import com.cossacklabs.themis.NullArgumentException;
import com.cossacklabs.themis.SecureCell;
import com.cossacklabs.themis.SecureCellException;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class crypt {

    public String encrypt(String pass, String plain){
        Charset charset = StandardCharsets.UTF_8;
        SecureCell.Seal sc = SecureCell.SealWithPassphrase(pass, charset);
        byte[] protectedData = sc.encrypt(plain.getBytes(charset));
        String encodedString = Base64.encodeToString(protectedData, Base64.NO_WRAP);
        return encodedString;
    }

    public String decrypt(String pass, String encodedString){
        Charset charset = StandardCharsets.UTF_8;
        SecureCell.Seal sc = SecureCell.SealWithPassphrase(pass, charset);
        byte[] decodedString = Base64.decode(encodedString, Base64.NO_WRAP);
        String decryptedData;
        try {
            byte[] unprotected = sc.decrypt(decodedString);
            decryptedData = new String(unprotected, charset);
            return decryptedData;
        }catch (InvalidArgumentException | NullArgumentException | SecureCellException e) {
            return "failed";
        }
    }
}


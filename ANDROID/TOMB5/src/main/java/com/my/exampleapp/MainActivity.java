package com.my.exampleapp;


import android.content.res.AssetManager;
import android.os.Bundle;

import static android.os.Environment.getExternalStorageDirectory;

public class MainActivity extends org.libsdl.app.SDLActivity {

    /**
     * This method is called by SDL before loading the native shared libraries.
     * It can be overridden to provide names of shared libraries to be loaded.
     * The default implementation returns the defaults. It never returns null.
     * An array returned by a new implementation must at least contain "SDL2".
     * Also keep in mind that the order the libraries are loaded may matter.
     *
     * @return names of shared libraries to be loaded (e.g. "SDL2", "main").
     */
    @Override
    protected String[] getLibraries() {
        return new String[]{
                "SDL2",
                "EGL",
                "GLESv3",
                "MAIN"
        };
    }

    private AssetManager mgr;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.out.println(getExternalStorageDirectory());
    }
}

package com.errantgames;

import java.io.IOException;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

import com.errantgames.input.InputSource;

public class DestroyTheCore extends Activity
{
  static
  {
    System.loadLibrary("destroythecore");
  }

  private GLSurfaceView view;
  private InputSource inputSource;

  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    nativeOnCreate();

    ApplicationInfo applicationInfo = getApplicationContext()
        .getApplicationInfo();
    nativeSetApkPath(applicationInfo.sourceDir);
    super.onCreate(savedInstanceState);

    try
    {
      addAssets("Tiles");
      addAssets("Maps");
      addAssets("Prefabbed");
      addAssets("Creatures");
    }
    catch (IOException e)
    {
      Log.e("DestroyTheCore",
          "An exception has occurred while attempting to list resources.", e);
    }

    view = new DestroyTheCoreView(this);
    view.setFocusable(true);
    view.setFocusableInTouchMode(true);
    view.requestFocus();
    setContentView(view);

    inputSource = new InputSource();
    view.setOnKeyListener(inputSource);
    view.setOnClickListener(inputSource);
    view.setOnTouchListener(inputSource);
  }

  @Override
  protected void onPause()
  {
    super.onPause();
    nativeOnPause();
    view.onPause();
  }

  @Override
  protected void onResume()
  {
    super.onResume();
    nativeOnResume();
    view.onResume();
  }

  @Override
  protected void onDestroy()
  {
    nativeOnDestroy();
    super.onDestroy();
  }

  private void addAssets(String assetRoot) throws IOException
  {
    AssetManager assetManager = getAssets();

    for (String asset : assetManager.list(assetRoot))
    {
      try
      {
        Log.i("DestroyTheCore", "Found asset: " + asset);

        if (asset.contains("."))
        {
          AssetFileDescriptor fd = null;

          try
          {
            fd = assetManager.openFd(assetRoot + "/" + asset);

            Log.d("DestroyTheCore",
                String.format("Asset %s has length %s", asset, fd.getLength()));

            nativeAddResource(assetRoot, asset, fd.getStartOffset(),
                fd.getLength());
          }
          finally
          {
            if (null != fd)
            {
              fd.close();
            }
          }
        }
      }
      catch (Exception ioe)
      {
        Log.e("DestroyTheCore",
            "An exception has occurred while attempting to load a resource.",
            ioe);
      }
    }
  }

  public native void nativeSetApkPath(String apkPath);

  public native void nativeAddResource(String bundle, String resourceName,
      long startOffset, long fileLength);

  public native void nativeOnCreate();

  public native void nativeOnPause();

  public native void nativeOnResume();

  public native void nativeOnDestroy();
}
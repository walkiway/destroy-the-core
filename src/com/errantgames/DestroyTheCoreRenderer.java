package com.errantgames;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.util.Log;

public class DestroyTheCoreRenderer implements GLSurfaceView.Renderer
{ 
  private IrrlichtStatus mStatus;
  private Activity activity;
  
  public DestroyTheCoreRenderer(Activity activity)
  {
    mStatus = new IrrlichtStatus();
    mStatus.mQuit = false;
  }
  
  @Override
  public void onSurfaceCreated(GL10 gl, EGLConfig config)
  {
    nativeInitGL();
  }

  @Override
  public void onSurfaceChanged(GL10 gl, int width, int height)
  {
    nativeResize(width, height);
  }

  @Override
  public void onDrawFrame(GL10 gl)
  {
    nativeDrawIteration();

    nativeGetStatus(mStatus);

    if (mStatus.mQuit)
    {
      Log.e("MESSAGE", "QUIT");
      activity.finish();
    }
  }

  public native void nativeInitGL();

  public native void nativeResize(int w, int h);

  public native void nativeGetStatus(IrrlichtStatus status);

  public native void nativeSendEvent(IrrlichtEvent event);

  public native void nativeDrawIteration();

}

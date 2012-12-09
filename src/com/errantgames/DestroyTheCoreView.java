package com.errantgames;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;

public class DestroyTheCoreView extends GLSurfaceView
{
  private final static String LogTag = "DestroyTheCoreView-Java";
  
  private Renderer renderer;

  public DestroyTheCoreView(Context context)
  {
    super(context);
    renderer = new DestroyTheCoreRenderer((Activity)context);
    setRenderer(renderer);
  }

  public DestroyTheCoreView(Context context, boolean translucent, int depth,
      int stencil)
  {
    super(context);
    renderer = new DestroyTheCoreRenderer((Activity)context);
    setRenderer(renderer);
  }
  
//  @Override
//  public boolean onKeyDown(int keyCode, KeyEvent event)
//  {
//    Log.e(LogTag, "Key pressed down");
//    return super.onKeyDown(keyCode, event);
//  }
//
//  @Override
//  public boolean onKeyUp(int keyCode, KeyEvent event)
//  {
//    Log.e(LogTag, "Key released");
//    return super.onKeyUp(keyCode, event);
//  }
}

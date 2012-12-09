package com.errantgames.input;

import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.view.View.OnTouchListener;

public class InputSource implements OnKeyListener, OnTouchListener,
    OnClickListener
{
  private final static String LogTag = "InputSourceJava";

  @Override
  public void onClick(View v)
  {
    Log.d(LogTag, "Click event!");
  }

  @Override
  public boolean onTouch(View v, MotionEvent event)
  {
    if (MotionEvent.ACTION_DOWN == event.getAction())
    {
      Log.e(LogTag,
          String.format("Touch event at %f x %f!", event.getX(), event.getY()));
      nativeTouchPressDown(event.getX(), event.getY());
    }
    return true;
  }

  @Override
  public boolean onKey(View v, final int keyCode, final KeyEvent event)
  {
    Log.d(LogTag, String.format("Key event with code: %d", keyCode));
    final IrrlichtKeyCode code = IrrlichtKeyCode.getForKeyEvent(event);

    if (null != code)
    {
      switch (event.getAction())
      {
      case KeyEvent.ACTION_DOWN:
        Log.d(LogTag, "Key pressed down!");
        nativeKeyPress(code.getIrrlichtKeyCode());
        break;
      case KeyEvent.ACTION_UP:
        Log.d(LogTag, "Key released!");
        nativeKeyRelease(code.getIrrlichtKeyCode());
        break;
      }
    }

    return true;
  }

  public native void nativeKeyPress(int keyCode);

  public native void nativeKeyRelease(int keyCode);

  public native void nativeTouchPressDown(float x, float y);
}

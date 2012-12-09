package com.errantgames.input;

import android.view.KeyEvent;

public enum IrrlichtKeyCode
{
  KEY_LEFT(0x25), // LEFT ARROW key
  KEY_UP(0x26), // UP ARROW key
  KEY_RIGHT(0x27), // RIGHT ARROW key
  KEY_DOWN(0x28); // DOWN ARROW key

  int irrlichtKeyCode;

  IrrlichtKeyCode(int irrlichtKeyCode)
  {
    this.irrlichtKeyCode = irrlichtKeyCode;
  }

  public static IrrlichtKeyCode getForKeyEvent(KeyEvent keyEvent)
  {
    IrrlichtKeyCode keyCode = null;
    
    if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_UP)
    {
      keyCode = KEY_UP;
    }
    if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_DOWN)
    {
      keyCode = KEY_DOWN;
    }
    if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_LEFT)
    {
      keyCode = KEY_LEFT;
    }
    if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_RIGHT)
    {
      keyCode = KEY_RIGHT;
    }
    
    return keyCode;
  }
  
  public int getIrrlichtKeyCode()
  {
    return irrlichtKeyCode;
  }
  
}

XBOX360 Gamepad Support
=======================

**IT SUPPORTS THE *MYSTERIOUS* GUIDE BUTTON!**

It is a Gamepad class for getting input from XBOX 360 controller (it uses windows.h and Xinput, so it requires Windows (:D) and DirectX 9 SDK (or higher).

Usage
-----


```cpp
  Gamepad gamepad(0); // 0 is pad's ID - we can support up to 4 pads with id's 0, 1, 2, 3
  
  while (gamepad.connected()) // you don't really have to check for it,
                              // while (true) works well even if there
                              // is no controller
  {
    gamepad.update();
    
    ...
    ...
    ...
  }
```

Getting analog values (returns [-1, 1]):
```cpp
  float walkX = gamepad.leftStick().x;
  float walkY = gamepad.leftStick().y;
  
  float lookX = gamepad.rightStick().x;
  float lookY = gamepad.rightStick().y;
  
  float doSthElseX = gamepad.dPad().x;
  float doSthElseY = gamepad.dPad().y;
  
  // you can also check for analog being in it's DEADZONE,
  // but it will still return { 0.0f, 0.0f } if so
  // if you really want to check for deadzone, do the following:
  
  if (!gamepad.leftStick().dead)
  {
    // perform some expensive code
  }
```

Getting trigger values (returns [0, 1]):
```cpp
  float rt = gamepad.rightTrigger();
  float lt = gamepad.leftTrigger();
```

Getting button state (returns {0, 1}):
```cpp
  // same for B, X, Y, RB, LB, RightStick, LeftStick, Start, Back and the Guide button
  int valueOfA = gamepad.button(Gamepad::Button::A);
  
  int dPadRight = gamepad.button(Gamepad::DPad::Right);
```

(returns {true, false}):
```cpp
  // returns true only once - when A was just pressed
  gamepad.buttonDown(Gamepad::Button::A);
  // returns true if A is being pressed
  gamepad.buttonPressed(Gamepad::Button::A);
  // returns true only in the frame in which A was released
  gamepad.buttonUp(Gamepad::Button::A);
```

Vibrations (Rumble):
```cpp
  float leftVibration = 0.75f; // should be from [0, 1]
  float rightVibration = 0.4f; // should be from [0, 1]
  gamepad.vibrate(leftVibration, rightVibration);
```

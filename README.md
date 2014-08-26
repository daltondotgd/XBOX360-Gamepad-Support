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

Getting analog values:
```cpp
  float walkX = gamepad.leftStick().x;
  float walkY = gamepad.leftStick().y;
  
  float lookX = gamepad.rightStick().x;
  float lookY = gamepad.rightStick().y;
  
  // you can also check for analog being in it's DEADZONE,
  // but it will still return { 0.0f, 0.0f } if so
  // if you really want to check for deadzone, do the following:
  
  if (!gamepad.leftStick().dead)
  {
    // perform some expensive code
  }
```

Getting trigger values:
```cpp
  float rt = gamepad.rightTrigger();
  float lt = gamepad.leftTrigger();
```

Getting button state:
```cpp
  int valueOfA = gamepad.button(Gamepad::Button::A);
  // same for B, X, Y, RB, LB, RightStick, LeftStick, Start, Back and the Guide button
  
  int dPadRight = gamepad.button(Gamepad::DPad::Right);
  // I will add a digital-joystick behaviour to DPad soon
```

```cpp
  // returns true only once - when A was just pressed
  gamepad.buttonDown(Gamepad::Button::A);
  // returns true if A is being pressed
  gamepad.buttonPressed(Gamepad::Button::A);
  // returns true only in the frame in which A was released
  gamepad.buttonUp(Gamepad::Button::A);
```

Vibrating:
```cpp
  float leftVibration = 0.75f;
  float rightVibration = 0.4f;
  gamepad.vibrate(leftVibration, rightVibration);
```

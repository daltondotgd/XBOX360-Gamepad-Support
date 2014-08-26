/* Copyright (c) 2014 Krzysztof Pachulski
* License: The MIT License (MIT)
* MIT License page: http://opensource.org/licenses/MIT
*/

#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include <windows.h>
#include <Xinput.h>

#define MICROSOFTS_GREATEST_SECRET__THE_GUIDE_BUTTON_BYTE_ADDRESS 0x0400

static const WORD XINPUT_Buttons[] = {
    XINPUT_GAMEPAD_A,
    XINPUT_GAMEPAD_B,
    XINPUT_GAMEPAD_X,
    XINPUT_GAMEPAD_Y,
    XINPUT_GAMEPAD_DPAD_UP,
    XINPUT_GAMEPAD_DPAD_DOWN,
    XINPUT_GAMEPAD_DPAD_LEFT,
    XINPUT_GAMEPAD_DPAD_RIGHT,
    XINPUT_GAMEPAD_LEFT_SHOULDER,
    XINPUT_GAMEPAD_RIGHT_SHOULDER,
    XINPUT_GAMEPAD_LEFT_THUMB,
    XINPUT_GAMEPAD_RIGHT_THUMB,
    XINPUT_GAMEPAD_START,
    XINPUT_GAMEPAD_BACK,
    MICROSOFTS_GREATEST_SECRET__THE_GUIDE_BUTTON_BYTE_ADDRESS
};

class Gamepad
{
public:
    struct TopTopSecretControllerState
    {
        unsigned long eventCount;
        WORD wButtons;
        BYTE bLeftTrigger;
        BYTE bRightTrigger;
        SHORT sThumbLX;
        SHORT sThumbLY;
        SHORT sThumbRX;
        SHORT sThumbRY;
    };
    typedef int(_stdcall* STATE_GET_FUNCTION)(int, TopTopSecretControllerState*);
    STATE_GET_FUNCTION getControllerState;

    enum Buttons
    {
        A = 0,
        B = 1,
        X = 2,
        Y = 3,

        LB = 8,
        RB = 9,

        LeftStick = 10,
        RightStick = 11,

        Start = 12,
        Back = 13,

        Guide = 14
    };

    enum DPad
    {
        Up = 4,
        Down = 5,
        Left = 6,
        Right = 7
    };

    Gamepad(int id);

    TopTopSecretControllerState getState() { this->refreshState(); return this->state; }
    int getId() { return this->id; }
    bool connected();
    void update();

    struct Value2d {
        float x;
        float y;

        bool dead;
    };

    Value2d leftStick();
    Value2d rightStick();

    float leftTrigger();
    float rightTrigger();

    int button(int buttonId);

    bool buttonDown(int buttonId);
    bool buttonPressed(int buttonId);
    bool buttonUp(int buttonId);

    void vibrate(float leftMotor = 0.0f, float rightMotor = 0.0f);

private:
    DWORD refreshState();

    TopTopSecretControllerState state;
    int id;

    static const int ButtonCount = 15;

    enum ButtonState { NONE, DOWN, PRESSED, UP };

    ButtonState buttonStates[ButtonCount];
    bool buttonsPreviouslyPressed[ButtonCount];
    bool buttonsCurrentlyPressed[ButtonCount];
};

#endif // __GAMEPAD_H__
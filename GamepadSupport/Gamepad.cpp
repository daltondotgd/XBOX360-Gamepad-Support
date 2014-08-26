/* Copyright (c) 2014 Krzysztof Pachulski
* License: The MIT License (MIT)
* MIT License page: http://opensource.org/licenses/MIT
*/

#include "Gamepad.h"

#pragma comment(lib, "Xinput.lib")

Gamepad::Gamepad(int id)
{
    this->id = id;

    for (int i = 0; i < ButtonCount; ++i)
    {
        this->buttonsPreviouslyPressed[i] = false;
        this->buttonsCurrentlyPressed[i] = false;
    }

    HINSTANCE xinputDLL = LoadLibrary(L"C:/Windows/System32/xinput1_3.dll");
    FARPROC getProcessAddress = GetProcAddress(HMODULE(xinputDLL), (LPCSTR)100);
    this->getControllerState = STATE_GET_FUNCTION(getProcessAddress);

}

DWORD Gamepad::refreshState()
{
    memcpy(this->buttonsPreviouslyPressed, this->buttonsCurrentlyPressed, sizeof (this->buttonsPreviouslyPressed));

    ZeroMemory(&this->state, sizeof (TopTopSecretControllerState));
    return this->getControllerState(this->id, &this->state);
}

void Gamepad::update()
{
    this->refreshState();

    for (int i = 0; i < ButtonCount; ++i)
    {
        this->buttonsCurrentlyPressed[i] = (this->state.wButtons & XINPUT_Buttons[i]) == XINPUT_Buttons[i];

        if (this->buttonsCurrentlyPressed[i] && !this->buttonsPreviouslyPressed[i])
            this->buttonStates[i] = ButtonState::DOWN;
        else if (this->buttonsCurrentlyPressed[i] && this->buttonsPreviouslyPressed[i])
            this->buttonStates[i] = ButtonState::PRESSED;
        else if (!this->buttonsCurrentlyPressed[i] && this->buttonsPreviouslyPressed[i])
            this->buttonStates[i] = ButtonState::UP;
        else
            this->buttonStates[i] = ButtonState::NONE;

        this->buttonsPreviouslyPressed[i] = this->buttonsCurrentlyPressed[i];
    }
}

bool Gamepad::connected()
{
    auto result = this->refreshState();

    if (result == ERROR_SUCCESS)
        return true;
    else
        return false;
}

Gamepad::Value2d Gamepad::leftStick()
{
    short x = this->state.sThumbLX;
    short y = this->state.sThumbLY;

    if (x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
        && y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
        && x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
        && y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
        return{ 0, 0, true };

    Value2d value;
    value.x = (static_cast<float>(x) / (x < 0 ? 32768.0f : 32767.0f));
    value.y = (static_cast<float>(y) / (y < 0 ? 32768.0f : 32767.0f));
    value.dead = false;

    return value;
}

Gamepad::Value2d Gamepad::rightStick()
{
    short x = this->state.sThumbRX;
    short y = this->state.sThumbRY;

    if (x < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
        && y < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
        && x > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
        && y > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
        return{ 0, 0, true };

    Value2d value;
    value.x = (static_cast<float>(x) / (x < 0 ? 32768.0f : 32767.0f));
    value.y = (static_cast<float>(y) / (y < 0 ? 32768.0f : 32767.0f));
    value.dead = false;

    return value;
}

float Gamepad::leftTrigger()
{
    BYTE trigger = this->state.bLeftTrigger;
    if (trigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
        return 0.0f;

    return trigger / 255.0f;
}

float Gamepad::rightTrigger()
{
    BYTE trigger = this->state.bRightTrigger;
    if (trigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
        return 0.0f;

    return trigger / 255.0f;
}

void Gamepad::vibrate(float leftMotor, float rightMotor)
{
    XINPUT_VIBRATION vibrationState;

    ZeroMemory(&vibrationState, sizeof (XINPUT_VIBRATION));

    vibrationState.wLeftMotorSpeed = int(leftMotor * 65535.0f);
    vibrationState.wRightMotorSpeed = int(rightMotor * 65535.0f);

    XInputSetState(this->id, &vibrationState);
}

int Gamepad::button(int buttonId)
{
    if (this->buttonsCurrentlyPressed[buttonId])
        return 1;
    return 0;
}

bool Gamepad::buttonDown(int buttonId)
{
    return this->buttonStates[buttonId] == ButtonState::DOWN;
}

bool Gamepad::buttonPressed(int buttonId)
{
    return this->buttonStates[buttonId] == ButtonState::PRESSED;
}

bool Gamepad::buttonUp(int buttonId)
{
    return this->buttonStates[buttonId] == ButtonState::UP;
}
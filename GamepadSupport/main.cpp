#include "Gamepad.h"

#include <iostream>

#define BLOG(button) if (gamepad.buttonDown(Gamepad::Buttons::##button)) \
        std::cout << "Button " << #button << " down" << std::endl; \
    if (gamepad.buttonPressed(Gamepad::Buttons::##button)) \
        std::cout << "Button " << #button << " pressed" << std::endl; \
    if (gamepad.buttonUp(Gamepad::Buttons::##button)) \
        std::cout << "Button " << #button << " up" << std::endl

#define DLOG(button) if (gamepad.buttonDown(Gamepad::DPad::##button)) \
        std::cout << "DPad " << #button << " down" << std::endl; \
    if (gamepad.buttonPressed(Gamepad::DPad::##button)) \
        std::cout << "DPad " << #button << " pressed" << std::endl; \
    if (gamepad.buttonUp(Gamepad::DPad::##button)) \
        std::cout << "DPad " << #button << " up" << std::endl

int main()
{
    Gamepad gamepad(0);
    while (gamepad.connected())
    {
        gamepad.update();
        auto leftAnalog = gamepad.leftStick();
        auto rightAnalog = gamepad.rightStick();

        auto leftTrigger = gamepad.leftTrigger();
        auto rightTrigger = gamepad.rightTrigger();

        if (!leftAnalog.dead)
            std::cout << "Left analog: (" << leftAnalog.x << ", " << leftAnalog.y << ")" << std::endl;
        if (!rightAnalog.dead)
            std::cout << "Right analog: (" << rightAnalog.x << ", " << rightAnalog.y << ")" << std::endl;

        if (leftTrigger > 0)
            std::cout << "Left trigger: " << leftTrigger << std::endl;
        if (rightTrigger > 0)
            std::cout << "Right trigger: " << rightTrigger << std::endl;

        gamepad.vibrate(leftTrigger, rightTrigger);

        BLOG(A);
        BLOG(B);
        BLOG(X);
        BLOG(Y);

        DLOG(Up);
        DLOG(Down);
        DLOG(Left);
        DLOG(Right);

        BLOG(LB);
        BLOG(RB);

        BLOG(Start);
        BLOG(Back);

        BLOG(LeftStick);
        BLOG(RightStick);
        BLOG(Guide);

        for (int i = 0; i < 10000000; ++i);
    }
}

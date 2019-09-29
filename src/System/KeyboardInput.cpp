#include "System/KeyboardInput.h"

//#define DEBUG_OUTPUT_KEYBOARD_INPUT

#ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
#include<iostream>
#endif // DEBUG_OUTPUT_KEYBOARD_INPUT

KeyboardInput* KeyboardInput::s_instance;

KeyboardInput::KeyboardInput()
{
}

KeyboardInput* KeyboardInput::Instance()
{
    #ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
    std::cout << "Called for KeyboardInput::Instance()" << std::endl;
    #endif // DEBUG_OUTPUT_KEYBOARD_INPUT
    if (s_instance == 0) {
        #ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
        std::cout << "Made first KeyboardInput" << std::endl;
        #endif // DEBUG_OUTPUT_KEYBOARD_INPUT
        s_instance = new KeyboardInput();
    }
    return s_instance;
}

void KeyboardInput::TurnKeyOn(SDL_Keycode key)
{
    if (key == 15 || key == 13 ||
        key == 12 || key == 14)
    {
        m_keys_pressed[15]  = false;
        m_keys_pressed[13]    = false;
        m_keys_pressed[12]  = false;
        m_keys_pressed[14] = false;
    }
    m_keys_pressed[key] = true;
    #ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
    std::cout << key << " is pressed" << std::endl;
    #endif // DEBUG_OUTPUT_KEYBOARD_INPUT
}

void KeyboardInput::TurnKeyOff(SDL_Keycode key)
{
    m_keys_pressed[key] = false;
    //m_keys_pressed.erase(key);
    #ifdef DEBUG_OUTPUT_KEYBOARD_INPUT
    std::cout << key << " is released" << std::endl;
    #endif // DEBUG_OUTPUT_KEYBOARD_INPUT
}

bool KeyboardInput::IsKeyOn(SDL_Keycode key)
{
    if (m_keys_pressed.count(key) > 0)
        return m_keys_pressed[key];
    else
        return false;
}


#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

/**
 *  \file KeyboardInput.h
 *
 *  Defines class KeyboardInput which keeps track of user's presses and releases
 *  of buttons on the keyboard
 *
 */

#include <SDL2/SDL_keycode.h>
#include <map>

/** \class KeyboardInput
 *  \brief Class which keeps track of user's presses and releases of buttons on
 *         the keyboard
 *  \details This class is used to keep track of buttons the user is holding at
 *           any given time by using SLD_keycode for each button. Gives
 *           appropriate boolean value for each keyboard button. True if the
 *           button is being held, false otherwise.
 *           Also has methods for changing the boolean values according for each
 *           key.
 *           This class is singleton which means there can only be one instance
 *           of this class.
 *           This class is meant to be used with SDL_Event class.
 */
class KeyboardInput
{
    public:

        /**
         *  \brief Method to be used instead of constructor
         *
         *  Returns pointer to object KeyboardInput which is of singleton class
         *  so it will always return pointer to the same object.
         *  \return pointer to singleton KeyboardInput
         */
        static KeyboardInput* Instance();

        /**
         *  \brief Tells the object which button is pressed
         *
         *  Changes the object's value for the given key which represents one
         *  keyboard button so that the KeyboardInput object will know that
         *  the given button is being pressed.
         *  \param key SDL_Keycode of the button pressed
         *  \return void
         */
        void TurnKeyOn(SDL_Keycode key);
        /**
         *  \brief Tells the object which button is released
         *
         *  Changes the object's value for the given key which represents one
         *  keyboard button so that the KeyboardInput object will know that
         *  the given button is released.
         *  \param key SDL_Keycode of the button released
         *  \return void
         */
        void TurnKeyOff(SDL_Keycode key);
        /**
         *  \brief Tells if the button is pressed
         *
         *  Returns boolean value true if the button is pressed at any given
         *  moment.
         *  \param key SDL_Keycode of the button
         *  \return true if the button is pressed
         */
        bool IsKeyOn(SDL_Keycode key);

    protected:

        /**
         *  \brief Constructor for KeyboardInput
         *
         *  Makes an object of class KeyboardInput. Will return false values for
         *  every key at start.
         */
        KeyboardInput();

    private:
        std::map<SDL_Keycode,bool>  m_keys_pressed;

        static KeyboardInput*       s_instance;
};

#endif // KEYBOARDINPUT_H

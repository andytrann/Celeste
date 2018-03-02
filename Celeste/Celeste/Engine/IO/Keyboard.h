#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>

class Keyboard 
{
public:
	static void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

	static bool KeyDown(int _key);
	static bool KeyUp(int _key);
	static bool Key(int _key);

private:
	static bool keys[];
	static bool keysDown[];
	static bool keysUp[];
};

#endif
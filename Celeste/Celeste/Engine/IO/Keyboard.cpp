#include "Keyboard.h"

bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysDown[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysUp[GLFW_KEY_LAST] = { 0 };

void Keyboard::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	if (_key < 0)
		return;

	if (_action != GLFW_RELEASE && keys[_key] == false)
	{
		keysDown[_key] = true;
		keysUp[_key] = false;
	}

	if (_action == GLFW_RELEASE && keys[_key] == true)
	{
		keysDown[_key] = false;
		keysUp[_key] = true;
	}

	keys[_key] = _action != GLFW_RELEASE;
}

bool Keyboard::KeyDown(int _key)
{
	bool state = keysDown[_key];
	keysDown[_key] = false;
	return state;
}

bool Keyboard::KeyUp(int _key)
{
	bool state = keysUp[_key];
	keysUp[_key] = false;
	return state;
}

bool Keyboard::Key(int _key)
{
	return keys[_key];
}
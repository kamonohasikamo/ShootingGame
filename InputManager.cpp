#include "DxLib.h"
#include <string>

using namespace std;

enum class State
{
	NONE,
	LEFT,
	RIGHT,
	SPACE,
};

class InputManager
{
private:
	State nowState;
public:
	InputManager()
	{
		nowState = State::NONE;
	}

	void changeState(State state)
	{
		nowState = state;
	}

	State getState()
	{
		return nowState;
	}
};
#include "DxLib.h"
#include <string>

using namespace std;

enum class Scene
{
	START,
	GAME,
	RESULT
};

class SceneManager
{
private:
	Scene nowScene;
public:
	SceneManager()
	{
		nowScene = Scene::START;
	}

	void nextScene()
	{
		switch (nowScene)
		{
		case Scene::START:
			nowScene = Scene::GAME;
			break;
		case Scene::GAME:
			nowScene = Scene::RESULT;
			break;
		case Scene::RESULT:
			break;
		}
	}

	Scene getNowScene()
	{
		return nowScene;
	}
};
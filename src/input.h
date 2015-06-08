#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <map>
#include <vector>

class Input
{
public:
	std::vector<SDL_Keycode> m_events;

	Input() {}

	~Input() {}

	void pressKey(SDL_Keycode key)
	{
		m_events.push_back(key);
	}

	void purgeEvents()
	{
		m_events.clear();
	}
};

#endif

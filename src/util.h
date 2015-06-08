#ifndef UTIL_H
#define UTIL_H

#include <iostream>

class Util
{
public:
	static int random(int min, int max)
	{
		static bool first = true;
		if(first)
		{
			std::srand(time(NULL));
			first = false;
		}
		return min + std::rand() % (max - min);
	}
};

#endif

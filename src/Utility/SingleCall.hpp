#pragma once

#include <utility>

template <typename T>
class SingleCall
{
private:
	static inline bool s_alreadyRan = false;

public:
	template <typename TCallable, typename... TArgs>
	static void run(TCallable&& callable, TArgs&&... args)
	{
		if (s_alreadyRan)
			return;

		s_alreadyRan = true;
		callable(std::forward<TArgs>(args)...);
	}
};
#include "CommonDate.h"

namespace Engine::Common
{
    tm Date::GetLocalTime() 
	{
		time_t currentTime = time(NULL);
		tm localDate = *localtime(&currentTime);
        return localDate;
    }
}
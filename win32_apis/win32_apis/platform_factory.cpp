#include "platform_factory.hpp"

#ifdef _WIN32
#include "windows_adapter.hpp"
#endif


IPlatformAdapter* GetPlatformAdapter()
{
#ifdef _WIN32
	return new WindowsAdapter();
#endif
}
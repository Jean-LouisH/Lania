#pragma once

#if defined (_WIN32)
#if defined(_LANIA_ENGINE_EXPORTS)
#define  LANIA_ENGINE_API __declspec(dllexport)
#else
#define  LANIA_ENGINE_API __declspec(dllimport)
#endif
#else
#define LANIA_ENGINE_API
#endif

namespace Lania
{
	class LANIA_ENGINE_API Engine
	{
	public:
		Engine(
			int argc,
			char* argv[]);

		void run();
	private:
	};
}


#include "Native.hpp""

#ifdef _WIN32
	void Lania::Native::linkWindowsDLL()
	{
		HINSTANCE hGetProcIDDLL = LoadLibrary("LaniaNative.dll");

		if (hGetProcIDDLL)
		{
			this->native_init = (cpp_init)GetProcAddress(hGetProcIDDLL, "native_init");
			this->native_interpretStartLogic = (cpp_interpretStartLogic)GetProcAddress(hGetProcIDDLL, "native_interpretStartLogic");
			this->native_interpretInputLogic = (cpp_interpretInputLogic)GetProcAddress(hGetProcIDDLL, "native_interpretInputLogic");
			this->native_interpretProcessLogic = (cpp_interpretProcessLogic)GetProcAddress(hGetProcIDDLL, "native_interpretProcessLogic");
			this->native_interpretComputeLogic = (cpp_interpretComputeLogic)GetProcAddress(hGetProcIDDLL, "native_interpretComputeLogic");
			this->native_interpretLateLogic = (cpp_interpretLateLogic)GetProcAddress(hGetProcIDDLL, "native_interpretLateLogic");
			this->native_interpretFinalLogic = (cpp_interpretFinalLogic)GetProcAddress(hGetProcIDDLL, "native_interpretFinalLogic");
		}
	}
#endif

void Lania::Native::init(Scene* scene)
{
#ifdef _WIN32
	this->linkWindowsDLL();
#endif
	if (this->native_init)
		this->native_init(scene);
}

void Lania::Native::interpretStartLogic(Scene* scene)
{
	if(this->native_interpretStartLogic)
		this->native_interpretStartLogic(scene);
}

void Lania::Native::interpretInputLogic(Scene* scene)
{
	if (this->native_interpretInputLogic)
		this->native_interpretInputLogic(scene);
}

void Lania::Native::interpretProcessLogic(Scene* scene)
{
	if (this->native_interpretProcessLogic)
		this->native_interpretProcessLogic(scene);
}

void Lania::Native::interpretComputeLogic(Scene* scene, unsigned int computeTimeDelta_ms)
{
	if (this->native_interpretComputeLogic)
		this->native_interpretComputeLogic(scene, computeTimeDelta_ms);
}

void Lania::Native::interpretLateLogic(Scene* scene)
{
	if (this->native_interpretLateLogic)
		this->native_interpretLateLogic(scene);
}

void Lania::Native::interpretFinalLogic(Scene* scene)
{
	if (this->native_interpretFinalLogic)
		this->native_interpretFinalLogic(scene);
}
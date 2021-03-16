#pragma once

namespace Lania
{
	class SplashScreenTransition
	{
	public:
		void onStart();
		void onFrame();
	private:
		int countdown_value = 5.0;
		const char* next_scene = "project_list";
	};
}
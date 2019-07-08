#include <stdint.h>
#include <chrono>

namespace Lania 
{
	class ExecutionTimer
	{
	private:
		uint64_t delta_ns;
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> end;
	public:
		uint64_t getDelta_ns();
		void setStart();
		void setEnd();
		ExecutionTimer() :
			delta_ns(0)
		{}
	};
}

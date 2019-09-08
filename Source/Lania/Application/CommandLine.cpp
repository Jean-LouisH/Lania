#include "CommandLine.hpp"
#include <iostream>

void Lania::CommandLine::run(Core* core, Scene* scene)
{
#if _DEBUG
	if (this->isWaitingOnCommand)
	{
		bool isRepeating = true;

		std::cout << "\n\tLania Command Line\n\n";
		SDL_HideWindow(core->window);

		while (isRepeating)
		{
			String command;
			std::cout << ">> ";
			std::cin >> command;

			if (command == "shutdown")
			{
				isRepeating = false;
				this->isWaitingOnCommand = false;
				core->state = Core::states::SHUTDOWN;
			}
		}

		std::cout << std::endl;

		if (!isWaitingOnCommand)
			SDL_ShowWindow(core->window);
	}
#endif
}
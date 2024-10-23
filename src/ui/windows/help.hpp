#pragma once

#include <iostream>
#include <imgui.h>

namespace help
{
	namespace about
	{
		extern bool show_window;
		void loop(void);
	}

	namespace author
	{
		extern bool show_window;
		void loop(void);
	}

	namespace usage
	{
		extern bool show_window;
		void loop(void);
	}
}

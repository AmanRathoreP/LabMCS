#include "help.hpp"

bool help::usage::show_window = false;

void help::usage::loop(void)
{
    if (help::usage::show_window)
    {
        ImGui::Begin("Usage instructions", &help::usage::show_window);
        ImGui::Text("Use node structure to create timing diagrams and use timing graphs panel to analysis your node structure.\nNOTE: Rest of the documentation is currently under development.");
        ImGui::End();
    }
}

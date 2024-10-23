#include "settings.hpp"

bool settings::io::show_window = false;

void settings::io::loop(void)
{
    if (settings::io::show_window)
    {
        ImGui::Begin("Input/Output Settings", &settings::io::show_window);
        ImGui::Text("TODO");
        ImGui::End();
    }
}

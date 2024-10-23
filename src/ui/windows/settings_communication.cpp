#include "settings.hpp"

bool settings::communication::show_window = false;

void settings::communication::loop(void)
{
    if (settings::communication::show_window)
    {
        ImGui::Begin("Communication Settings", &settings::communication::show_window);
        ImGui::Text("TODO");
        ImGui::End();
    }
}

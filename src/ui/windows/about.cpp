#include "about.hpp"

bool help::about::show_window = false;

void help::about::loop(void)
{
    if (help::about::show_window)
    {
        ImGui::Begin("About", &help::about::show_window);
        ImGui::Text("This app is created by Aman Rathore from IISER Mohali; MS24058.");
        ImGui::End();
    }
}

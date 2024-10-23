#include "help.hpp"

bool help::about::show_window = false;

void help::about::loop(void)
{
    if (help::about::show_window)
    {
        ImGui::Begin("About", &help::about::show_window);
        ImGui::Text("This app is created by Aman Rathore to make user experience flexible while controlling laboratory equipments.\nThis app is initially created as per the requirements of PhD guys working at Dr. Aviru Kumar Basu's lab at INST Mohali.");
        ImGui::End();
    }
}

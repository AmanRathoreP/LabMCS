#include "author.hpp"

bool help::author::show_window = false;

void help::author::loop(void)
{
    if (help::author::show_window)
    {
        ImGui::Begin("About author(s)", &help::author::show_window);
        ImGui::Text("Author and maintainer i.e. Aman Rathore i.e. one who is writing this is currently studying at IISER Mohali and he is currently in his first year in 2024, his institute id is MS24058.\nEmail: aman.proj.rel@gmail.com\nTelegram id: aman0864\nInstitute Email id: ms24058@iisermohali.ac.in");
        ImGui::End();
    }
}

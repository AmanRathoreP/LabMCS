#include "timings_n_editor.hpp"

bool panels::timing::n_editor::show_window = false;

void panels::timing::n_editor::loop(void)
{
    if (panels::timing::n_editor::show_window)
    {
        ImGui::Begin("Timings Editor(Node based)", &panels::timing::n_editor::show_window);

        ImNodes::BeginNodeEditor();

        ImNodes::BeginNode(0);
        ImGui::Dummy(ImVec2(40.0f, 45.0f));
        ImNodes::EndNode();
        ImNodes::BeginNode(1);
        ImGui::Dummy(ImVec2(80.0f, 45.0f));
        ImNodes::EndNode();

        ImNodes::MiniMap();

        ImNodes::EndNodeEditor();
        ImGui::End();
    }
}

#include "panels.hpp"

bool panels::timing::diagrams::show_window = false;

void panels::timing::diagrams::loop(void)
{
    if (panels::timing::diagrams::show_window)
    {
        ImGui::Begin("Timing Diagrams", &panels::timing::diagrams::show_window);
        ImGui::BulletText("Static Timing Diagram");

        // Static data for the timing diagram
        static ImVector<ImVec2> digitalData1, digitalData2;
        if (digitalData1.empty()) {
            for (float t = 0; t < 10.0f; t += 0.1f) {
                digitalData1.push_back(ImVec2(t, sinf(2 * t) > 0.45)); // signal 1
                digitalData2.push_back(ImVec2(t, sinf(2 * t) < 0.45)); // signal 2
            }
        }

        if (ImPlot::BeginPlot("##Digital"))
        {
            ImPlot::SetupAxisLimits(ImAxis_X1, 0, 10.0, ImGuiCond_Always); // Fixed X-axis range
            ImPlot::SetupAxisLimits(ImAxis_Y1, -1, 1, ImGuiCond_Always);   // Y-axis for binary signals

            // Plot the two digital signals
            ImPlot::PlotDigital("digital_1", &digitalData1[0].x, &digitalData1[0].y, digitalData1.size());
            ImPlot::PlotDigital("digital_2", &digitalData2[0].x, &digitalData2[0].y, digitalData2.size());

            ImPlot::EndPlot();
        }

        ImGui::End();
    }
}

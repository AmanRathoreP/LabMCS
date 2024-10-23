#pragma once

#include <iostream>
#include <imgui.h>
#include <imnodes.h>
#include <implot.h>

namespace panels
{
    namespace timing
    {
        namespace n_editor
        {
            extern bool show_window;
            void loop(void);
        }

        namespace diagrams
        {
            extern bool show_window;
            void loop(void);
        }
    }

}
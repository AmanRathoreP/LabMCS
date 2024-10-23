#pragma once

#include <iostream>
#include <imgui.h>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#define APP_SETTINGS_FILE_NAME_AND_PATH "app_settings.json"

namespace settings
{
    namespace app
    {
        extern bool show_window;
        extern float font_weight;

        void setup(void);
        void loop(void);
        void save_settings(void);
    }

    namespace communication
    {
        extern bool show_window;
        void loop(void);
    }

    namespace io
    {
        extern bool show_window;
        void loop(void);
    }
}

common_files = {
    --imgui stuff
    "$(SolutionDir)/vendor/imgui/imgui.cpp",
    "$(SolutionDir)/vendor/imgui/imgui_demo.cpp",
    "$(SolutionDir)/vendor/imgui/imgui_draw.cpp",
    "$(SolutionDir)/vendor/imgui/imgui_tables.cpp",
    "$(SolutionDir)/vendor/imgui/imgui_widgets.cpp",
    "$(SolutionDir)/vendor/imgui/backends/imgui_impl_sdl2.cpp",
    "$(SolutionDir)/vendor/imgui/backends/imgui_impl_vulkan.cpp",
    "$(SolutionDir)/vendor/imgui/misc/debuggers/imgui.natstepfilter",
    "$(SolutionDir)/vendor/imgui/misc/debuggers/imgui.natvis",
    --implot stuff
    "$(SolutionDir)/vendor/implot/implot.h",
    "$(SolutionDir)/vendor/implot/implot_internal.h",
    "$(SolutionDir)/vendor/implot/implot.cpp",
    "$(SolutionDir)/vendor/implot/implot_items.cpp",
    "$(SolutionDir)/vendor/implot/implot_demo.cpp",
    --imnodes stuff
    "$(SolutionDir)/vendor/imnodes/imnodes.h",
    "$(SolutionDir)/vendor/imnodes/imnodes_internal.h",
    "$(SolutionDir)/vendor/imnodes/imnodes.cpp",
    -- rapidjson stuff
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/allocators.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/cursorstreamwrapper.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/document.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/encodedstream.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/encodings.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/filereadstream.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/filewritestream.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/fwd.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/istreamwrapper.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/memorybuffer.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/memorystream.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/ostreamwrapper.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/pointer.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/prettywriter.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/rapidjson.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/reader.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/schema.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/stream.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/stringbuffer.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/uri.h",
    "$(SolutionDir)/vendor/rapidjson/include/rapidjson/writer.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/biginteger.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/clzll.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/diyfp.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/dtoa.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/ieee754.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/itoa.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/meta.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/pow10.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/regex.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/stack.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/strfunc.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/strtod.h",
    "$(SolutionDir)/vendor/rapidjson/include/internal/swap.h",
    "$(SolutionDir)/vendor/rapidjson/include/error/en.h",
    "$(SolutionDir)/vendor/rapidjson/include/error/error.h",
    --comman files used by solution
    "src/ui/windows/help.hpp",
    "src/ui/windows/about.cpp",
    "src/ui/windows/author.cpp",
    "src/ui/windows/usage.cpp",
    "src/ui/windows/panels.hpp",
    "src/ui/windows/timing_diagrams.cpp",
    "src/ui/windows/timings_n_editor.cpp",
    "src/ui/windows/settings.hpp",
    "src/ui/windows/settings_communication.cpp",
    "src/ui/windows/settings_io.cpp",
    "src/ui/windows/settings_app.cpp",
}

-- Function to concatenate two tables
function concat_table(t1,t2)
    for i=1,#t2 do
        t1[#t1+1] = t2[i]
    end
    return t1
end

-- Define a function to apply common filters
function apply_common_filters(project_name)
    filter {"system:windows", "configurations:*"}
        systemversion "latest"
        targetdir ("bin/" .. project_name .. "/%{cfg.buildcfg}/%{cfg.platform}")
        externalincludedirs {
            "vendor/SDL2Image/include",
            "vendor/imgui",
            "vendor/implot",
            "vendor/imnodes",
            "vendor/rapidjson/include",
            "$(VULKAN_SDK)/Include",
            "$(VULKAN_SDK)/Include/SDL2"
        }
        links {"SDL2", "SDL2main", "SDL2_image", "vulkan-1"}

    filter {"system:windows", "platforms:Win64"}
        architecture "x64"
        objdir ("obj/" .. project_name .. "/%{cfg.buildcfg}/%{cfg.platform}")
        libdirs {"$(VULKAN_SDK)/Lib", "vendor/SDL2Image/lib/x64"}

    filter {"system:windows", "configurations:Debug", "platforms:Win64"}
        defines {"Proj_Win_64_Debug"}
        postbuildcommands {
            "{COPYFILE} \"$(VULKAN_SDK)/Bin/SDL2.dll\" \"$(SolutionDir)bin/" .. project_name .. "/Debug/Win64/SDL2.dll\"",
            "{COPYFILE} \"$(SolutionDir)vendor/SDL2Image/lib/x64/SDL2_image.dll\" \"$(SolutionDir)bin/" .. project_name .. "/Debug/Win64/SDL2_image.dll\"",
            "{COPYDIR} \"$(SolutionDir)res\" \"$(SolutionDir)bin/" .. project_name .. "/Debug/Win64/res\"",
            "{COPYDIR} \"$(SolutionDir)res\" \"$(ProjectDir)/res\""
        }

    filter {"system:windows", "configurations:Release", "platforms:Win64"}
        defines {"Proj_Win_64_Release"}
        postbuildcommands {
            "{COPYFILE} \"$(VULKAN_SDK)/Bin/SDL2.dll\" \"$(SolutionDir)bin/" .. project_name .. "/Release/Win64/SDL2.dll\"",
            "{COPYFILE} \"$(SolutionDir)vendor/SDL2Image/lib/x64/SDL2_image.dll\" \"$(SolutionDir)bin/" .. project_name .. "/Release/Win64/SDL2_image.dll\"",
            "{COPYDIR} \"$(SolutionDir)res\" \"$(SolutionDir)bin/" .. project_name .. "/Release/Win64/res\"",
            "{COPYDIR} \"$(SolutionDir)res\" \"$(ProjectDir)/res\""
        }

    -- Clear filters to reset for next project
    filter {}
end

-- Main Workspace Configuration
workspace "LabMCS"
    configurations {"Debug", "Release"}
    platforms {"Win64"}

-- Single Pendulum Project
project "LabMCS-UI"
    location "./LabMCS/LabMCS-UI"
    targetname "LabMCS"
    --! kind "ConsoleApp"
    kind "WindowedApp"
    systemversion "latest"
    toolset "msc-v143"
    language "C++"
    cppdialect "C++20"

    project_files  = {
        "src/main.cpp",
    }

    -- Appending common files with project files
    files(concat_table(project_files, common_files))

    -- Apply Common Filters
    apply_common_filters("LabMCS-UI")

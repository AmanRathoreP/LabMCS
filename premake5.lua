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
    --comman files used by solution
    "src/ui/windows/about.hpp",
    "src/ui/windows/about.cpp",
    "src/ui/windows/author.hpp",
    "src/ui/windows/author.cpp",
    "src/ui/windows/usage.hpp",
    "src/ui/windows/usage.cpp",
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

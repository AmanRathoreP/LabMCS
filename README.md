<div align="center">
  <h1>LabMCS - Lab Monitoring and Control System</h1>
</div>

<p align="center">
  This is a free open-source desktop app that can be used to control laboratory equipments and monitor them in real time.
</p>


# Features

* Timing Diagrams
* Node Editor
* Real Time analysis
* Uses [premake5](https://premake.github.io/) to generate project files dynamically
* ...

# Platforms

* Windows (64 bit)
* ...

# Quick start

## Pre-Compiled download
Releasing soon

## Self-Build

### Windows(exe)

Follow below steps

* Clone the repository
  ```
  git clone https://github.com/AmanRathoreP/LabMCS.git
  ```
* Getting the required modules
  * Initialising modules
    ```
    git submodule init
    ```
  * Updating modules
    ```
    git submodule update
    ```
* Generating project solution/makefile etc.
  ```
  premake5 vs2022
  ```
  > Note: this will [create solution for Visual Studio 2022](https://premake.github.io/docs/Using-Premake/#using-premake-to-generate-project-files). Use `premake5 --help` to more options
> Note: In [`premake5.lua`](premake5.lua) replace `$(VULKAN_SDK)` with your location of your VulkanSDK.
> * If you are in **windows** just add the path of Vulkan SDK to environment variables with name `VULKAN_SDK`.
# Contributing [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](issues.md)

Thank you for considering contributing to Pendulum Simulation

First note we have a code of conduct, please follow it in all your interactions with the program files.

We welcome any type of contribution, _not only code_. You can help with:
- **QA**: File bug reports, the more details you can give the better (e.g. images or videos)
- **New Features**: You can suggest an modifications or just ask for advancements in the old features of application.
- **Code**: Take a look at the [open issues](issues.md). Even if you can't write the code yourself, you can comment on them, showing that you care about a given issue matters. It helps us to handel them.

# Demo
Will be available soon.

# Author

- [@Aman](https://www.github.com/AmanRathoreP)
   - [GitHub](https://www.github.com/AmanRathoreP)
   - [Telegram](https://t.me/aman0864)
   - Email -> *aman.proj.rel@gmail.com*

# Facts
* This app is initially created to manage some laboratory equipments at Dr. Aviru Kumar Basu's lab, INST Mohali. 

# Credits
* For packages
  * [Omar](https://github.com/ocornut) for [imgui](https://github.com/ocornut/imgui)
  * [Sam Lantinga](https://github.com/slouken) for [SDL2Image](https://github.com/libsdl-org/SDL_image)


# License

[MIT License](https://choosealicense.com/licenses/mit/) | [LICENSE](LICENSE/)

Copyright (c) 2024, Aman Rathore
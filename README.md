Raycaster for the CASIO fx-CG50. It supports simple, 2D-array based worlds with alpha-masked sprites at arbitrary positions.

There is no objective or gameplay loop, just a world you can move about in.

## PrizmSDK
This project uses the [PrizmSDK](https://prizm.cemetech.net/index.php?title=Main_Page)'s build system and a few provided syscalls. You find the source [here](https://github.com/Jonimoose/libfxcg). The C standard library implementation isn't used - I rely mainly on templates and constexpr.

If you want to build this project yourself, download PrizmSDK and drop this project into `(SDK root)/projects/`. Use the build scripts in `(project root)/scripts/` to build (no additional dependencies required).

## WinTestbed
I wrote some interactive tests so that I could debug critical code quickly without leaving Windows using a proper debugger. This is the only bit that uses Visual Studio. The code also depends on wxWidgets, installed through [vcpkg](https://github.com/microsoft/vcpkg). It is cross-platform, but would need a cross-platform build system.
# vscode-vcpkg-template

- For a better package management experience like `npm`, we use `vcpkg` & CMake. vcpkg can also generate Visual Studio project files.
- For a better coding and intelligence experience, we use VSCode. VSCode is also much more faster than Visual Studio.

## Get Started

### Install dependencies

All dependencies should be defined in [`vcpkg.json`](vcpkg.json), for more information, see [the manifest docs](https://github.com/microsoft/vcpkg/blob/master/docs/users/manifests.md).

```bash
git clone --recurse-submodules https://github.com/upupming/vscode-qt-cmake-vcpkg-template.git
.\vcpkg\bootstrap-vcpkg.bat
# install manually (optional, vcpkg can install dependencies automatically when configuring project)
# Note that install manually will got deps in `vcpkg_installed` folder, but cMake will install in `build/vcpkg_installed` folder
# .\vcpkg\vcpkg --feature-flags=manifests,versions install
```

After bootstrapped, You can just run CMake and all dependencies will automatically get installed to `build/vcpkg_installed` folder.

### VSCode Configuration

CMake can find the include directories and supply them to VSCode intelligence. For example, for the `dcmtk` library, we add this in the `CMakeLists.txt`:

```cmake
find_package(dcmtk REQUIRED)
# Add the given directories to those the compiler uses to search for include files.
include_directories(${DCMTK_INCLUDE_DIR})
```

And then in `.vscode/settings.json`, we use CMake tools as the [configuration provider](https://code.visualstudio.com/docs/cpp/faq-cpp#_how-do-i-get-intellisense-to-work-correctly):

```json
"C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
```

This will make VSCode intelligence (`#include <dcmtk...>` and autocomplete) work seamlessly.

### Run the project

1. CMake -> Configure. This will generate Visual Studio project files.
2. CMake -> Build. This will build the `.exe` binary.
3. You can just press `F5` or use the debug button on the left sidebar for debug, the [`launch.json`](./.vscode/launch.json) has been configured correctly. For each run, [CMake Task](./.vscode/tasks.json) will executed before start the built exe.
4. vcpkg will link the lib to exe and copy the DLLs to the exe folder automatically, how easy it is.

## Todo

- GitHub Actions for auto build

## Useful information

1. https://github.com/microsoft/vcpkg
2. https://vcpkg.info/
3. https://vcpkgx.com/
4. https://github.com/microsoft/STL
5. https://github.com/miredirex/cmake-vcpkg-example/
6. https://github.com/microsoft/vcpkg/blob/master/docs/users/manifests.md
7. https://www.youtube.com/watch?v=iZeK3Ie5Fz0
8. https://cliutils.gitlab.io/modern-cmake/

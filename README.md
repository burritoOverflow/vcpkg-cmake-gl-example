### GLFW GLAD CMake Example w/ vcpkg

Uses [vcpkg package manager](https://vcpkg.io/en/) for retrieving [GLAD](https://github.com/Dav1dde/glad) and [GLFW](https://github.com/glfw/glfw)

`vcpkg` is retrieved as a submodule (does not require a local installation):

```bash
git submodule update --init
```

Set up `vcpkg`

```bash
./vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

The previous steps are provided via `bootstrap.sh`.

Use the preset for configuration:

```bash
cmake --preset  "vcpkg Default Debug - Ninja"
```

Build the executable:

```bash
cmake --build build/default
```

Executable is in `./build/default/bin/OGLvcpkgExample`

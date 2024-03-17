### GLFW GLAD CMake Example w/ vcpkg

Uses [vcpkg package manager](https://vcpkg.io/en/) for retrieving [GLAD](https://github.com/Dav1dde/glad) and [GLFW](https://github.com/glfw/glfw)

Requires `VCPKG_ROOT` to be set to the path of your `vcpkg` installation, as the configration requires the toolchain file.

configuring (requires `ninja`, as the name indicates):

```bash
 cmake --preset "vcpkg Default - Ninja"
```

build dir is set to `default`, i.e:

```bash
cmake --build build/default
```

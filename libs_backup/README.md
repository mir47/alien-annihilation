# Setup libraries on Windows with Visual Studio

Built with:

- Microsoft Visual Studio Community 2022
- SDL2-2.28.5 ([SDL](https://www.libsdl.org) and [repo](https://github.com/libsdl-org/SDL))
- SDL_gfxPrimitives-1.5

Steps to setup project: [Setting up SDL 2 on Visual Studio](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php)

[Tutorial on Game Programming with SDL](https://lazyfoo.net/tutorials/SDL)

[SDL 1 to 2 Migration Guide](https://wiki.libsdl.org/SDL2/MigrationGuide#Overview_of_new_features)

[SDL release archive](https://www.libsdl.org/release)

## Libraries

Folder `downloads`:

### SDL

- `SDL2-devel-2.28.5-VC.zip` 
- folders `include` and `lib` are dependencies for project.
- `include` has header files - `Include directories`
- `lib` has `SDL2.lib` and `SDL2main.lib` - `Library directories`
- `lib` has `SDL2.dll` - used at runtime, copy paste into project folder `alien-annihilation/alien-annihilation`, and not in top level solution folder `alien-annihilation`.

### TTF

- `SDL2_ttf-devel-2.20.2-VC.zip`

### GFX 

- `SDL2_gfx-1.0.4.gz`
- `SDL2_gfx-1.0.4` is the .gz file, with solution opened and built in Visual Studio, for 32 bit (`x86`). The important build outputs (`SDL2_gfx.lib` and `SDL2_gfx.dll`) are contained in folder `/Win32/Debug`

Folder `vclib`:

- Just the important files copied from the downloads folder. Can copy this to anywhere e.g. `C:\vclib`, and needs to be referenced in the project dependencies.

Notes:

- Set project configuration to `x86` (32 bit), and configure depencies on `x86` libs. I could only get `SDL2_gfx` to build for `x86` and not `x64`.

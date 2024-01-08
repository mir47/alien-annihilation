# Setup on Windows

## Basic Setup

- Install Microsoft Visual Studio Community 2022.
- Open solution file and set build configuration to `x86` (32 bit), and configure depencies on `x86` libs (next step). I could only get `SDL2_gfx` to build for `x86` and not `x64`.
- `vclib.zip` contains just the necessary library files copied from the `source` folder. This is needed to build the `alien-annihilation` project. Extract and copy this to anywhere e.g. `C:\vclib`, and configure the project settings in Visual Studio (see [Setting up SDL 2 on Visual Studio](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php) for more info).
- To run the executable, copy the `.dll` files to the same folder as the `.exe` e.g. `alien-annihilation/Debug`, but these should already be there. If it doesn't work, try put them in the project folder `alien-annihilation/alien-annihilation` next to the source files. If still doesn't work, then ask Google or ChatGPT.

## Source

See `source` folder. These are generally available to download from the internet. They are here as a backup (just in case).

- SDL
  - info: [SDL](https://www.libsdl.org) and [repo](https://github.com/libsdl-org/SDL)
  - source: `SDL2-devel-2.28.5-VC.zip` 
  - folders `include` and `lib` contain the dependencies needed for building the `alien-annihilation` project.
  - folder `include` has header files for `Include directories`
  - folder `lib` has binary files (`SDL2.lib` and `SDL2main.lib`) for `Library directories`
  - folder `lib` also has `SDL2.dll` for runtime. Copy paste this dll into project folder `alien-annihilation/alien-annihilation`, and not in top level solution folder `alien-annihilation`.

- TTF
  - source: `SDL2_ttf-devel-2.20.2-VC.zip`
  - similar structure to SDL folder

- GFX 
  - source: `SDL2_gfx-1.0.4.gz` - original SDL2 GFX library.
  - `SDL2_gfx-1.0.4-build-x86.zip` - extracted SDL2 GFX library (.gz file), with solution built in Visual Studio, for 32-bit (`x86`) config. The outputs from the build are in the folder `/Win32/Debug`, most importantly `SDL2_gfx.lib` and `SDL2_gfx.dll`. The zip file has been manually renamed with `-build-x86` suffix (just as a label), so if extracting to rerun the build, the main folder `SDL2_gfx-1.0.4-build-x86` might need to be renamed to the original `SDL2_gfx-1.0.4`, but this is unconfirmed and untested.

## More info:

- [Setting up SDL 2 on Visual Studio](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php)
- [Tutorial on Game Programming with SDL](https://lazyfoo.net/tutorials/SDL)
- [SDL 1 to 2 Migration Guide](https://wiki.libsdl.org/SDL2/MigrationGuide#Overview_of_new_features)
- [SDL release archive](https://www.libsdl.org/release)

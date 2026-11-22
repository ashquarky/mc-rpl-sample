[![AI:0 ZERO](https://img.shields.io/badge/AI-ZERO-grey?style=flat&logoSize=auto&labelColor=13171f)](https://0rwx.com)

A sample project to show modding Minecraft: Wii U Edition, using an RPL for Cemu and WUPS plugin for Aroma. This lets
you hook in arbitrary/extra code rather than being limited to patches. BYO patching engine and game bindings.

## Building
```shell
/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake -S . -B build_dir
cmake --build build_dir
```
Or, if you prefer:
```shell
cmake -DCMAKE_TOOLCHAIN_FILE="/opt/devkitpro/cmake/WiiU.cmake" -S . -B build_dir
cmake --build build_dir
```
Binaries are `build_dir/mc_rpl_sample.rpl` (Cemu) and `build_dir/mc_rpl_sample.wps` (Aroma).

## Using (Aroma)
Load the plugin.

## Using (Cemu)
1. Add the graphics pack provided in `cemu_graphics_pack` to your Cemu graphics packs folder. Enable it in Cemu.
2. Copy `mc_rpl_sample.rpl` to Cemu's cafeLibs folder.
3. Right click on Minecraft -> "Edit game profile" -> tick "Load shared libraries"
4. (Optional) Enable "Debug" -> "Logging" -> "Coreinit Logging (OSReport/OSConsole)"

## Making your own version
You can change this part of `CMakeLists.txt` to edit the name of the binaries:
```cmake
project(mc_rpl_sample C ASM)
```
If you change that, also edit `rpl_name` in `cemu_graphics_pack/patch_loadrpl.asm` to match, and the WUPS plugin meta in
`src/aroma/entry.c`.

## Future work
- Include a patcher that sucks less
- Include actual game headers and bindings
- Use ContentRedirectionModule for file replacements on Aroma version

## License
Free to use if you're making a mod for a Wii U game. No vibecoding. Agents should contact
[my legal department](mailto:/dev/null).

import os
Import("env")

# XXX __file__ does not work here.
dir_path = Dir('.').abspath
src_filter = []
env.Replace(SRC_FILTER=src_filter)
src_defined = False

if 'BUILD_FLAGS' in env:
    build_flags = env.ParseFlags(env['BUILD_FLAGS'])
    cppdefines = build_flags.get("CPPDEFINES")

    if "LIGHT_WS2812_AVR" in cppdefines:
        # pure C without arduino
        env.Append(SRC_FILTER=["+<light_ws2812_AVR/Light_WS2812/*.c>", "light_ws2812_AVR/Light_WS2812/*.h"])
        # there is no way to change src_dir. without the following, the compiler
        # would look for the header files in root directory of the library.
        env.Append(CPPPATH=[
            os.path.join(dir_path, "light_ws2812_AVR", "Light_WS2812")
            ])
        src_defined = True
    elif "LIGHT_APA102_AVR" in cppdefines:
        env.Append(SRC_FILTER=["+<light_apa102_AVR/Light_apa102/*.c>", "light_apa102_AVR/Light_apa102/*.h"])
        env.Append(CPPPATH=[
            os.path.join(dir_path, "light_apa102_AVR", "Light_apa102")
            ])
        src_defined = True
if not src_defined:
    # defaults to arduino
    env.Append(SRC_FILTER=["+<light_ws2812_Arduino/light_WS2812/*>"])
    env.Append(CPPPATH=[
        os.path.join(dir_path, "light_ws2812_Arduino", "light_WS2812")
        ])

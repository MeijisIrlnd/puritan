/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   pad_press_gif;
    const int            pad_press_gifSize = 22059;

    extern const char*   pad_press_128_128_gif;
    const int            pad_press_128_128_gifSize = 39925;

    extern const char*   pad_press_512_512_gif;
    const int            pad_press_512_512_gifSize = 154940;

    extern const char*   ScanLine_gif;
    const int            ScanLine_gifSize = 5319;

    extern const char*   PixelTandysoft0rJG_ttf;
    const int            PixelTandysoft0rJG_ttfSize = 23996;

    extern const char*   MixerHandle_png;
    const int            MixerHandle_pngSize = 2512;

    extern const char*   RotaryHandle_png;
    const int            RotaryHandle_pngSize = 1147;

    extern const char*   puritan_pad_png;
    const int            puritan_pad_pngSize = 7635;

    extern const char*   puritan_pad32_32_png;
    const int            puritan_pad32_32_pngSize = 194;

    extern const char*   drinkLove_gif;
    const int            drinkLove_gifSize = 362644;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 10;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}

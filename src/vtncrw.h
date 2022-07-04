#pragma once
#include "vector"

// WARNING: THIS REWRITE DOES NOT WORK CURRENTLY SO IT WILL CAUSE A LOT OF COMPILE ERRORS.

namespace VTNCRW
{
    // Rescalable Data
    // Basically, it is intendended to be a custom datatype that it's bit size is changeable.
    class rescData
    {
    public:
        // The last bit index of the last byte
        int lastBitIndex;
        unsigned char *data;
        unsigned int bitSize;
        unsigned char *toChar();
        rescData(unsigned int bitsize = 8, unsigned int initialsize = 1);
        ~rescData();
        rescData operator+(rescData b);
    };

    struct Frame
    {
        // The index of the colors inside the ColorBuffer. It is used as a way to not repeat the same 4 bytes for every pixel color.
        rescData Pixels;
        rescData msDuration;
    };

    struct Resolution
    {
        rescData x;
        rescData y;
    };

    struct RGBA
    {
        unsigned char R;
        unsigned char G;
        unsigned char B;
        unsigned char A;
    };

    //"Group" is a generic name for how it is intended to work, as each group can work differently depending of the context.
    // It can be used as a "layer" category or even as a way to separate multiple images in only one file.
    struct Group
    {
        Resolution resolution;

        // An array of frames.
        Frame *frames;

        // A set of numbers that is interpreted by some software in the way the developers intended.
        // Works as a key.
        unsigned char modifiers;
    };
    struct Internals
    {
        unsigned char TAGNeeded[6] = "VTNCI";
    };

    class VTNCFile
    {
    public:
        RGBA *ColorBuffer;
        Group *GroupList;
        VTNCFile();
    };
    VTNCFile create(Group *GroupList);
    VTNCFile read(std::vector<unsigned char> file);
    std::vector<unsigned char> write(VTNCFile file);
} // namespace VTNCRW
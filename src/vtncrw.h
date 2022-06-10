#pragma once
#include "vector"

//WARNING: THIS REWRITE DOES NOT WORK CURRENTLY SO IT WILL CAUSE A LOT OF COMPILE ERRORS.


//NEED SOME CREATIVE NAME HERE, THE PRESENT ONE IS NOT GOOD AT ALL
//Basically, it is intendended to be a custom datatype that it's bit size is changeable.
class resizeable
{
public:
    bool* data;
    unsigned int size;
    unsigned char* toChar();
    resizeable(/* args */);
    ~resizeable();
};

struct Frame {
    //The index of the colors inside the ColorBuffer. It is used as a way to not repeat the same 4 bytes for every pixel color.
    resizeable Pixels;
    resizeable msDuration;
};


struct Resolution{
    resizeable x;
    resizeable y;
};


struct RGBA{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};


//"Group" is a generic name for how it is intended work, as each group can work differently depending of the context.
//It can be used as a "layer" category or even as a way to separate multiple images in only one file.
struct Group{
    Resolution resolution;

    //An array of frames.
    Frame* frames;

    //A set of numbers that is interpreted by some software in the way the developers intended.
    //Works as a key.
    unsigned char modifiers;
};

class VTNCFile
{
public:
    RGBA *ColorBuffer;
    Group *GroupList;
};

class VTNCRW
{
private:
    unsigned char TAGNeeded [6] = "VTNCI";
public:
    VTNCRW();
    VTNCFile create(unsigned char layerQuantity, Resolution EachLayerResolution[], unsigned char ColorsQuantity, unsigned char EndsAnimationAt);
    VTNCFile read(std::vector<unsigned char> file);
    std::vector<unsigned char> write(VTNCFile file);
};
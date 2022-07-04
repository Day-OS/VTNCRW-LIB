#include "vtncrw.h"
#include <cstring>
#include "iostream"
#include "bitset"

VTNCRW::VTNCFile::VTNCFile()
{
}


namespace VTNCRW
{
    rescData::rescData(unsigned int bitsize, unsigned int initialsize)
    {
        this->data = (unsigned char*) calloc (initialsize, sizeof(unsigned char));
        this->bitSize = bitsize;
    }

    rescData::~rescData()
    {
        
    }
    
    
    rescData rescData::operator+(rescData b)
    {
        rescData result = *this;
        std::cout << "BINARY DATA: " << std::hex << *reinterpret_cast<std::bitset<8*4>*>(data) << std::endl;
        std::cout<< strlen(reinterpret_cast<const char*>(data));
        //result.data = (unsigned char *) 
        //reinterpret_cast<std::bitset<8>*>( data[ strlen(reinterpret_cast<const char*>(data)) ]
        //    )
        // + 4;
        //std::cout << "sus";


        
        std::cout << "BINARY DATA AFTER: " << std::hex << *reinterpret_cast<std::bitset<8*4>*>(result.data) << std::endl;
        //std::cout << std::endl << "length: " << strlen(reinterpret_cast<const char*>(b.data)) << std::endl;
        return result;
    }
}


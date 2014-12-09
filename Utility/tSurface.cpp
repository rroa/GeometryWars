#include "package.hpp"
#include "stb_image.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tSurface& tSurface::operator=(const tSurface& origSurface)
{
    if (this != &origSurface)
    {
        delete [] mPtr;

        mSize           = origSurface.mSize;
        mBytesPerRow    = origSurface.mBytesPerRow;

        mPtr = new uint8_t[(int32_t)(origSurface.mSize.height * mBytesPerRow)];

        assert(mPtr);

        memcpy(mPtr, origSurface.mPtr, (size_t)(origSurface.mSize.height * mBytesPerRow));
    }

    return *this;
}

tSurface::tSurface(const std::string& filename)
: mSize(0,0), mPtr(NULL)
{
    //---------------------------------------------------------------------------------
    // RR: Changed iOS specific implementation for image loading.
    //---------------------------------------------------------------------------------

    // Load the texture at szPath, puts it into an OpenGL texture, and returns
    // the ID of the texture. ( RGBA in byte order ).
    int nChannels;
    int width;
    int height;

    // nChannels will actually have the amount of bytes of the loaded image
    // Assuming all images are 4 bytes
    unsigned char *pixels = stbi_load( filename.c_str(), &width, &height, &nChannels, 4 );
    
    if( !pixels )
    {
        assert( pixels );
    } 

     // Get Image size
    mSize.width     = (int32_t) width;
    mSize.height    = (int32_t) height;
    mBytesPerRow    = uint16_t(4 * mSize.width);

    //  We have to copy that raw data one row at a time….yay
    mPtr = new uint8_t[(int32_t)(mSize.height * mBytesPerRow)];

    memcpy( mPtr, pixels, size_t( mSize.height * mBytesPerRow ));

    // Free Stuff
    //
    stbi_image_free( pixels );    

    assert((mSize.width != 0) && (mSize.height != 0) && (mPtr));
}

//TODO: This might be okay, I dunno?!
tSurface::tSurface(const tDimension2f& newSize)
: mSize(newSize)
{
    assert(newSize.width > 0 && newSize.height > 0);

    mBytesPerRow = uint16_t(4 * newSize.width);
    if ((mBytesPerRow & 0x3) != 0)
    {
        mBytesPerRow = (mBytesPerRow & ~0x3) + 4;
    }
    
    mPtr = new uint8_t[(int32_t)(newSize.height * mBytesPerRow)];
    
    assert(mPtr);
}

tSurface::tSurface(const tSurface& origSurface)
: mSize(origSurface.mSize), mBytesPerRow(origSurface.mBytesPerRow)
{
    mPtr = new uint8_t[(int32_t)(origSurface.mSize.height * mBytesPerRow)];

    assert(mPtr);
    
    memcpy(mPtr, origSurface.mPtr, (size_t)(origSurface.mSize.height * mBytesPerRow));
}

tSurface::~tSurface()
{
    if (mPtr)
    {
        delete[] mPtr;
    }
}

tDimension2f tSurface::getSize() const
{
    return mSize;
}


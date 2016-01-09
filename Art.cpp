#include "Art.hpp"

#include "Utility/package.hpp"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

Art::Art()
{
    // TODO: RR: Create utility class to generate these strings.
    //

    #if EMSCRIPTEN
        const std::string resourcesPath = "";
    #else
        const std::string resourcesPath = "./Resources/Sprites/";
    #endif
    mPlayer         = new tTexture(tSurface(std::string(resourcesPath + "player.png")));
    mSeeker         = new tTexture(tSurface(std::string(resourcesPath + "seeker.png")));
    mWanderer       = new tTexture(tSurface(std::string(resourcesPath + "wanderer.png")));
    mBullet         = new tTexture(tSurface(std::string(resourcesPath + "bullet.png")));
    mPointer        = new tTexture(tSurface(std::string(resourcesPath + "pointer.png")));
    mBlackHole      = new tTexture(tSurface(std::string(resourcesPath + "blackhole.png")));

    mFontTexture    = new tTexture(tSurface(std::string(resourcesPath + "font.png")));

    mVPadTop        = new tTexture(tSurface(std::string(resourcesPath + "vpad_top.png")));
    mVPadBottom     = new tTexture(tSurface(std::string(resourcesPath + "vpad_bot.png")));

    mLineParticle   = new tTexture(tSurface(std::string(resourcesPath + "laser.png")));
    mGlow           = new tTexture(tSurface(std::string(resourcesPath + "glow.png")));

	mPixel          = new tTexture(tSurface(std::string(resourcesPath + "pixel.png")));
}

tTexture* Art::getPlayer() const
{
    return mPlayer;
}

tTexture* Art::getSeeker() const
{
    return mSeeker;
}

tTexture* Art::getWanderer() const
{
    return mWanderer;
}

tTexture* Art::getBullet() const
{
    return mBullet;
}

tTexture* Art::getPointer() const
{
    return mPointer;
}

tTexture* Art::getBlackHole() const
{
    return mBlackHole;
}

tTexture* Art::getLineParticle() const
{
    return mLineParticle;
}

tTexture* Art::getGlow() const
{
    return mGlow;
}

tTexture* Art::getPixel() const
{
    return mPixel;
}

tTexture* Art::getVPadBottom() const
{
    return mVPadBottom;
}

tTexture* Art::getVPadTop() const
{
    return mVPadTop;
}

tSpriteFont Art::getFont() const
{
    return tSpriteFont( mFontTexture, tTextSheet(tRectf( 0, 0, 256,  36), tDimension2f( 8, 12), tDimension2f( 6, 10 ), ' ', '~' ));
}

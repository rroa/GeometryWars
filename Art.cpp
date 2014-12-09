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
    std::string resourcesPath = "/home/raulroa/Code/projects/Geometry/Resources/Sprites/";

    mPlayer         = new tTexture(tSurface(std::string(resourcesPath + "player.png")));
    mSeeker         = new tTexture(tSurface(std::string(resourcesPath + "seeker.png")));
    mWanderer       = new tTexture(tSurface(std::string(resourcesPath + "wanderer.png")));
    mBullet         = new tTexture(tSurface(std::string(resourcesPath + "bullet.png")));
    mPointer        = new tTexture(tSurface(std::string(resourcesPath + "pointer.png")));
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
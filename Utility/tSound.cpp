#include "package.hpp"
#include <algorithm>
#include <iostream>

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

uint8_t              tSound::mAvailable   = 0;
std::list<tSound*>   tSound::mPausedSounds;
std::list<tSound*>   tSound::mAllSounds;
bool                 tSound::mPaused      = false;

void tSound::RegisterSound(tSound* newSound)
{
    if (tSound::mAvailable != 0)
    {
        assert(newSound);
        assert(std::find(mAllSounds.begin(), mAllSounds.end(), newSound) == mAllSounds.end());

        mAllSounds.push_back(newSound);
    }
}

void tSound::UnregisterSound(tSound* newSound)
{
    if (tSound::mAvailable != 0)
    {
        assert(newSound);
        assert(find(mAllSounds.begin(), mAllSounds.end(), newSound) != mAllSounds.end());

        mAllSounds.remove(newSound);
        mPausedSounds.remove(newSound);
    }
}

void tSound::OnSuspend()
{
    std::list<tSound*>::iterator iter;

    for(iter = mAllSounds.begin(); iter != mAllSounds.end(); iter++)
    {
        if ((*iter)->isPlaying())
        {
            (*iter)->pause();

            mPausedSounds.push_back(*iter);
        }
    }
}

void tSound::OnResume()
{
    std::list<tSound*>::iterator iter;

    for(iter = mPausedSounds.begin(); iter != mPausedSounds.end(); iter++)
    {
        if ((*iter)->isPaused())
        {
            (*iter)->resume();
        }
    }

    mPausedSounds.clear();
}

tSound::tSound(const std::string& filename)
        :   m_chunk(0),
            m_channelId(-1),
            mIsPlaying(false),
            mIsPaused(false)
{
    tSound::mAvailable++;
    RegisterSound(this);

    m_chunk = Mix_LoadWAV(filename.c_str());

    assert(m_chunk);
}

tSound::~tSound()
{
    stop();

    assert(m_chunk);

    delete m_chunk;

    UnregisterSound(this);

    if (tSound::mAvailable)
    {
        tSound::mAvailable--;
    }
}

bool    tSound::isPlaying()
{
    return mIsPlaying;
}

bool    tSound::isPaused()
{
    return mIsPaused;
}

bool   tSound::play(float startTimeMS, uint32_t nloops)
{
    if (!mIsPlaying && !mIsPaused)
    {
        assert(m_chunk);

        m_channelId = Mix_PlayChannel(-1, m_chunk, 0);
        mIsPlaying = (m_channelId != -1 );
        std::cout << m_channelId << std::endl;
        return mIsPlaying;
    }

    return false;
}
void    tSound::pause()
{
    if (mIsPlaying && !mIsPaused)
    {
        assert(m_chunk);

        Mix_Pause(m_channelId);

        mIsPaused = true;
    }
}

bool   tSound::resume()
{
    if (mIsPlaying && mIsPaused)
    {
        assert(m_chunk);

        mIsPaused = false;

        Mix_Resume(m_channelId);

        return mIsPlaying;
    }

    return false;
}

void    tSound::stop()
{
    if (mIsPlaying)
    {
        assert(m_chunk);

        mIsPlaying    = false;
        mIsPaused     = false;

        Mix_HaltChannel(m_channelId);
    }
}

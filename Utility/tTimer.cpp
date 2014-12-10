#include <sys/time.h>

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

#include "package.hpp"

uint32_t tTimer::getTimeMS()
{
    struct timeval tm;
    gettimeofday( &tm, NULL );
    return (uint32_t)((tm.tv_sec + (uint32_t)tm.tv_usec / 1000000.0) * 0.001);
}

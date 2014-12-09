// Space Combat
#include "TimeManager.hpp"

// STL
//
#include <cstdlib>

namespace Geometry
{
    TimeManager::TimeManager()
    {
#ifdef WIN32
        ::QueryPerformanceFrequency( &frequency );
        m_startCount.QuadPart   = 0;
        m_endCount.QuadPart     = 0;
#else
        m_startCount.tv_sec     = m_startCount.tv_usec = 0;
        m_endCount.tv_sec       = m_endCount.tv_usec = 0;
#endif
        m_stopped = 0;
        m_startTimeInMicroSeconds = 0;
        m_endTimeInMicroSeconds = 0;
    }

    TimeManager::~TimeManager()
    {}

    void TimeManager::Start( )
    {
        m_stopped = 0; // reset stop flag
#ifdef WIN32
        ::QueryPerformanceCounter( &m_startCount );
#else
        gettimeofday( &m_startCount, NULL );
#endif       
    }

    void TimeManager::Stop( )
    {
        m_stopped = 1; // set timer stopped flag
#ifdef WIN32
        ::QueryPerformanceCounter( &m_endCount );
#else
        gettimeofday( &m_endCount, NULL );
#endif
    }

    double TimeManager::GetElapsedTimeInMicroseconds( )
    {
#ifdef WIN32
        if( !m_stopped )
        {
            ::QueryPerformanceCounter( &m_endCount );
        }

        m_startTimeInMicroSec = m_startCount.QuadPart * ( 1000000.0 / m_frequency.QuadPart );
        m_endTimeInMicroSec   = m_endCount.QuadPart * ( 1000000.0 / m_frequency.QuadPart );
#else
        if(!m_stopped)
        {
            gettimeofday( &m_endCount, NULL );
        }            

        m_startTimeInMicroSeconds   = ( m_startCount.tv_sec * 1000000.0 ) + m_startCount.tv_usec;
        m_endTimeInMicroSeconds     = ( m_endCount.tv_sec * 1000000.0 ) + m_endCount.tv_usec;
#endif

        return m_endTimeInMicroSeconds - m_startTimeInMicroSeconds;
    }

    double TimeManager::GetElapsedTimeInMilliseconds( )
    {
        return this->GetElapsedTimeInMicroseconds( ) * 0.001;
    }

    double TimeManager::GetElapsedTimeInSeconds( )
    {
        return this->GetElapsedTimeInMicroseconds( ) * 0.000001;
    }

    double TimeManager::GetElapsedTime( )
    {
        return this->GetElapsedTimeInSeconds( );
    }
}
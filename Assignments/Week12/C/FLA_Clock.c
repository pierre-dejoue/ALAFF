#if defined(__APPLE__) || defined(__MACH__)
  #include <AvailabilityMacros.h>
  #include <mach/mach_time.h>
#else
#ifdef _MSC_VER
  // Windows
  #include <Windows.h>
#else
  // Linux
  #include <time.h>
#endif
#endif

double FLA_Clock_helper( void );

// A global variable used when FLA_Clock_helper() is defined in terms of
// clock_gettime()/gettimeofday().
double gtod_ref_time_sec = 0.0;

double FLA_Clock( void )
{
	return FLA_Clock_helper();
}

#ifdef _MSC_VER
struct timespec {
    long tv_sec;
    long tv_nsec;
};
#endif

#if defined(__APPLE__) || defined(__MACH__)

double FLA_Clock_helper()
{
    mach_timebase_info_data_t timebase;
    mach_timebase_info(&timebase);

    uint64_t nsec = mach_absolute_time();

    double the_time = (double)nsec * 1.0e-9 * timebase.numer / timebase.denom;

    if (gtod_ref_time_sec == 0.0)
        gtod_ref_time_sec = the_time;

    return the_time - gtod_ref_time_sec;
}

#else

double FLA_Clock_helper()
{
    double the_time, norm_sec;
    struct timespec ts;

#ifdef _MSC_VER
    // Based on https://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows
    __int64 wintime;
    GetSystemTimePreciseAsFileTime((FILETIME*)&wintime);
    wintime -= 116444736000000000i64;             // 1jan1601 to 1jan1970
    ts.tv_sec = wintime / 10000000i64;            // seconds
    ts.tv_nsec = (wintime % 10000000i64) * 100;   // nano-seconds
#else
    clock_gettime( CLOCK_MONOTONIC, &ts );
#endif

    if (gtod_ref_time_sec == 0.0)
        gtod_ref_time_sec = (double)ts.tv_sec;

    norm_sec = (double)ts.tv_sec - gtod_ref_time_sec;

    the_time = norm_sec + (double)ts.tv_nsec * 1.0e-9;
    return the_time;
}

#endif


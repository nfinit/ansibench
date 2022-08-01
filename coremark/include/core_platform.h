/*
ANSIbench platform-specific definitions for CoreMark
*/

#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

/* Linux
 * - USE_CLOCK=1 causes multithreaded runs under ARM Linux to not account for
 *   all cores and thus only show single-threaded rates 
 */
#if defined(linux) || defined (LINUX) || \
    defined(__linux) || defined (__LINUX) || \
    defined(__linux__) || defined (__LINUX__) || \
    defined (__gnu_linux__) || defined (__GNU_LINUX__)
  #define USE_CLOCK 0
#endif

/* AIX
 * ANSIbench has only been tested with one system running AIX 4.3
 */
#ifdef _AIX
#endif

#endif /* CORE_PLATFORM_H */

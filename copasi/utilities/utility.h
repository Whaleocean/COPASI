#ifndef COPASI_utilities
#define COPASI_utilities

#include <string>
#include <stdio.h>
#include <stdarg.h>

using std::string;

#define INITIALTEXTSIZE 1024

/**
 *  sprintf like function for strings
 *  @param "const char *" format sprintf like format string
 *  @param ...
 *  @return "string" 
 */
string StringPrint(const char * format, ...);

/**
 *
 */
void dgefa(C_FLOAT64 ** a,
           C_INT32 n,
           C_INT32 * ipvt,
           C_INT32 * info);

/**
 *  Returns index of the componen the maximum of the absolute values of 
 *  the components of the vector dx. The vector dx is incremented (n-1) 
 *  times by the incx.
 *  @param "C_INT32" n number of elements in the vector dx
 *  @param "C_FLOAT64 *" dx (fortran style vector)
 *  @param "C_INT32" incx increment stepsize
 *  @return "C_INT32" index of the component with maximum of absolute values
 */
C_INT32 idamax(C_INT32 n,
               C_FLOAT64 * dx,
               C_INT32 incx);

/**
 *  Returns the maximum of the absolute values of the components of 
 *  the vector dx. The vector dx is incremented (n-1) times by the incx.
 *  @param "C_INT32" n number of elements in the vector dx
 *  @param "C_FLOAT64 *" dx (fortran style vector)
 *  @param "C_INT32" incx increment stepsize
 *  @return "C_FLOAT64" maximum of absolute values
 */
C_FLOAT64 xNorm(C_INT32 n,
                C_FLOAT64 * dx,
                C_INT32 incx);

/**
 *
 */
void dgesl(C_FLOAT64 ** a,
           C_INT32 n,
           C_INT32 * ipvt,
           C_FLOAT64 * b,
           C_INT32 job);

/**
 *
 */
void daxpy(C_INT32 n,
           C_FLOAT64 da,
           C_FLOAT64 * dx,
           C_INT32 incx,
           C_FLOAT64 * dy,
           C_INT32 incy);

#ifdef XXXX 
/**
 *
 */
void lsoda_dscal(C_INT32 n,
                 C_FLOAT64 da,
                 C_FLOAT64 * dx,
                 C_INT32 incx);
#endif // XXXX

/**
 *
 */
C_FLOAT64 ddot(C_INT32 n,
               C_FLOAT64 * dx,
               C_INT32 incx,
               C_FLOAT64 * dy,
               C_INT32 incy);

#endif // COPASI_utilities

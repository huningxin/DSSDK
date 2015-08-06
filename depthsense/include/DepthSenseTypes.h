////////////////////////////////////////////////////////////////////////////////
// SoftKinetic DepthSense SDK
//
// COPYRIGHT AND CONFIDENTIALITY NOTICE - SOFTKINETIC CONFIDENTIAL
// INFORMATION
//
// All rights reserved to SOFTKINETIC SENSORS NV (a
// company incorporated and existing under the laws of Belgium, with
// its principal place of business at Boulevard de la Plainelaan 15,
// 1050 Brussels (Belgium), registered with the Crossroads bank for
// enterprises under company number 0811 341 454 - "Softkinetic
// Sensors").
//
// The source code of the SoftKinetic DepthSense Camera Drivers is
// proprietary and confidential information of Softkinetic Sensors NV.
//
// For any question about terms and conditions, please contact:
// info@softkinetic.com Copyright (c) 2002-2015 Softkinetic Sensors NV
////////////////////////////////////////////////////////////////////////////////


#ifndef _DEPTHSENSETYPES_H
#define	_DEPTHSENSETYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER

typedef signed   __int8   int8_t;
typedef signed   __int16  int16_t;
typedef signed   __int32  int32_t;
typedef signed   __int64  int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;

# define PRId64         "I64d"
# define PRIi64         "I64i"
# define PRIu64         "I64u"
# define PRIx64         "I64x"

# ifdef _WIN64
#  define INT64_C(c)	c ## L
#  define UINT64_C(c)	c ## UL
# else
#  define INT64_C(c)	c ## LL
#  define UINT64_C(c)	c ## ULL
# endif

#define SK_NO_RETURN __declspec(noreturn)
#define SK_MAY_ALIAS

#else
// Warning: this will break if <stdint.h> has already been included from elsewhere
// without __STDC_CONSTANT_MACROS and __STDC_FORMAT_MACROS defined in the first place.
#ifndef __STDC_CONSTANT_MACROS
# define __STDC_CONSTANT_MACROS // for UINT64_C(c) and friends
#endif
#ifndef __STDC_FORMAT_MACROS
# define __STDC_FORMAT_MACROS // for PRIi64 and friends
#endif
#include <stdint.h>
#include <inttypes.h>

#define SK_NO_RETURN __attribute__ ((noreturn))
#define SK_MAY_ALIAS __attribute__ ((__may_alias__))

#endif /* _MSC_VER */

// detect std::hash availability:
//
//   - gcc defines the __GXX_EXPERIMENTAL_CXX0X__ symbol when C++11
//     support is available, see
//
//     http://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html#status.iso.200x
//   - Visual Studio 2010 and later versions support std::hash
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (_MSC_VER >= 1600)
#define __DS_HAVE_STD_HASH
#endif

#ifdef __cplusplus
}
#endif

#endif	/* _DEPTHSENSETYPES_H */

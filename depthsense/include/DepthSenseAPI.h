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


#ifndef _DEPTHSENSEAPI_H
#define	_DEPTHSENSEAPI_H


/*----------------------------------------------------------------------------*/
#if defined(DepthSense_EXPORTS)
#
#  if defined(_MSC_VER)
#    define DEPTHSENSE_API  __declspec(dllexport)
#  elif defined(__GNUC__)
#    define DEPTHSENSE_API  __attribute__((visibility("default")))
#  else
#    error Unsupported compiler
#  endif /* _MSC_VER || __GNUC__ */
#
#elif defined(DepthSense_STATIC)
#
#    define DEPTHSENSE_API
#
#else /* !DepthSense_EXPORTS && !DepthSense_STATIC */
#
#  if defined(_MSC_VER)
#    define DEPTHSENSE_API  __declspec(dllimport)
#  elif defined(__GNUC__)
#    define DEPTHSENSE_API  __attribute__((visibility("default")))
#  else
#    error Unsupported compiler
#  endif /* _MSC_VER || __GNUC__ */
#
#endif /* DepthSense_EXPORTS */


/*----------------------------------------------------------------------------*/
// Helper macros for private data access in API classes

#define DEPTHSENSE_PRIVATE_DECLARE(C) \
private: \
    class C##Private; \
    friend class C##Private; \
    inline C##Private &get_priv() { return *priv; } \
    inline const C##Private &get_priv() const { return *((const C##Private *) priv); } \
    C##Private *priv

#define DEPTHSENSE_PRIVATE_BEGIN(C) \
class C::C##Private { \
private: \
    friend class C

#define DEPTHSENSE_PRIVATE_BEGIN_USING_NAMESPACE(N, C) \
class N::C::C##Private { \
private: \
    friend class N::C

// variant to avoid "first seen using 'struct' now seen using 'class'" warnings with MSVC
#define DEPTHSENSE_PRIVATE_STRUCT_BEGIN_USING_NAMESPACE(N, C) \
class N::C::C##Private { \
private: \
    friend struct N::C

#define DEPTHSENSE_PRIVATE_END(C) \
}

#define DEPTHSENSE_PRIVATE_END_USING_NAMESPACE(N, C) \
}

// for completeness; see above
#define DEPTHSENSE_PRIVATE_STRUCT_END_USING_NAMESPACE(N, C) \
}

#define DEPTHSENSE_STRUCT_BASE(C) \
C(); \
C(const C &); \
~C(); \
C &operator=(const C &)

#define DEPTHSENSE_PRIVATE_ALLOCATE(C) \
priv = new C##Private()

// to be used in copy constructors
#define DEPTHSENSE_PRIVATE_COPY_ALLOCATE(C, arg) \
priv = new C##Private(arg.get_priv())

#define DEPTHSENSE_PRIVATE_DEALLOCATE(C) \
delete priv

#define DEPTHSENSE_PRIVATE_CTOR(C) \
C##Private()

#define DEPTHSENSE_PRIVATE_COPY_CTOR(C, arg) \
C##Private(const C##Private &arg)

#define DEPTHSENSE_PRIVATE_OPERATOR_EQUAL(C, arg) \
C##Private &operator=(const C##Private &arg)

#define DEPTHSENSE_PRIVATE_OPERATOR_EQUALITY(C, arg) \
bool operator==(const C##Private &arg) const

#define DEPTHSENSE_PRIVATE_DTOR(C) \
virtual ~C##Private()

#define DEPTHSENSE_PRIVATE_INIT(C) \
C##Private &m = get_priv(); (void)m

#define DEPTHSENSE_PRIVATE_INIT_USING_NAMESPACE(N, C) \
N::C::C##Private &m = get_priv()

#define DEPTHSENSE_PRIVATE_NAMESPACE(C) \
C::C##Private::


/*----------------------------------------------------------------------------*/
// Helper macros for protected data access in API classes

#define DEPTHSENSE_PROTECTED_DECLARE(C) \
protected: \
    class C##Protected; \
    friend class C##Protected; \
    inline C##Protected &get_prot() { return *prot; } \
    inline const C##Protected &get_prot() const { return *((const C##Protected *) prot); } \
    C##Protected *prot

#define DEPTHSENSE_PROTECTED_BEGIN(C) \
class C::C##Protected { \
protected: \
    friend class C

#define DEPTHSENSE_PROTECTED_BEGIN_USING_NAMESPACE(N, C) \
class N::C::C##Protected { \
protected: \
    friend class N::C

// variant to avoid "first seen using 'struct' now seen using 'class'" warnings with MSVC
#define DEPTHSENSE_PROTECTED_STRUCT_BEGIN_USING_NAMESPACE(N, C) \
class N::C::C##Protected { \
protected: \
    friend struct N::C

#define DEPTHSENSE_PROTECTED_END(C) \
}

#define DEPTHSENSE_PROTECTED_END_USING_NAMESPACE(N, C) \
}

// for completeness; see above
#define DEPTHSENSE_PROTECTED_STRUCT_END_USING_NAMESPACE(N, C) \
}

#define DEPTHSENSE_STRUCT_BASE(C) \
C(); \
C(const C &); \
~C(); \
C &operator=(const C &)

#define DEPTHSENSE_PROTECTED_ALLOCATE(C) \
prot = new C##Protected()

// to be used in copy constructors
#define DEPTHSENSE_PROTECTED_COPY_ALLOCATE(C, arg) \
prot = new C##Protected(arg.get_prot())

#define DEPTHSENSE_PROTECTED_DEALLOCATE(C) \
delete prot

#define DEPTHSENSE_PROTECTED_CTOR(C) \
C##Protected()

#define DEPTHSENSE_PROTECTED_COPY_CTOR(C, arg) \
C##Protected(const C##Protected &arg)

#define DEPTHSENSE_PROTECTED_OPERATOR_EQUAL(C, arg) \
C##Protected &operator=(const C##Protected &arg)

#define DEPTHSENSE_PROTECTED_DTOR(C) \
virtual ~C##Protected()

#define DEPTHSENSE_PROTECTED_INIT(C) \
C##Protected &m = get_prot()

#define DEPTHSENSE_PROTECTED_INIT_USING_NAMESPACE(N, C) \
N::C::C##Protected &m = get_prot()

#define DEPTHSENSE_PROTECTED_NAMESPACE(C) \
C::C##Protected::


/*----------------------------------------------------------------------------*/
// Helper macro for disabling copy constructors and overloaded = operators;
// to be used in the private: section of the class definition

#define DEPTHSENSE_DISABLE_COPY(C) \
C(const C &src); \
C &operator=(const C &src)

#endif	/* _DEPTHSENSEAPI_H */

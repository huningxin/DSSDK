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


#ifndef _Pointer_hxx
#define _Pointer_hxx

#include <DepthSenseTypes.h>

namespace DepthSense
{
    namespace Utils
    {
        class BinaryReader;
        class BinaryWriter;
    }

    /// Exposes a memory buffer
    ///
    /// The Pointer class exposes a read-only memory buffer and its
    /// number of elements to the client application.
    ///
    /// The Pointer class feature automatic memory management,
    /// implemented with reference counted smart pointer mechanisms.
    ///
    /// \tparam T the element type
    template <class T>
    class DEPTHSENSE_API Pointer
    {
    public:
#ifndef DEPTHSENSE_DOC
        Pointer ();

        Pointer (const Pointer& other);

        Pointer& operator= (const Pointer& other);

        ~Pointer ();
#endif

        /// Returns the internal memory buffer
        ///
        /// Returns the internal memory buffer. The returned memory is
        /// owned by the Pointer instance and should not be modified,
        /// deleted or freed.
        ///
        /// \return the internal memory buffer, or \c NULL if the pointer is unset
        ///
        /// \exception DepthSense::IOException could not open the shared memory buffer
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        operator const T* () const;

        /// Returns the number of elements
        ///
        /// Returns the number of \p T elements contained in the
        /// current pointer.
        ///
        /// \return the number of elements, or \c 0 if the pointer is unset
        int32_t size () const;

    private:
        void* _data;

        Pointer (DepthSense::Utils::BinaryReader& reader);

        Pointer (uint64_t name,
                 int32_t index,
                 int32_t offset,
                 int32_t size,
                 int32_t totalSize);

        void serialize (DepthSense::Utils::BinaryWriter& writer) const;

        uint64_t name();

        friend class PointerPrivate;
    };
};

#endif

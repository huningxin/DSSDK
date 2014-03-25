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
// info@softkinetic.com Copyright (c) 2002-2014 Softkinetic Sensors NV
////////////////////////////////////////////////////////////////////////////////



#ifndef _Vector_hxx
#define _Vector_hxx

#include <vector>
#include <DepthSenseAPI.h>

namespace DSI
{
    template <class T>
    class Vector
    {
    public:
        DEPTHSENSE_API Vector ();

        DEPTHSENSE_API Vector (std::vector<T> vec);

        DEPTHSENSE_API Vector (const Vector& other);

        DEPTHSENSE_API Vector& operator= (const Vector& other);

        DEPTHSENSE_API ~Vector ();

        DEPTHSENSE_API int32_t size () const;

        DEPTHSENSE_API const T& operator[] (int32_t index) const;

        DEPTHSENSE_API void push_back (T value);

        static Vector marshal (std::vector<T> value)
        {
            Vector r;

            for (typename std::vector<T>::const_iterator iter = value.begin(); iter != value.end(); iter++)
                r.push_back(*iter);

            return r;
        }

        std::vector<T> unmarshal () const
        {
            std::vector<T> r;

            for (int32_t i = 0; i < size(); i++)
                r.push_back((*this)[i]);

            return r;
        }

    private:
        void* _data;
    };
}

#endif

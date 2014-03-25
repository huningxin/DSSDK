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


#ifndef _String_hxx
#define _String_hxx

#include <DepthSenseAPI.h>
#include <DepthSenseTypes.h>
#include <string>

namespace DSI
{
    class String
    {
    public:
        DEPTHSENSE_API String ();

        DEPTHSENSE_API String (const char* str);

        DEPTHSENSE_API String (std::string str);

        DEPTHSENSE_API String (const String& other);

        DEPTHSENSE_API String& operator= (const String& other);

        DEPTHSENSE_API ~String ();

        DEPTHSENSE_API const char *c_str () const;

        DEPTHSENSE_API int32_t length () const;

        std::string unmarshal () const
        {
            return std::string(c_str(), length());
        }

    private:
        void* _data;
    };
}

#endif

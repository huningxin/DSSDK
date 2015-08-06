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


#ifndef _Event_hxx
#define _Event_hxx

#include <DepthSenseAPI.h>
#include <EventHandler.hxx>

namespace DSI
{
    class InstanceBase;
};

namespace DepthSense
{
    class DEPTHSENSE_API EventBase
    {
    public:
        virtual ~EventBase ();
    };

    template <class InterfaceType, class DataType>
    class DEPTHSENSE_API Event : public EventBase
    {
    public:
        virtual ~Event ();

        void raise (InterfaceType obj, DataType data);

    protected:
        Event (DSI::InstanceBase* instance, int eventID, int setEnableRequestID);

        void connect (DepthSense::EventHandler<InterfaceType, DataType>* handler);
        void disconnect (DepthSense::EventHandler<InterfaceType, DataType>* handler);

    private:
        void* _data;

        void setEnable (bool value);

        friend class DSI::InstanceBase;
    };
}

#endif

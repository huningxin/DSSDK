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

#ifndef _PropertyPost_hxx
#define _PropertyPost_hxx

inline std::string DepthSense::Property<std::string>::getValue (DepthSense::Interface iface) const
{
    return getValue_p(iface).unmarshal();
}

inline std::string DepthSense::Property<std::string>::getValue (DepthSense::Interface iface, const char* propertyName)
{
    return getValue_p(iface, propertyName).unmarshal();
}

template <class T>
inline std::vector<T> DepthSense::Property< std::vector<T> >::getValue (DepthSense::Interface iface) const
{
    return getValue_p(iface).unmarshal();
}

template <class T>
inline void DepthSense::Property< std::vector<T> >::setValue (DepthSense::Interface iface, std::vector<T> value) const
{
    setValue_p(iface, DSI::Vector<T>::marshal(value));
}

template <class T>
inline std::vector<T> DepthSense::Property< std::vector<T> >::getValue (DepthSense::Interface iface, const char* propertyName)
{
    return getValue_p(iface, propertyName).unmarshal();
}

template <class T>
inline void DepthSense::Property< std::vector<T> >::setValue (DepthSense::Interface iface, const char* propertyName, std::vector<T> value)
{
    setValue_p(iface, propertyName, DSI::Vector<T>::marshal(value));
}


#endif

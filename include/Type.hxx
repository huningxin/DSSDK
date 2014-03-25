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


#ifndef _Type_hxx
#define _Type_hxx

#include <vector>
#include <string>
#include <functional>
#include <DepthSenseAPI.h>
#include <DepthSenseTypes.h>
#include <Property.hxx>
#include <String.hxx>
#include <Vector.hxx>

namespace DSI
{
    class Instance;
}

namespace DepthSense
{
    /// \class Type DepthSense.hxx
    ///
    /// Represents a DepthSense instance type
    ///
    /// The Type class can be used to obtain information about the
    /// runtime type of a DepthSense::Interface instance.
    ///
    /// \par Example:
    /// <pre>
    /// void displayTypeName (DepthSense::Interface iface)
    /// {
    ///   DepthSense::Type type = iface.getType();
    ///   cout << "Interface is of type " << type.name() << endl;
    /// }
    /// </pre>
    ///
    /// The Type class features automatic memory management,
    /// implemented with reference counted smart pointer mechanisms.
    class Type
    {
    public:
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API Type ();

        DEPTHSENSE_API Type (const Type& other);

        DEPTHSENSE_API Type& operator= (const Type& other);

        DEPTHSENSE_API ~Type ();

        DEPTHSENSE_API bool operator== (const Type& other) const;
        DEPTHSENSE_API bool operator!= (const Type& other) const;

        // allows to use Type as key of a std::map
        DEPTHSENSE_API bool operator< (const Type& other) const;
        DEPTHSENSE_API bool operator> (const Type& other) const;
#endif

        /// Returns the qualified name of the current type
        ///
        /// Returns the qualified name of the current type.
        ///
        /// \return a string of the form \c "DepthSense.ColorNode"
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        std::string name () const
        {
            return name_p().unmarshal();
        }

        /// Gets a property by name
        ///
        /// Returns the property whose name is \p name, or an unset
        /// PropertyBase instance if no such property exists.
        ///
        /// Name lookup is performed in the current type and in its
        /// type ancestry.
        ///
        /// \return the property named \p name, or an unset instance if not found
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        DEPTHSENSE_API PropertyBase getProperty (const char* name) const;

        /// Gets the properties of the current type and of its type ancestry
        ///
        /// Returns the properties of the current type and of its type
        /// ancestry, sorted in no particular order.
        ///
        /// \return the property list
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        std::vector<PropertyBase> getProperties () const
        {
            return getProperties_p().unmarshal();
        }

    private:
        void* _data;

        // does not take ownership of the passed data
        Type (void* data);

        int32_t typeID () const;

        int32_t typeMask () const;

        DEPTHSENSE_API DSI::String name_p () const;

        DEPTHSENSE_API DSI::Vector<PropertyBase> getProperties_p () const;

        friend class PropertyBase;

        friend class TypePrivate;

        friend class DSI::Instance;
    };
}

#ifdef __DS_HAVE_STD_HASH
namespace std
{
    template <>
    struct DEPTHSENSE_API hash<DepthSense::Type>
    {
        size_t operator() (DepthSense::Type type) const;
    };
}
#endif

#endif

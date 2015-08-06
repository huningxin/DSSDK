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


#ifndef _Property_hxx
#define _Property_hxx

#include <string>
#include <functional>
#include <DepthSenseAPI.h>
#include <DepthSenseTypes.h>
#include <String.hxx>
#include <Vector.hxx>

namespace DepthSense
{
    namespace Utils
    {
        class BinaryReader;
        class BinaryWriter;
    }

    class Interface;

    class Type;

    template <class T>
    class Property;

    class PropertyPrivate;

    /// \class PropertyBase DepthSense.hxx
    /// The base property class
    ///
    /// The PropertyBase class is the common base class for the
    /// strongly-typed Property template instantiations. It provides
    /// runtime property introspection facilities for Interface and
    /// its subclasses.
    ///
    /// A PropertyBase object can be obtained by using
    /// Type::getProperty(), Type::getProperties() or by connecting to
    /// the \c propertyChanged event of the Interface class.
    ///
    /// The PropertyBase class and its subclasses feature automatic
    /// memory management, implemented with reference counted smart
    /// pointer mechanisms.
    class PropertyBase
    {
    public:
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API PropertyBase ();

        DEPTHSENSE_API PropertyBase (const PropertyBase& other);

        DEPTHSENSE_API PropertyBase& operator= (const PropertyBase& other);
#endif

#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        ~PropertyBase ();

        /// Returns the declaring type of the current property
        ///
        /// Returns the type in which the current property was
        /// declared. This type might or might not correspond to the
        /// derived runtime type of the interface being queried.
        ///
        /// \return the declaring type
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        Type declaringType () const;

        /// Returns the name of the current property
        ///
        /// Returns the name of the current property.
        ///
        /// \return the property name
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        std::string name () const
        {
            return name_p().unmarshal();
        }

        /// Returns whether the current property is read-only
        ///
        /// Returns whether the current property is
        /// read-only. Contrast with isReadOnly(Interface) const, which
        /// determines whether the current property is read-only in
        /// the provided interface.
        ///
        /// \return whether the current property is read-only
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        bool isReadOnly () const;

        /// Returns whether the current property is read-only in the provided interface
        ///
        /// Returns whether the current property is read-only in \p
        /// iface.  Properties which are read-write by design (that
        /// is, for which isReadOnly() returns true) can be read-only
        /// in a given interface if, for instance, the interface is a
        /// Node and the client application did not request full
        /// control access of the node, which can be done with
        /// Context::requestControl(Node).
        ///
        /// Contrast with isReadOnly(), which returns whether the
        /// current property is read-only as per its static,
        /// compile-time specifications.
        ///
        /// \param iface the interface to examine
        ///
        /// \return whether the current property is read-only in \p iface
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset
        /// \exception std::bad_alloc not enough memory to perform the requested operation
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        bool isReadOnly (Interface iface) const;

        /// Checks if the current property instance is set
        ///
        /// Checks if the current property instance is set.
        ///
        /// Given a variable \c prop (of type PropertyBase) and a
        /// variable \c ptr (of type \c void*), the
        /// <tt>prop.isSet()</tt> expression is semantically
        /// equivalent to <tt>ptr != NULL</tt>.
        ///
        /// \par Example:
        /// <pre>
        /// DepthSense::PropertyBase prop;
        /// bool b = prop.isSet(); // b is false
        /// </pre>
        ///
        /// \return whether the current property instance is set
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        bool isSet () const;

        /// Unsets the current property instance
        ///
        /// Unsets the current property instance.
        ///
        /// Given a variable \c prop (of type PropertyBase) and a variable
        /// \c ptr (of type \c void*), the <tt>prop.unset();</tt> statement
        /// is semantically equivalent to <tt>p = NULL;</tt>.
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        void unset ();

#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API bool operator== (const PropertyBase& other) const;
        DEPTHSENSE_API bool operator!= (const PropertyBase& other) const;

        // allows to use a property as std::map key
        DEPTHSENSE_API bool operator< (const PropertyBase& other) const;
        DEPTHSENSE_API bool operator> (const PropertyBase& other) const;

        template <class T>
        bool is () const;

        template <class T>
        T as () const;

        bool isPublic() const;
#endif

    private:
        void* _data;

        // does not take ownership of the passed data
        PropertyBase (void* _data);

        DEPTHSENSE_API DSI::String name_p () const;

        void serialize (DepthSense::Utils::BinaryWriter& writer);
        static PropertyBase deserialize (DepthSense::Utils::BinaryReader& reader, Type (*typeFactory) (int32_t typeID));

        friend class PropertyPrivate;

        template <class T>
        friend class Property;
    };

    /// \class Property DepthSense.hxx
    /// The strongly-typed property leaf class
    ///
    /// The Property class provides strongly-typed runtime property
    /// introspection facilities for Interface and its subclasses.
    ///
    /// \tparam T the property type
    template <class T>
    class Property
#ifdef DEPTHSENSE_DOC
        : public PropertyBase
#endif
    {
    public:
        /// The property type
        ///
        /// Exposes the property type.
        typedef T Type;

#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API Property ();

        DEPTHSENSE_API explicit Property (const PropertyBase& prop);

        DEPTHSENSE_API Property (const Property& other);

        DEPTHSENSE_API Property& operator= (const Property& other);

        DEPTHSENSE_API ~Property ();

        DEPTHSENSE_API DepthSense::Type declaringType () const;

        std::string name () const
        {
            return name_p().unmarshal();
        }

        DEPTHSENSE_API bool isReadOnly () const;
        DEPTHSENSE_API bool isReadOnly (Interface iface) const;

        DEPTHSENSE_API bool isSet () const;
        DEPTHSENSE_API void unset ();

        DEPTHSENSE_API bool operator== (const Property& other) const;
        DEPTHSENSE_API bool operator!= (const Property& other) const;

        // allows to use a property as std::map key
        DEPTHSENSE_API bool operator< (const Property& other) const;
        DEPTHSENSE_API bool operator> (const Property& other) const;

        DEPTHSENSE_API operator PropertyBase () const;
#endif

        /// Returns the value of the current property in an interface
        ///
        /// Returns the value of the current property in \p iface.
        ///
        /// \param iface the interface to examine
        ///
        /// \return the property value
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset, or the current property does not exist in the type of \p iface
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ///
        /// \note
        /// In addition to the exceptions specified above, this method
        /// can throw any of the exceptions specified in the getter of
        /// the property.
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        T getValue (Interface iface) const;

        /// Sets the value of the current property in an interface
        ///
        /// Sets the value of the current property in \p iface.
        ///
        /// \param iface the interface to modify
        /// \param value the value to set
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset, or the current property does not exist in the type of \p iface
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ///
        /// \note
        /// In addition to the exceptions specified above, this method
        /// can throw any of the exceptions specified in the setter of
        /// the property.
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        void setValue (Interface iface, T value) const;

        /// Returns the value of a property in an interface
        ///
        /// Returns the value of property named \p propertyName in \p iface.
        ///
        /// \param iface the interface to examine
        /// \param propertyName the name of the property to query
        ///
        /// \return the property value
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset, or no property named \p propertyName exists in the type of \p iface
        /// \exception DepthSense::InvalidOperationException the type of the looked up property does not match \p T
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ///
        /// \note
        /// In addition to the exceptions specified above, this method
        /// can throw any of the exceptions specified in the getter of
        /// the property.
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        static T getValue (Interface iface, const char* propertyName);

        /// Sets the value of a property in an interface
        ///
        /// Sets the value of property named \p propertyName in \p iface.
        ///
        /// \param iface the interface to modify
        /// \param propertyName the name of the property whose value to set
        /// \param value the value to set
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset, or no property named \p propertyName exists in the type of \p iface
        /// \exception DepthSense::InvalidOperationException the type of the looked up property does not match \p T
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ///
        /// \note
        /// In addition to the exceptions specified above, this method
        /// can throw any of the exceptions specified in the setter of
        /// the property.
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        static void setValue (Interface iface, const char* propertyName, T value);

    private:
        void *_data;

        // does not take ownership of the passed data
        Property (void* data);

        // takes ownership of the passed data
        static Property take (void* data);

        DEPTHSENSE_API DSI::String name_p () const;

        friend class PropertyBase;

        friend class PropertyPrivate;
    };

    /// The string property class
    ///
    /// In DepthSense SDK, properties of type \c std::string are
    /// particular in so that they are asymmetric: while the getter
    /// returns a \c std::string value, the setter accepts a <tt>const
    /// char*</tt> argument.
    ///
    /// To account for this peculiarity, the Property<std::string>
    /// template specialization is defined. The only difference with
    /// the non-specialized Property template is that the setValue()
    /// methods accept a \p value argument of type <tt>const
    /// char*</tt> rather than of type \c T.
    template <>
    class Property<std::string>
#ifdef DEPTHSENSE_DOC
        : public PropertyBase
#endif
    {
    public:
        /// The property type
        ///
        /// Exposes the property type.
        typedef std::string Type;

#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API Property ();

        DEPTHSENSE_API explicit Property (const PropertyBase& prop);

        DEPTHSENSE_API Property (const Property& other);

        DEPTHSENSE_API Property& operator= (const Property& other);

        DEPTHSENSE_API ~Property ();

        DEPTHSENSE_API DepthSense::Type declaringType () const;

        std::string name () const
        {
            return name_p().unmarshal();
        }

        DEPTHSENSE_API bool isReadOnly () const;
        DEPTHSENSE_API bool isReadOnly (Interface iface) const;

        DEPTHSENSE_API bool isSet () const;
        DEPTHSENSE_API void unset ();

        DEPTHSENSE_API bool operator== (const Property& other) const;
        DEPTHSENSE_API bool operator!= (const Property& other) const;

        // allows to use a property as std::map key
        DEPTHSENSE_API bool operator< (const Property& other) const;
        DEPTHSENSE_API bool operator> (const Property& other) const;

        DEPTHSENSE_API operator PropertyBase () const;
#endif

        /// Returns the value of the current property in an interface
        ///
        /// Returns the value of the current property in \p iface.
        ///
        /// \param iface the interface to examine
        ///
        /// \return the property value
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset, or the current property does not exist in the type of \p iface
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ///
        /// \note
        /// In addition to the exceptions specified above, this method
        /// can throw any of the exceptions specified in the getter of
        /// the property.
        std::string getValue (Interface iface) const;

        /// Sets the value of the current property in an interface
        ///
        /// Sets the value of the current property in \p iface.
        ///
        /// \param iface the interface to modify
        /// \param value the value to set
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset, or the current property does not exist in the type of \p iface
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ///
        /// \note
        /// In addition to the exceptions specified above, this method
        /// can throw any of the exceptions specified in the setter of
        /// the property.
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        void setValue (Interface iface, const char* value) const;

        /// Returns the value of a property in an interface
        ///
        /// Returns the value of property named \p propertyName in \p iface.
        ///
        /// \param iface the interface to examine
        /// \param propertyName the name of the property to query
        ///
        /// \return the property value
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset, or no property named \p propertyName exists in the type of \p iface
        /// \exception DepthSense::InvalidOperationException the type of the looked up property does not match \p T
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ///
        /// \note
        /// In addition to the exceptions specified above, this method
        /// can throw any of the exceptions specified in the getter of
        /// the property.
        static std::string getValue (Interface iface, const char* propertyName);

        /// Sets the value of a property in an interface
        ///
        /// Sets the value of property named \p propertyName in \p iface.
        ///
        /// \param iface the interface to modify
        /// \param propertyName the name of the property whose value to set
        /// \param value the value to set
        ///
        /// \exception DepthSense::ArgumentException \p iface is unset, or no property named \p propertyName exists in the type of \p iface
        /// \exception DepthSense::InvalidOperationException the type of the looked up property does not match \p T
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ///
        /// \note
        /// In addition to the exceptions specified above, this method
        /// can throw any of the exceptions specified in the setter of
        /// the property.
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        static void setValue (Interface iface, const char* propertyName, const char* value);

    private:
        void *_data;

        // does not take ownership of the passed data
        Property (void* data);

        // takes ownership of the passed data
        static Property take (void* data);

        DEPTHSENSE_API DSI::String name_p () const;

        DEPTHSENSE_API DSI::String getValue_p (Interface iface) const;

        DEPTHSENSE_API static DSI::String getValue_p (Interface iface, const char* propertyName);

        friend class PropertyBase;

        friend class PropertyPrivate;
    };

#ifndef DEPTHSENSE_DOC
    template <class T>
    class Property< std::vector<T> >
    {
    public:
        typedef std::vector<T> Type;

        DEPTHSENSE_API Property ();

        DEPTHSENSE_API explicit Property (const PropertyBase& prop);

        DEPTHSENSE_API Property (const Property& other);

        DEPTHSENSE_API Property& operator= (const Property& other);

        DEPTHSENSE_API ~Property ();

        DEPTHSENSE_API DepthSense::Type declaringType () const;

        std::string name () const
        {
            return name_p().c_str();
        }

        DEPTHSENSE_API bool isReadOnly () const;
        DEPTHSENSE_API bool isReadOnly (Interface iface) const;

        DEPTHSENSE_API bool isSet () const;
        DEPTHSENSE_API void unset ();

        DEPTHSENSE_API bool operator== (const Property& other) const;
        DEPTHSENSE_API bool operator!= (const Property& other) const;

        // allows to use a property as std::map key
        DEPTHSENSE_API bool operator< (const Property& other) const;
        DEPTHSENSE_API bool operator> (const Property& other) const;

        DEPTHSENSE_API operator PropertyBase () const;

        std::vector<T> getValue (Interface iface) const;

        void setValue (Interface iface, std::vector<T> value) const;

        static std::vector<T> getValue (Interface iface, const char* propertyName);

        static void setValue (Interface iface, const char* propertyName, std::vector<T> value);

    private:
        void *_data;

        // does not take ownership of the passed data
        Property (void* data);

        // takes ownership of the passed data
        static Property take (void* data);

        DEPTHSENSE_API DSI::String name_p () const;

        DEPTHSENSE_API DSI::Vector<T> getValue_p (Interface iface) const;

        DEPTHSENSE_API void setValue_p (Interface iface, DSI::Vector<T> value) const;

        DEPTHSENSE_API static DSI::Vector<T> getValue_p (Interface iface, const char* propertyName);

        DEPTHSENSE_API static void setValue_p (Interface iface, const char* propertyName, DSI::Vector<T> value);

        friend class PropertyBase;

        friend class PropertyPrivate;
    };
#endif
}

#ifdef __DS_HAVE_STD_HASH
namespace std
{
    template <>
    struct DEPTHSENSE_API hash<DepthSense::PropertyBase>
    {
        size_t operator() (DepthSense::PropertyBase property) const;
    };
}
#endif

#endif

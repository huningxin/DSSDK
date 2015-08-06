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


#pragma once

#ifndef DEPTHSENSE_HXX
#define	DEPTHSENSE_HXX

/// \file DepthSense.hxx
///
/// The %DepthSense SDK.

/// \mainpage The %DepthSense SDK Reference Manual
///
/// \section overview Overview
///
/// %DepthSense SDK provides an interface to the various SoftKinetic
/// %DepthSense cameras. By using the %DepthSense library, you can
/// configure one or more %DepthSense cameras and capture depth, color and
/// audio frame data.
///
/// Some of the %DepthSense SDK features are:
///
/// <ul>
///   <li>a type system transparently combining automatic memory management and polymorphism, and providing some reflection capabilities</li>
///   <li>an elegant event-based framework for receiving frame data and server notifications</li>
///   <li>a property system supporting reflection</li>
///   <li>multi-camera and multi-client support</li>
/// </ul>
///
/// These features will be examined in more detail in the following sections.
///
/// \section type-system The DepthSense SDK type system
///
/// The %DepthSense SDK type system provides automatic memory
/// management (which is implemented with traditional smart pointer
/// mechanisms) while preserving the syntactical advantages of C++
/// polymorphism.
///
/// %DepthSense SDK objects reside on the stack and are passed by
/// value (like smart pointers), but offer polymorphism abilities
/// similar to what C++ offers with heap-based pointers. The following
/// examples compare C++ and %DepthSense with commonly-used idioms.
///
/// \subsection init-unset-var Initializing an object variable to the unset state
///
/// \subsubsection init-unset-var-cxx C++ code
/// \code
/// MyClass* obj = NULL;
/// \endcode
///
/// \subsubsection init-unset-var-ds DepthSense SDK code
/// \code
/// MyClass obj;
/// \endcode
///
/// \subsection testing-if-set Testing if an object variable is set
///
/// \subsubsection testing-if-set-cxx C++ code
/// \code
/// bool b = obj != NULL;
/// \endcode
///
/// \subsubsection testing-if-set-ds DepthSense SDK code
/// \code
/// bool b = obj.isSet();
/// \endcode
///
/// \subsection unset-var Unsetting an object variable
///
/// \subsubsection unset-var-cxx C++ code
/// \code
/// obj = NULL;
/// \endcode
///
/// \subsubsection unset-var-ds DepthSense SDK code
/// \code
/// obj.unset();
/// \endcode
///
/// \subsection upcast Performing an upcast
///
/// \subsubsection upcast-cxx C++ code
/// \code
/// MyDerivedClass* derived = param1;
/// MyBaseClass* base = derived;
/// \endcode
///
/// \subsubsection upcast-ds DepthSense SDK code
/// \code
/// MyDerivedClass derived = param1;
/// MyBaseClass base = derived;
/// \endcode
///
/// \subsection derived-call Calling a method of the most derived class
///
/// \subsubsection derived-call-cxx C++ code
/// \code
/// obj->derivedMethod();
/// \endcode
///
/// \subsubsection derived-call-ds DepthSense SDK code
/// \code
/// obj.derivedMethod();
/// \endcode
///
/// \subsection base-call Calling a method of a base class
///
/// \subsubsection base-call-cxx C++ code
/// \code
/// obj->baseMethod();
/// \endcode
///
/// \subsubsection base-call-ds DepthSense SDK code
/// \code
/// obj.baseMethod();
/// \endcode
///
/// \subsection rtt-test Testing the runtime type of an object
///
/// \subsubsection rtt-test-cxx C++ code
/// \code
/// MyBaseClass* base = param1;
/// bool b = dynamic_cast<MyDerivedClass*>(base) != NULL;
/// \endcode
///
/// \subsubsection rtt-test-ds DepthSense SDK code
/// \code
/// MyBaseClass base = param1;
/// bool b = base.is<MyDerivedClass>();
/// \endcode
///
/// \subsection downcast Performing a downcast which cannot fail
///
/// \subsubsection downcast-cxx C++ code
/// \code
/// // if the cast fails, derived is NULL and the code crashes
/// MyBaseClass* base = param1;
/// MyDerivedClass* derived = dynamic_cast<MyDerivedClass*>(base);
/// derived->someMethod();
/// \endcode
///
/// \subsubsection downcast-ds DepthSense SDK code
/// \code
/// // if the cast fails, std::bad_cast is thrown
/// MyBaseClass base = param1;
/// MyDerivedClass derived = (MyDerivedClass) base;
/// derived.someMethod();
/// \endcode
///
/// \subsection downcast-attempt Performing a downcast which can fail
///
/// \subsubsection downcast-attempt-cxx C++ code
/// \code
/// MyBaseClass* base = param1;
/// MyDerivedClass* derived = dynamic_cast<MyDerivedClass*>(base);
/// bool castSucceeded = derived != NULL;
/// \endcode
///
/// \subsubsection downcast-attempt-ds DepthSense SDK code
/// \code
/// MyBaseClass base = param1;
/// MyDerivedClass derived = base.as<MyDerivedClass>();
/// bool castSucceeded = derived.isSet();
/// \endcode
///
/// \subsection get-type-name Obtaining the name of the runtime type of an object
///
/// \subsubsection get-type-name-cxx C++ code
/// \code
/// // the name is implementation-defined and often mangled
/// const char* name = typeid(*obj).name();
/// \endcode
///
/// \subsubsection get-type-name-ds DepthSense SDK code
/// \code
/// // the name is formalized and of the form DepthSense.ColorNode
/// std::string name = obj.getType().name();
/// \endcode
///
/// \subsection get-properties Obtaining the list of properties of an interface
///
/// \subsubsection get-properties-cxx C++ code
/// \code
/// // C++ provides no such facility
/// \endcode
///
/// \subsubsection get-properties-ds DepthSense SDK code
/// \code
/// std::vector<DepthSense::PropertyBase> properties = MyClass::type().getProperties();
/// \endcode
///
/// \section event-system The DepthSense SDK event system
///
/// %DepthSense SDK features an event-based framework for providing
/// the client application with frame data and server notifications.
///
/// The following example demonstrates how to capture the data coming
/// from the first available color sensor attached to the host system.
/// 
/// \include Apps/DepthSenseHelloWorld/src/DepthSenseHelloWorld.cxx
///
/// \section property-system The DepthSense SDK property system
///
/// Each %DepthSense class (such as DepthSense::Device or
/// DepthSense::ColorNode) defines properties of various types.
///
/// While the most natural way of querying and modifying the value of
/// a property is to use the relevant accessor methods, %DepthSense
/// SDK also supports property reflection. The following example
/// demonstrates how to discover and display object properties at
/// runtime.
///
/// \include Apps/DepthSensePropertyHelloWorld/src/DepthSensePropertyHelloWorld.cxx
/// \section multi Multi-camera, multi-client support
///
/// %DepthSense SDK can interface with multiple cameras
/// simultaneously. The DepthSense::Context::getDevices() method
/// returns the list of camera devices attached to the host system.
///
/// Moreover, a single %DepthSense server instance can serve multiple
/// clients simultaneously. To be notified when the server accepts a
/// new client connection, connect to the \c clientConnected event of
/// the DepthSense::Context class.

#include <string>

#include <DepthSenseVersion.hxx>
#include <DepthSenseAPI.h>
#include <DepthSenseTypes.h>
#include <DepthSense-public.hxx>
#include <PropertyPost.hxx>

namespace DepthSense
{
    /// Converts a resolution to a FrameFormat value
    ///
    /// Converts a resolution to a FrameFormat enumeration value.
    ///
    /// \param width the width
    /// \param height the height
    ///
    /// \return the corresponding FrameFormat value
    ///
    /// \exception DepthSense::ArgumentException the \p width, \p height pair does not match any FrameFormat value
    /// \exception std::bad_alloc not enough memory to perform the requested operation
    FrameFormat
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        FrameFormat_fromResolution (int32_t width, int32_t height);

    /// Converts a FrameFormat value to a resolution
    ///
    /// Converts a FrameFormat enumeration value to a resolution.
    ///
    /// \param frameFormat the FrameFormat value to convert
    /// \param width a location to store the resulting width
    /// \param height a location to store the resulting height
    ///
    /// \exception DepthSense::ArgumentException \p frameFormat is invalid
    /// \exception std::bad_alloc not enough memory to perform the requested operation
    void
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        FrameFormat_toResolution (FrameFormat frameFormat, int32_t* width, int32_t* height);

    /// Gets the DepthSense Library version information
    ///
    /// Returns a structure containing the DepthSense Library version information.
    ///
    /// \return the DepthSense Library version information
    ///
    /// \sa Context::getClientVersion
    /// \sa Context::getServerVersion
    DepthSense::Version
#ifndef DEPTHSENSE_DOC
        DEPTHSENSE_API
#endif
        getLibraryVersion ();

    /// Computes the UV mapping of image points
    ///
    /// The ProjectionHelper class computes the UV mapping of a set of
    /// image points.
    class
    #ifndef DEPTHSENSE_DOC
    DEPTHSENSE_API
    #endif
    ProjectionHelper
    {
        DEPTHSENSE_PRIVATE_DECLARE(ProjectionHelper);

        public:

        /// Instantiates a ProjectionHelper
        ///
        /// Creates a new instance of the ProjectionHelper class.
        ///
        /// \param parameters the system model parameters to use (see DepthSense::DepthNode::NewSampleReceivedData::stereoCameraParameters)
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        ProjectionHelper (StereoCameraParameters parameters);
        ~ProjectionHelper ();

        /// Gets the system model parameters
        ///
        /// Gets the system model parameters used in the computations.
        ///
        /// \return the system model parameters currently in use
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        StereoCameraParameters getStereoCameraParameters () const;

        /// Sets the system model parameters
        ///
        /// Sets the system model parameters to use in the computations.
        ///
        /// \param parameters the system model parameters to use (see DepthSense::DepthNode::NewSampleReceivedData::stereoCameraParameters)
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        void setStereoCameraParameters (StereoCameraParameters parameters);

        /// Computes the UV mapping of an Extended2DPoint set
        ///
        /// Computes the UV mapping of an Extended2DPoint set.
        ///
        /// \param input an Extended2DPoint array
        /// \param output a user-allocated array of UV coordinates
        /// \param npoints the number of points to be transformed
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        void getUVMapping (const Extended2DPoint* input,
                           UV* output,
                           int32_t npoints);

        /// Computes the UV mapping of a FPExtended2DPoint set
        ///
        /// Computes the UV mapping of a FPExtended2DPoint set.
        ///
        /// \param input a FPExtended2DPoint array
        /// \param output a user-allocated array of UV coordinates
        /// \param npoints the number of points to be transformed
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        void getUVMapping ( const FPExtended2DPoint* input,
                            UV* output,
                            int32_t npoints );

        /// Computes the 3D coordinates of an Extended2DPoint set
        ///
        /// Computes the 3D coordinates of an Extended2DPoint set. If
        /// a point lies outside of the field of view of the camera,
        /// the distortion coefficient is assumed to be the one of the
        /// last point within the field of view.
        ///
        /// The depth of each Extended2DPoint should lie in the range
        /// [0 - 31999], otherwise the corresponding 3D output point
        /// will be mapped to {0, 0, input[i].z}.
        ///
        /// \param input an Extended2DPoint array
        /// \param output an user-allocated array of 3D points
        /// \param npoints the number of points to be transformed
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        void get3DCoordinates (const Extended2DPoint* input,
                               Vertex* output,
                               int32_t npoints);

        /// Computes the 3D coordinates of a FPExtended2DPoint set
        ///
        /// Computes the 3D coordinates of a FPExtended2DPoint set.
        /// If a point lies outside of the field of view of the
        /// camera, the distortion coefficient is assumed to be the
        /// one of the last point within the field of view.
        ///
        /// The depth of each FPExtended2DPoint should be greater than
        /// 0.0, otherwise the corresponding 3D output point will be
        /// mapped to {0.0, 0.0, input[i].z}.
        ///
        /// \param input a FPExtended2DPoint array
        /// \param output an user-allocated array of 3D points
        /// \param npoints the number of points to be transformed
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        void get3DCoordinates (const FPExtended2DPoint* input,
                               FPVertex* output,
                               int32_t npoints);

        /// Computes the 2D coordinates of a Vertex set
        ///
        /// Computes the 2D coordinates of a Vertex set on one camera
        /// plane. If a point lies outside of the field of view of the
        /// camera, the distortion coefficient is assumed to be the
        /// one of the last point within the field of view.
        ///
        /// \param input a Vertex array
        /// \param output an user-allocated array of 2D points
        /// \param npoints the number of points to be transformed
        /// \param plane the plane to project on
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        void get2DCoordinates (const Vertex* input,
                               Point2D* output,
                               int32_t npoints,
                               CameraPlane plane);

        /// Computes the 2D coordinates of a FPVertex set
        ///
        /// Computes the 2D coordinates of a FPVertex set on one
        /// camera plane.  If a point lies outside of the field of
        /// view of the camera, the distortion coefficient is assumed
        /// to be the one of the last point within the field of view.
        ///
        /// \param input a FPVertex array
        /// \param output an user-allocated array of 2D points
        /// \param npoints the number of points to be transformed
        /// \param plane the plane to project on
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        void get2DCoordinates (const FPVertex* input,
                               Point2D* output,
                               int32_t npoints,
                               CameraPlane plane);
        
        private:
        DEPTHSENSE_DISABLE_COPY(ProjectionHelper);
    };

    // FIXME - Document
    class
    #ifndef DEPTHSENSE_DOC
    DEPTHSENSE_API
    #endif
    ProcessingHelper
    {
        DEPTHSENSE_PRIVATE_DECLARE(ProcessingHelper);

        public:
        ProcessingHelper (StereoCameraParameters parameters, short confidenceThreshold);
        ~ProcessingHelper ();

        /// Sets the system model parameters
        ///
        /// Sets the system model parameters to use in the computations.
        ///
        /// \param parameters the system model parameters to use (see DepthSense::DepthNode::NewSampleReceivedData::stereoCameraParameters)
        /// \param confidenceThreshold the confidence threshold
        ///
        /// \exception std::bad_alloc not enough memory to perform the requested operation
        void setParameters (StereoCameraParameters parameters, short confidenceThreshold);

        // Only scalar versions for the time being
        void applyConfidenceThreshold ( const short* confidenceMap, const short* input, short* output);
        void applyConfidenceThreshold ( const short* confidenceMap, const float* input, float* output);
        void applyConfidenceThreshold ( const short* confidenceMap, const Vertex* input, Vertex* output);
        void applyConfidenceThreshold ( const short* confidenceMap, const FPVertex* input, FPVertex* output);
        void applyConfidenceThreshold ( const short* confidenceMap, const UV* input, UV* output);

        // in place versions
        void applyConfidenceThreshold ( const short* confidenceMap, short* buffer);
        void applyConfidenceThreshold ( const short* confidenceMap, float* buffer);
        void applyConfidenceThreshold ( const short* confidenceMap, Vertex* buffer);
        void applyConfidenceThreshold ( const short* confidenceMap, FPVertex* buffer);
        void applyConfidenceThreshold ( const short* confidenceMap, UV* buffer);

        private:
        DEPTHSENSE_DISABLE_COPY(ProcessingHelper);
    };
}

#endif	/* DEPTHSENSE_HXX */

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


#ifndef _EventHandler_hxx
#define _EventHandler_hxx

#include <DepthSenseAPI.h>

namespace DepthSense
{
    class DEPTHSENSE_API EventHandlerBase
    {
    public:
        bool operator== (const EventHandlerBase& other) const;
        bool operator!= (const EventHandlerBase& other) const;

        virtual ~EventHandlerBase ();

    protected:
        virtual bool equals (EventHandlerBase* other) const = 0;
    };

    template <class InterfaceType, class DataType>
    class EventHandler : public EventHandlerBase
    {
    public:
        virtual void operator () (InterfaceType obj, DataType data) = 0;
    };

    template <class InterfaceType, class DataType>
    class FunctionHandler : public EventHandler<InterfaceType, DataType>
    {
    public:
        typedef void (*Function) (InterfaceType obj, DataType data);

        FunctionHandler (Function func)
            : _func(func)
        {
        }

        virtual void operator () (InterfaceType obj, DataType data)
        {
            _func(obj, data);
        }

    protected:
        virtual bool equals (EventHandlerBase* other) const
        {
            FunctionHandler<InterfaceType, DataType>* f = static_cast< FunctionHandler<InterfaceType, DataType>* >(other);
            return f != NULL && f->_func == _func;
        }

    private:
        Function _func;
    };

    template <class InterfaceType, class DataType, class FunctionType>
    class GenericFunctionHandler : public EventHandler<InterfaceType, DataType>
    {
    public:
        typedef FunctionType Function;

    protected:
        Function _func;

        GenericFunctionHandler (Function func)
            : _func(func)
        {
        }

        virtual bool equals (EventHandlerBase* other) const
        {
            GenericFunctionHandler<InterfaceType, DataType, FunctionType>* f = static_cast< GenericFunctionHandler<InterfaceType, DataType, FunctionType>* >(other);
            return f != NULL && f->_func == _func;
        }
    };

    template <class InterfaceType, class DataType, class ClosureDataType>
    class ClosureHandler : public EventHandler<InterfaceType, DataType>
    {
    public:
        typedef void (*Closure) (InterfaceType obj, DataType data, ClosureDataType closureData);

        ClosureHandler (Closure closure, ClosureDataType closureData)
            : _closure(closure), _closureData(closureData)
        {
        }

        virtual void operator () (InterfaceType obj, DataType data)
        {
            _closure(obj, data, _closureData);
        }

    protected:
        virtual bool equals (EventHandlerBase* other) const
        {
            ClosureHandler<InterfaceType, DataType, ClosureDataType>* f = static_cast< ClosureHandler<InterfaceType, DataType, ClosureDataType>* >(other);
            return f != NULL && f->_closure == _closure && f->_closureData == _closureData;
        }

    private:
        Closure _closure;
        ClosureDataType _closureData;
    };

    template <class InterfaceType, class DataType, class ObjectType>
    class MethodHandler : public EventHandler<InterfaceType, DataType>
    {
    public:
        typedef void (ObjectType::*Method) (InterfaceType obj, DataType data);

        MethodHandler (ObjectType* obj, Method method)
            : _obj(obj), _method(method)
        {
        }

        virtual void operator () (InterfaceType obj, DataType data)
        {
            (_obj->*_method)(obj, data);
        }

    protected:
        virtual bool equals (EventHandlerBase* other) const
        {
            MethodHandler<InterfaceType, DataType, ObjectType>* f = static_cast< MethodHandler<InterfaceType, DataType, ObjectType>* >(other);
            return f != NULL && f->_obj == _obj && f->_method == _method;
        }

    private:
        ObjectType* _obj;
        Method _method;
    };

    template <class InterfaceType, class DataType, class ObjectType, class MethodType>
    class GenericMethodHandler : public EventHandler<InterfaceType, DataType>
    {
    public:
        typedef MethodType Method;

    protected:
        ObjectType* _obj;
        Method _method;

        GenericMethodHandler (ObjectType* obj, Method method)
            : _obj(obj), _method(method)
        {
        }

        virtual bool equals (EventHandlerBase* other) const
        {
            GenericMethodHandler<InterfaceType, DataType, ObjectType, MethodType>* f = static_cast< GenericMethodHandler<InterfaceType, DataType, ObjectType, MethodType>* >(other);
            return f != NULL && f->_obj == _obj && f->_method == _method;
        }
    };
}

#endif

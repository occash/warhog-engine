/*********************************************************************
    This file is part of the uMOF library.
    Copyright (C) 2014 Artem Shal
    artiom.shal@gmail.com

    The uMOF library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
    USA.
**********************************************************************/

#ifndef METHOD_H
#define METHOD_H

#include "defines.h"
#include "conststring.h"
#include "any.h"
#include "type.h"

#include <string>

class Object;

/*  \brief Internal struct to store method meta information.
*/
struct MethodTable
{
    ConstString name;
    InvokeMem invoker;
    int argc;
    const TypeTable **types;
};

/*! \brief The Method class provides meta information for method.
*/
class UMOF_EXPORT Method
{
public:
    /*! \brief Constructs a Method with the given table.
        Method constructor should never be used directly.
        Please use METHOD() or OVERLOAD() macros instead.
    */
    Method(const MethodTable *table);

    /*! Checks whether Method is valid object.
        Call to invalid method will result in application crash.
    */
    bool valid() const;

    /*! Returns the name of the method.
        \sa signature()
    */
    ConstString name() const;

    /*! Returns the signature of the method.
        The signature returned in normalized form. This means
        there is no whitespace between parameters and parameter
        names described as typeid().name().
        \sa name()
    */
    std::string signature() const;

    /*! Returns the return type of this method.
    */
    Type returnType() const;

    /*! Returns the number of arguments.
    */
    int parameterCount() const;

    /*! Returns the type of the argument at given index.
    */
    Type parmaeterType(int index) const;
    //ConstString parameterName(int index) const; //Not supported

    /*! Invokes the method with given args.
    */
    Any invoke(Object *obj, int argc, const Any *args) const;

    /*! Invokes the method with given args.
    */
    Any invoke(Object *obj, std::initializer_list<Any> args) const;

private:
    const MethodTable *_table;

};

#endif
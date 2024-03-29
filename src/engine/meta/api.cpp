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

#include "api.h"
#include "object.h"

#include <cstring>

Api::Api(const ApiTable *table) :
    _table(table)
{
}

ConstString Api::name() const
{
    return _table->name;
}

const Api *Api::super() const
{
    return _table->super;
}

int Api::indexOfMethod(const char *signature) const
{
    const Api *s = this;
    std::string sig = signature;

    while (s)
    {
        for (int i = 0; i < s->_table->methodCount; ++i)
            if (Method(_table->methods + i).signature() == signature)
                return i + s->methodOffset();

        s = s->_table->super;
    }

    return -1;
}

Method Api::method(int index) const
{
    int i = index - methodOffset();
    if (i < 0 && _table->super)
        return _table->super->method(index);

    if (i >= 0 && i < _table->methodCount)
        return Method(_table->methods + index);

    return Method(nullptr);
}

int Api::methodCount() const
{
    int count = _table->methodCount;
    const Api *s = _table-> super;
    while (s)
    {
        count += s->_table->methodCount;
        s = s->_table->super;
    }
    return count;
}

int Api::methodOffset() const
{
    int offset = 0;
    const Api *s = _table->super;
    while (s)
    {
        offset += s->_table->methodCount;
        s = s->_table->super;
    }
    return offset;
}

int Api::indexOfProperty(const char *name) const
{
    const Api *s = this;

    while (s)
    {
        for (int i = 0; i < s->_table->propCount; ++i)
            if (std::strcmp(s->_table->props[i].name, name) == 0)
                return i + propertyOffset();

        s = s->_table->super;
    }

    return -1;
}

Property Api::property(int index) const
{
    int i = index - propertyOffset();
    if (i < 0 && _table->super)
        return _table->super->property(index);

    if (i >= 0 && i < _table->propCount)
        return Property(_table->props + index);

    return Property(nullptr);
}

int Api::propertyCount() const
{
    int count = _table->propCount;
    const Api *s = _table->super;
    while (s)
    {
        count += s->_table->propCount;
        s = s->_table->super;
    }
    return count;
}

int Api::propertyOffset() const
{
    int offset = 0;
    const Api *s = _table->super;
    while (s)
    {
        offset += s->_table->propCount;
        s = s->_table->super;
    }
    return offset;
}

Any Api::invoke(Object *obj, const char *name, std::initializer_list<Any> args)
{
    const Api *api = obj->api();

    std::string sig(name);
    sig += '(';
    for (Any arg : args)
    {
        sig += arg.type().id().name();
        sig += ',';
    }
    if (args.size() > 0)
        sig[sig.size() - 1] = ')';
    else
        sig += ')';

    int index = api->indexOfMethod(sig.c_str());
    if (index >= 0)
        throw std::runtime_error("No such method");

    Method m = api->method(index);
    return m.invoke(obj, args.size(), args.begin());

    //TODO try to convert parameters
    /*  Method func = api->method(sig.c_str());
        if (func.valid())
        return func.invoke(obj, args);

        auto mrange = api->data.methods.equal_range(name);
        auto m = api->data.methods.end();
        int conform = std::numeric_limits<int>::min();
        for (auto i = mrange.first; i != mrange.second; ++i)
        {
        int a = 0;
        int c = -args.size();
        for (auto type : (*i).second.data.types)
        {
            if (type.checker(args[a]))
            {
                c++;
                if (type.id == args[a].type())
                    c++;
            }
            a++;
        }

        if (c >= 0 && c > conform)
        {
            conform = c;
            m = i;
        }
        }

        if (m != api->data.methods.end())
        {
        ArgPack newArgs(args.size());
        int a = 0;
        for (auto type : (*m).second.data.types)
        {
            newArgs[a] = type.converter(args[a]);
            a++;
        }

        return (*m).second.invoke(obj, newArgs);
        }*/
}

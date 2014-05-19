#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>
#include <boost/any.hpp>

class Settings
{
public:
    typedef std::map<std::string, boost::any> SettingsMap;

    enum Format
    {
        Yaml,
        Json,
        Xml,
        Ini,
        User
    };

    Settings(std::string filename, Format format);
    virtual ~Settings();

private:
    std::string _filename;
    Format _format;
    SettingsMap _setmap;

};

#endif

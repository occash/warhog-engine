#ifndef FILERESOURCEMETA_H
#define FILERESOURCEMETA_H

#include <memory>
#include <string>
#include "global.h"

class ResourceNode;
class ResourceIO;

class ENGINE_EXPORT FileResourceMeta
{
public:
    FileResourceMeta(ResourceIO *io);
    ~FileResourceMeta();

    bool readTree(const std::string& meta, ResourceNode *&root);
    bool writeTree(const std::string& meta, ResourceNode *root);

private:
    ResourceIO *_io;
    std::string _metafile;

};

#endif
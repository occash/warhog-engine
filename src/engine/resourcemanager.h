#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <fstream>

#include "tree.h"
#include "resource.h"

class ResourceIO;
class ResourceNode;

/*! \brief The ResourceManager class allows engine to manage assests
*/
class ENGINE_EXPORT ResourceManager
{
public:
    ResourceManager(std::shared_ptr<ResourceIO> io);
    ~ResourceManager();

    void setBasePath(const std::string& path);
    std::string basePath() const;

    /*! \brief Add resource loader to manager

        Use addLoader(Args... args) for convinience. It will create
        loader automatically.

        \param loader Pointer to existing resource loader
        \sa addLoader(Args... args)
        \sa BaseResource
        \sa Resource
    */
    void addLoader(std::shared_ptr<BaseResource> loader);
    void removeLoader(std::shared_ptr<BaseResource> loader);

    /*! \brief Load resource with given id
    */
    std::shared_ptr<Object> load(const std::string& id);

    /*! \brief Save resource to abstract storage

        Use this function to store the resource.
        You should explicitly set resource type.
        If you want the manager to guess the type
        use save(const std::string& id, std::shared_ptr<T> object)
        for convenience.

        \warning Groups not created automatically

        \param id Resource identifier
        \param type Resource type
        \sa load
        \sa ResourceIO
    */
    bool save(const std::string& id, std::shared_ptr<Object> object);

    /*! \brief Returns resource group by id

        If id is empty method will return root group.

        \param id Resource group id
        \sa root()
    */
    //const ResourceGroup *group(const std::string& id = std::string()) const;

    /*! \brief Returns root resource group

        Same as group("").

        \sa group()
    */
    const ResourceNode *root() const;

    /*! \brief Creates new group

        It also creates all subgroups if required.

        \param id Full path for group
        \sa group()
    */
    bool createGroup(const std::string& id);

    bool createHandle(BaseResource::Type type, const std::string& id);

    /*! \brief Removes group and all resources assotiated with it

        \param id Full path for group

        \sa group()
    */
    bool deleteNode(const std::string& id);

    bool renameNode(const std::string& id, const std::string& name);

    template<typename T, typename... Args>
    void addLoader(Args... args)
    {
        addLoader(std::make_shared<T>(args...));
    }

    template<typename T>
    std::shared_ptr<T> load(const std::string& id)
    {
        return std::dynamic_pointer_cast<T>(load(id));
    }
    template<typename T>
    bool save(const std::string& id, std::shared_ptr<T> object)
    {
        return save(id, object, Resource<T>::staticType());
    }

private:
    typedef std::map<BaseResource::Type, std::shared_ptr<BaseResource>> LoaderMap;
    //typedef std::map<std::string, std::shared_ptr<BaseResource>> ResourceCache;

    std::shared_ptr<ResourceIO> _io;
    LoaderMap _loaders;
    //ResourceCache _cache;
    //tree<std::shared_ptr<Resource>> _resourceTree;
};

#endif
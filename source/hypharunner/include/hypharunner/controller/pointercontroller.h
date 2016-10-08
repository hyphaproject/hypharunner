// Copyright (c) 2016 Hypha

#ifndef POINTERCONTROLLER_H
#define POINTERCONTROLLER_H

#include <hypha/core/cache/cache.h>

class PointerController
{
public:
    static PointerController *instance();

    /**
     * @brief put
     * @param key
     * @param data
     */
    void put(std::string &key, std::string data);

    /**
     * @brief put
     * stores data by newly generated key. Key starts with hostname and ':' followed by UUID.
     * @param data to put
     * @return the generated key
     */
    std::string put(std::string data);
    /**
     * @brief get
     * @param key
     * @return
     */
    std::string get(std::string &key);

    static std::string getHostname(std::string &key);
    static std::string getUUID(std::string &key);

private:
    PointerController();
    static PointerController *singleton;
    hypha::cache::Cache cache;
};

#endif // POINTERCONTROLLER_H

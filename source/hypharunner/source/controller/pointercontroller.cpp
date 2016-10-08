// Copyright (c) 2016 Hypha

#include "hypharunner/controller/pointercontroller.h"

#include <mutex>

#include <Poco/Net/DNS.h>
#include <Poco/UUIDGenerator.h>

PointerController *PointerController::singleton = nullptr;

PointerController *PointerController::instance()
{
    static std::mutex mutex;
    if (!singleton) {
      mutex.lock();

      if (!singleton) singleton = new PointerController();
      mutex.unlock();
    }

    return singleton;
}

void PointerController::put(std::string &key, std::string data)
{
    cache.put(key, data);
}

std::string PointerController::put(std::string data)
{
    Poco::UUIDGenerator generator;
    std::string key = Poco::Net::DNS::hostName() + ":" + generator.createOne().toString();
    put(key, data);
    return key;
}

std::string PointerController::get(std::string &key)
{
    return cache.get(key);
}

std::string PointerController::getHostname(std::string &key)
{
    int pos = key.find(':');
    return key.substr(0, pos);
}

std::string PointerController::getUUID(std::string &key)
{
    int pos = key.find(':');
    return key.substr(pos, key.size() - pos);
}

PointerController::PointerController()
{
    cache.connect();
}

//
// Created by hua on 2024/9/9.
//

#include "config.h"

Config::Config() : QObject() {

}

Config::Config(const Config& other) : downloadPath(other.downloadPath) {}

const string &Config::getAppsUrl() const {
    return appsUrl;
}

void Config::setAppsUrl(const string &appsUrl) {
    Config::appsUrl = appsUrl;
}

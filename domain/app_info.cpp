//
// Created by hua on 2024/9/6.
//

#include "app_info.h"

const string &AppInfo::getName() const {
    return name;
}

void AppInfo::setName(const string &name) {
    AppInfo::name = name;
}

const string &AppInfo::getDescription() const {
    return description;
}

void AppInfo::setDescription(const string &description) {
    AppInfo::description = description;
}

const string &AppInfo::getLogoUrl() const {
    return logoUrl;
}

void AppInfo::setLogoUrl(const string &logoUrl) {
    AppInfo::logoUrl = logoUrl;
}

const string &AppInfo::getWebUrl() const {
    return webUrl;
}

void AppInfo::setWebUrl(const string &webUrl) {
    AppInfo::webUrl = webUrl;
}

const string &AppInfo::getCategory() const {
    return category;
}

void AppInfo::setCategory(const string &category) {
    AppInfo::category = category;
}

const map<string, string> &AppInfo::getWindowsUrl() const {
    return windowsUrl;
}

void AppInfo::setWindowsUrl(const map<string, string> &windowsUrl) {
    AppInfo::windowsUrl = windowsUrl;
}

const map<string, string> &AppInfo::getLinuxUrl() const {
    return linuxUrl;
}

void AppInfo::setLinuxUrl(const map<string, string> &linuxUrl) {
    AppInfo::linuxUrl = linuxUrl;
}

const map<string, string> &AppInfo::getMacOsUrl() const {
    return macOSUrl;
}

void AppInfo::setMacOsUrl(const map<string, string> &macOsUrl) {
    macOSUrl = macOsUrl;
}

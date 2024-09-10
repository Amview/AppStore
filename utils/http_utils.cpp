//
// Created by hua on 2024/9/8.
//

#include "http_utils.h"
#include "config_utils.h"
#include <httplib.h>
#include <fstream>
#include <QMessageBox>
#include "string_utils.h"
#include <iostream>
#include <thread>
#include <future>
using namespace std;
HttpUtils::HttpUtils() : QObject(){

}

void HttpUtils::download(const string &url, httplib::Progress process) {
    HttpUtils::UrlPart urlPart = analyseUrl(url);
    httplib::Client cli(urlPart.host);
    httplib::Result result;
    try {
        result = cli.Get(urlPart.path, process);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        QMessageBox::warning(nullptr, tr("Open Directory"),
                             tr("Could not open directory"));
    }
    if (result->status == 302 || result->status == 301) {
        string location = result->get_header_value("Location", 0);
        if (!location.empty()) {
            download(location, process);
        }
    } else if (result && result->status == 200) {
        string file_path = ConfigUtils::readConfig().getDownloadPath() + "/" + urlPart.lastPart;
        cout << "下载路径："  << file_path;
        std::ofstream file(file_path, std::ios::binary);
        file.write(result->body.data(), result->body.size());
        std::cout << "下载完成：" << url <<  std::endl;
        file.close();
    } else {
        std::cerr << "Failed to download file. Status code: " <<
        (result ? std::to_string(result->status) : "N/A") << std::endl;
    }
}

HttpUtils::UrlPart HttpUtils::analyseUrl(const string& url) {
    HttpUtils::UrlPart urlPart;
    vector<string> parts = StringUtils::splitStr(url, "/");
    vector<string> temp;
    for (int i = 0; i < parts.size(); ++i) {
        temp.push_back(parts[i]);
        if (i == 2) {
            urlPart.host = accumulate(temp.begin(), temp.end(), urlPart.host);
        }
        if (i == parts.size() - 2) {
//            urlPart.urlExcludeLastPart = accumulate(temp.begin(), temp.end(), urlPart.urlExcludeLastPart);
        }
        if (i != parts.size() - 1) {
            temp.push_back("/");
        }
    }
    urlPart.path = accumulate(temp.begin() + 5, temp.end(), urlPart.path);
    urlPart.lastPart = parts[parts.size() - 1];
    return urlPart;

}


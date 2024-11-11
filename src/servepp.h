// httpp.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fmt/core.h>
#include <string>
#include <string_view>
#include <curl/curl.h>
#include <map>
#include <algorithm>
#include <format>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>

namespace servepp
{   
    void init_server(std::string_view& address, int port);
}


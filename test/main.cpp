#include <fmt/core.h>
#include "servepp.h"
#include <fstream>

using namespace servepp;

int main()
{

    int port = 8801;

    Server server;
    // char* message;

    server.init_server("127.0.0.1", port);

    fmt::println("The message: \n{}", (char *)R"(
        HTTP/1.1 200 OK\r\n
        Content-Type: text/html\r\n
        Connection: close\r\n
        \r\n
        <p>Hello, world!</p>
        )");

    while (true)
    {
        server.listen_server();

        server.send_buffer((char *)R"(
        HTTP/1.1 200 OK\r\n
        Content-Type: text/html\r\n
        Connection: close\r\n
        \r\n
        <p>Hello, world!</p>
        )");

        // message = (char*)"";
        // server.recieve_buffer(message);
        // if (strlen(message) != 0) {
        //     fmt::println("Client: {}", message);
        // }
    }

    return 0;
}
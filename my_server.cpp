
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main() 
{

    int server_port = 5000;
    int buffer_size = 2048;
    char buffer[buffer_size];
    long int counter_read_success = 0;
    long int counter_read_failure = 0;    

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        cout << "Socket creation error" << endl;
        exit(EXIT_FAILURE);
    }
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int binding_status = bind(socket_fd, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address));
    if (binding_status == -1)
    {
        cout << "Socket binding error" << endl;
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    cout << "Start server listening UDP on " << "127.0.0.1:"<< server_port << endl;
    cout << "Press Ctrl+C to stop." << endl;

    while (errno != EINTR)
    {
        long int number_bytes_read = recvfrom(socket_fd, buffer, sizeof(buffer), 0, nullptr, nullptr);
        if (number_bytes_read == -1)
        {
            counter_read_failure++;
        }
        else
        {
            counter_read_success++;
            std::printf("\rReceived packets: %lu", counter_read_success);
            std::fflush(stdout);   
        }
    }

    close(socket_fd);
    return EXIT_SUCCESS;
}


#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

//#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
    int port_destination = 5000;
    int packets_to_send = 1000;
    int packet_size = 32;

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        cout << "Socket creation error" << endl;
        exit(EXIT_FAILURE);
    }
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port_destination);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //char packet[packet_size]{};
    char packet[packet_size] = "1234123412341234123412341234123";
    int counter_packets_sent = 0;

    for (int i = 0; i < packets_to_send; i++)
    {
        usleep(10000);
        long int number_bytes_sent = sendto(socket_fd, packet, sizeof(packet), 0, reinterpret_cast<sockaddr*>(&server), sizeof(server));

        if (number_bytes_sent == -1)
        {
            cout << "Packet sending error" << endl;
            close(socket_fd);
            exit(EXIT_FAILURE);
        }
        counter_packets_sent++;
    }

    cout << "Sent " << counter_packets_sent << " UDP packets." << endl;
    close(socket_fd);
    return EXIT_SUCCESS;
}

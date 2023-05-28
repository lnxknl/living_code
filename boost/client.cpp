#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_service io_service;

        tcp::socket socket(io_service);
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8888));

        std::cout << "Connected to server." << std::endl;

        while (true) {
            std::string message;
            std::getline(std::cin, message);

            boost::asio::write(socket, boost::asio::buffer(message + "\n"));

            boost::system::error_code error;
            char response[1024];
            size_t length = socket.read_some(boost::asio::buffer(response), error);
            if (error == boost::asio::error::eof) {
                std::cout << "Server closed the connection." << std::endl;
                break; // Connection closed cleanly by peer.
            } else if (error) {
                throw boost::system::system_error(error); // Some other error.
            }

            std::string response_message(response, length);
            std::cout << response_message << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

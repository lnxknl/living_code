#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_service io_service;

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8888));

        while (true) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::cout << "New client connected: " << socket.remote_endpoint() << std::endl;

            boost::system::error_code error;
            while (true) {
                char data[1024];
                size_t length = socket.read_some(boost::asio::buffer(data), error);
                if (error == boost::asio::error::eof) {
                    std::cout << "Client disconnected: " << socket.remote_endpoint() << std::endl;
                    break; // Connection closed cleanly by peer.
                } else if (error) {
                    throw boost::system::system_error(error); // Some other error.
                }

                std::string message(data, length);
                std::cout << "Received message from " << socket.remote_endpoint() << ": " << message << std::endl;

                boost::asio::write(socket, boost::asio::buffer("You said: " + message));
            }
        }
    } catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

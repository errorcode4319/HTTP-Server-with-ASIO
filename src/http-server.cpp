#include"http-server.h"

namespace http {

	HttpServer::HttpServer(uint16_t port/*=8080*/) : 
		mAsioAcceptor(
			mAsioCtx, boost::asio::ip::tcp::endpoint(
				boost::asio::ip::tcp::v4(), port))	{

	}

	HttpServer::~HttpServer() {
		stop();
	}

	int HttpServer::start() {
		try {
			wait_request();
			mThreadCtx = std::thread([&]() {mAsioCtx.run(); });
			std::cout << "Server Started!" << std::endl;
		}
		catch (std::exception& e) {
			std::cerr << "Server Start Failed => " << e.what() << std::endl;
			return -1;
		}
		return 0;
	}

	int HttpServer::stop() {
		mAsioCtx.stop();
		if (mThreadCtx.joinable())
			mThreadCtx.join();
		std::cout << "Server Stopped" << std::endl;
		return 0;
	}

	void HttpServer::wait_request() {
		mAsioAcceptor.async_accept(
			[this](std::error_code err, boost::asio::ip::tcp::socket sock) {
				if (!err) {
					std::cout << "Get Request => " << sock.remote_endpoint() << std::endl;
					sock.close();
				}
				else {
					std::cerr << "Accept New Client Failed => " << err.message() << std::endl;
				}
				wait_request();
			}
		);
	}

}
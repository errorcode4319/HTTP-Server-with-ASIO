#ifndef __HTTP_SERVER_H
#define __HTTP_SERVER_H

#include<iostream>
#include<thread>
#include<cstdint>
#include<utility>
#include<functional>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif 

#include<boost/asio.hpp>
#include<boost/asio/ts/buffer.hpp>
#include<boost/asio/ts/internet.hpp>

namespace http {

	class HttpServer {
	public:
		HttpServer(uint16_t port=8080);
		~HttpServer();

		int start();
		int stop();

	private:
		void wait_request();

		boost::asio::io_context			mAsioCtx;
		boost::asio::ip::tcp::acceptor	mAsioAcceptor;
		std::thread						mThreadCtx;

	};

}


#endif // __HTTP_SERVER_H
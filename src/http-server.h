#ifndef __HTTP_SERVER_H
#define __HTTP_SERVER_H

#include "net-headers.h"
#include "http-request.h"
#include "http-router.h"

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

		HttpRouter						mRouter;
	};

}


#endif // __HTTP_SERVER_H
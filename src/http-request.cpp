#include "http-request.h"

namespace http {


	HttpRequest::HttpRequest(boost::asio::io_context& asioCtx, boost::asio::ip::tcp::socket sock)
		: mrfAsioCtx(asioCtx), mSocket(std::move(sock)) {

	}

	HttpRequest::~HttpRequest() {
		if (mSocket.is_open())
			mSocket.close();
	}

	int HttpRequest::load_request() {


		return 0;
	}

}
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
		if (!mSocket.is_open()) {
			return -1;
		}
		std::string buf;
		buf.resize(MAX_REQ_LENGTH);
		boost::system::error_code ec;
		mSocket.read_some(boost::asio::buffer(buf.data(), buf.size()), ec);
		std::cout << buf;

		if (!parseRequest(buf)) {
			std::cerr << "Invalid HTTP Request" << std::endl;
			return -1;
		}

		std::cout << "Target URL => " << mTarget << std::endl;
		std::cout << "Target Method => " << mMethod << std::endl;
		return 0;
	}

	bool HttpRequest::parseRequest(const std::string& raw) {

		auto startLine = raw.substr(0, raw.find("\r\n"));
		mTarget = [&]() -> std::string {
			std::string ret(startLine.c_str() + startLine.find(' ') + 1);
			ret = ret.substr(0, ret.find(' '));
			return std::string(ret);
		} ();
		mMethod = startLine.substr(0, startLine.find(' '));

		auto rawHeader = raw.substr(
			raw.find("\r\n") + 2,
			raw.find("\r\n\r\n") - raw.find("\r\n")
		);

		while (rawHeader.find("\r\n") != std::string::npos) {
			auto header_deli_iter = rawHeader.find("\r\n");
			auto key_value_deli_iter = rawHeader.find(':');

			auto header = rawHeader.substr(0, header_deli_iter);
			auto key = header.substr(0, key_value_deli_iter);
			auto value = header.substr(key_value_deli_iter + 1, header_deli_iter);
			while (value[0] == ' ') {
				value = value.substr(1);
			}
			mHeader[std::string(key)] = std::string(value);
			rawHeader = rawHeader.substr(header_deli_iter + 2);
		}
		mBody = raw.substr(raw.find("\r\n\r\n") + 4);

		return true;
	}

}
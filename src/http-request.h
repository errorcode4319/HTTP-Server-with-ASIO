#ifndef __HTTP_REQUEST_H
#define __HTTP_REQUEST_H

#include "net-headers.h"

namespace http {

	constexpr int MAX_REQ_LENGTH = 4096;

	class HttpRequest : 
		public std::enable_shared_from_this<HttpRequest> {

	public:
		HttpRequest(boost::asio::io_context& asioCtx, boost::asio::ip::tcp::socket sock);
		~HttpRequest();

		int load_request();

		std::string_view getTarget() const { return mTarget; }

		std::string_view getMethod() const { return mMethod; }

		std::string_view getHeaderProp(std::string_view key) const {
			if (auto iter = mHeader.find(key.data()); iter != std::end(mHeader)) {
				return iter->second;
			}
			return "";
		}

		const auto& getHeaders() const {
			return mHeader;
		}

	private:
		bool	parseRequest(const std::string& raw);

		std::string mTarget;
		std::string mMethod;
		std::unordered_map<std::string, std::string>	
					mHeader;
		std::string mBody;

	private:
		boost::asio::io_context& mrfAsioCtx;
		boost::asio::ip::tcp::socket mSocket;
	};

}


#endif // __HTTP_REQUEST_H
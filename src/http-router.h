#ifndef __HTTP_ROUTER_H
#define __HTTP_ROUTER_H

#include "net-headers.h"
#include "http-request.h"

namespace http {

	class HttpRouter {
	public:
		HttpRouter();
		~HttpRouter();

		int start(int numThreads);
		int stop();

		int route(std::string_view url, std::function<std::string()> func);

		void addRequest(std::shared_ptr<HttpRequest> req);

	private:

		void	worker_process(int tid);
		std::shared_ptr<HttpRequest> pullRequest();
		void	pushRequest(std::shared_ptr<HttpRequest> req);


		bool			mIsRunning = false;
		int				mNumThreads = 0;
		std::vector<std::thread>	mThreadPool;
		std::mutex					mWorkerMutex;
		std::condition_variable		mWorkerCV;

		std::mutex		mReqMutex;
		std::queue<std::shared_ptr<HttpRequest>>	mReqQueue;
		
		std::unordered_map<std::string, std::function<std::string()>> mRouteFunc;
	};

}

#endif // __HTTP_ROUTER_H
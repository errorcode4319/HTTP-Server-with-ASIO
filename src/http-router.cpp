#include "http-router.h"

#include<chrono>
using namespace std::chrono_literals;

namespace http {

	HttpRouter::HttpRouter() {

	}

	HttpRouter::~HttpRouter() {
		stop();
	}

	int HttpRouter::start(int numThreads) {
		if (mIsRunning) return -1;
		mIsRunning = true;
		mNumThreads = numThreads;

		mThreadPool.resize(numThreads);
		for (int i = 0; i < numThreads; i++) {
			mThreadPool[i] = std::thread{ &HttpRouter::worker_process, this, i };
		}

		return 0;
	}

	int HttpRouter::stop() {
		mIsRunning = false;
		for (int i = 0; i < mNumThreads; i++)
			if(mThreadPool[i].joinable())
				mThreadPool[i].join();
		return 0;
	}

	int HttpRouter::route(std::string_view url, std::function<std::string()> func) {


		return 0;
	}

	void HttpRouter::addRequest(std::shared_ptr<HttpRequest> req) {
		pushRequest(req);
		std::unique_lock lock(mWorkerMutex);
		mWorkerCV.notify_one();
	}

	void HttpRouter::worker_process(int tid) {

		while (mIsRunning) {
			{
				std::unique_lock lock(mWorkerMutex);
				mWorkerCV.wait_for(lock, 1000ms, [&]() {return !mReqQueue.empty(); });
				if (mIsRunning == false) return;
			}
			auto req = pullRequest();
			if (req == nullptr) continue;

			req->load_request();
			std::cout << "Request Target URL => " << req->getTarget() << std::endl;
			std::cout << "Request HTTP Method => " << req->getMethod() << std::endl;
		}

	}

	std::shared_ptr<HttpRequest> HttpRouter::pullRequest() {
		std::scoped_lock lock(mReqMutex);
		if (mReqQueue.empty()) return nullptr;
		auto req = std::move(mReqQueue.front());
		mReqQueue.pop();
		return req;
	}

	void HttpRouter::pushRequest(std::shared_ptr<HttpRequest> req) {
		std::scoped_lock lock(mReqMutex);
		mReqQueue.push(req);
	}



}
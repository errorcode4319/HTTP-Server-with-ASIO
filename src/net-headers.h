#ifndef __NET_HEADERS_H
#define __NET_HEADERS_H

#include<iostream>
#include<thread>
#include<cstdint>
#include<utility>
#include<queue>
#include<vector>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<unordered_map>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif 

#include<boost/asio.hpp>
#include<boost/asio/ts/buffer.hpp>
#include<boost/asio/ts/internet.hpp>

#endif // __NET_HEADERS_H
#include"http-server.h"

int main() {

	http::HttpServer server(8080);
	server.start();

	std::cout << "Press Any Key To Exit" << std::endl;

	std::string temp;
	std::getline(std::cin, temp);

	return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include "include/httplib.h"
#include <format>
#include <winsqlite/winsqlite3.h>


namespace Logger {
	static void Log(const std::string& msg) {
		printf("[SERVER] %s\n", msg.c_str());
	}
}


class WebServer {
private:
	httplib::Server m_server;
	std::string m_host;
	int m_port;


    static std::string readSite(const std::string & page_name) {
		std::stringstream s;
		std::string ss;
		//ss = std::format();


		s << "<html>\n"
		<< "<head>\n"
		<< "<title>Test</title>\n"
		<< "<link rel = \"stylesheet\" href=\"/styles/style.css\">\n"
		<< "<script type=\"text/javascript\" src=\"/js/script.js\"></script>\n"
		<< "</head>\n"

		<< "<body>\n"

		<< "<h1 onclick=\"change(this)\">Hello, world!</h1>\n"

		<< "</body>\n"
		<< "</html>";

		return s.str();
    }

public:
	static void index(const httplib::Request& req, httplib::Response& res) {
	

		res.set_content(WebServer::readSite("index"), "text/html");
	}

    WebServer (const std::string & host = "localhost", int port = 80):
		m_host(host), m_port(port) {
		Logger::Log("Init HOST: " + m_host + " PORT: " + std::to_string(m_port));


		//Mount Points
		m_server.set_mount_point("/styles/", "www/styles/");
		m_server.set_mount_point("/js/", "www/js/");


		//Get
		m_server.Get("/", index);
	}

	void launch() {
		Logger::Log("Start Listening");
		m_server.listen(m_host, m_port);

	}

	~WebServer() {
		Logger::Log("STOP");
	}

};

int main() {
	WebServer server("192.168.0.107");
	server.launch();
	return 0;
}
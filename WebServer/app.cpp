﻿#include <iostream>
#include "httplib.h"
namespace Logger {
	static void Log(const std::string& msg) {
		printf("[SERVER] %s\n", msg.c_str());
		return;
	}
}

class WebServer {
private:
	httplib::Server m_server;
	std::string m_host;
	int m_port;

public:
	static void index(const httplib::Request& req, httplib::Response& res) {
		std::string s = "<html><head><title>Test</title>";
		s += "<link rel = \"stylesheet\" href=\"/styles/style.css\">";
		s += "<script type=\"text/javascript\" src=\"/js/script.js\"></script>";
		s += "</head><body><h1 onclick=\"change(this)\" >Hello, world!</h1></body></html>";
		res.set_content(s, "text/html");
		return;
	}

	WebServer(std::string host = "localhost", int port = 80): 
		m_host(host), m_port(port) {
		Logger::Log("Init HOST: " + m_host + " PORT: " + std::to_string(m_port));
		m_server.set_mount_point("/styles/", "www/styles/");
		m_server.set_mount_point("/js/", "www/js/");
		m_server.Get("/", index);
	}

	void launch() {
		Logger::Log("Start Listening HOST: " + m_host + " PORT: " + std::to_string(m_port));
		m_server.listen(m_host, m_port);

	}

	~WebServer() {
		Logger::Log("STOP");
	}

};


int main() {
	WebServer server("localhost");
	server.launch();
	return 0;
}
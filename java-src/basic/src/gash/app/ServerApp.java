package gash.app;

import gash.socket.BasicServer;

/**
 * server application
 * 
 * @author gash
 * 
 */
class ServerApp {
	public ServerApp() {
	}

	public static void javaServer(String[] args) {
		var host = "127.0.0.1";
		var port = 3000;
		var server = new BasicServer(host,port);
		server.start();
	}

	public static void main(String[] args) {
		javaServer(args);
	}
}

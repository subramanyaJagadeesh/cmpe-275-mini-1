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

	public static void cppServer(String[] args) {
		var host = "127.0.0.1";
		var port = 2000;
		var server = new BasicServer(host,port);
		server.start();
	}

	public static void pythonServer(String[] args) {
		var host = "127.0.0.1";
		var port = 4000;
		var server = new BasicServer(host,port);
		server.start();
	}

	public static void main(String[] args) {

		//javaServer();
		//pythonServer();
		//cppServer();
		ServerApp.javaServer(args);
		ServerApp.cppServer(args);
  		ServerApp.pythonServer(args);
  		

	}
}

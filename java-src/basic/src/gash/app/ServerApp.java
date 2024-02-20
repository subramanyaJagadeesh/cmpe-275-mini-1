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
     
	/*public void javaServer(String[] args) {
		var host = "127.0.0.1";
		var port = 2000;
		var server = new BasicServer(host,port);
		server.start();
	}

	public void  CppServer(String[] args) {
		var host = "127.0.0.1";
		var port = 3000;
		var server = new BasicServer(host,port);
		server.start();
	}

	public static void main(String[] args) {

	}*/
	public static void main(String[] args) {
		var host = "127.0.0.1";
		var port1 = 2000;
		var serverJava = new BasicServer(host,port1);
		serverJava.start();

		var port2 = 3000;
		var serverCpp = new BasicServer(host,port2);
		serverCpp.start();
	}
}



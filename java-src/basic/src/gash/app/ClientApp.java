package gash.app;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import gash.socket.BasicClient;

/**
 * client - basic chat construct. This varies from our Python and C++ versions
 * as it prompts the use for messages.
 * 
 * @author gash
 * 
 */
public class ClientApp {
	private BasicClient myClient;

	public ClientApp() {
	}

	public static void sendToJava(){
		var javaClient = new BasicClient("app", "127.0.0.1", 3000);
		javaClient.connect();
		javaClient.join("pets/dogs");
		javaClient.sendMessage("My name is inigo montoya");
	}

	public static void sendToCPP(){
		var cppClient = new BasicClient("app", "127.0.0.1", 2000);
		cppClient.connect();
		cppClient.join("pets/dogs");
		cppClient.sendMessage("My name is inigo montoya");
	}

	public static void sendToPython(){
		var pythonClient = new BasicClient("app", "127.0.0.1", 4000);
		pythonClient.connect();
		pythonClient.join("pets/dogs");
		pythonClient.sendMessage("My name is inigo montoya");
	}

	public static void main(String[] args) {
		sendToJava();
		sendToPython();
		sendToCPP();
	}
}

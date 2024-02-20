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

		var br = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			try {
				System.out.print("\nenter message ('exit' to quit): ");
				var m = br.readLine();
				if (m.length() == 0 || "exit".equalsIgnoreCase(m))
					break;

				javaClient.sendMessage(m);
			} catch (Exception ex) {
				break;
			}
		}
	}

	public static void sendToCPP(){
		var javaClient = new BasicClient("app", "127.0.0.1", 2000);
		javaClient.connect();
		javaClient.join("pets/dogs");

		var br = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			try {
				System.out.print("\nenter message ('exit' to quit): ");
				var m = br.readLine();
				if (m.length() == 0 || "exit".equalsIgnoreCase(m))
					break;

				javaClient.sendMessage(m);
			} catch (Exception ex) {
				break;
			}
		}
	}

	public static void sendToPython(){
		var javaClient = new BasicClient("app", "127.0.0.1", 4000);
		javaClient.connect();
		javaClient.join("pets/dogs");

		var br = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			try {
				System.out.print("\nenter message ('exit' to quit): ");
				var m = br.readLine();
				if (m.length() == 0 || "exit".equalsIgnoreCase(m))
					break;

				javaClient.sendMessage(m);
			} catch (Exception ex) {
				break;
			}
		}
	}

	public static void main(String[] args) {
		sendToJava();
		sendToPython();
	}
}
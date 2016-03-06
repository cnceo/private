package vliu.websocket;

import java.io.IOException;
import java.io.InputStreamReader;
import javax.websocket.DeploymentException;

import org.glassfish.tyrus.server.Server;

public class Main {
	public static void main(String[] args) {
		String host="localhost";
		int port=8080;
		Server server=new Server(host,port,"",null,ServerEP.class);
		System.out.println("server started on "+host+":"+port);

		InputStreamReader ir=new InputStreamReader(System.in);
		try {
			server.start();
			while('x'!=ir.read()){}
			server.stop();
			System.out.println("server stopped");
		} catch (DeploymentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (Exception e){
			e.printStackTrace();
		}
		System.out.println("exit");
	}
}
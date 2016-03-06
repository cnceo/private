package vliu.websocket;

import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URI;
import javax.websocket.ContainerProvider;
import javax.websocket.DeploymentException;
import javax.websocket.Session;
import javax.websocket.WebSocketContainer;

public class Main {
	public static void main(String[] args) {
		String strUrl="ws://localhost:8080/game/123456";
		URI uri=URI.create(strUrl);
		Session session=null;
		try {
			WebSocketContainer container=ContainerProvider.getWebSocketContainer();
			System.out.println("connecting to "+strUrl);
			session=container.connectToServer(ClientEP.class,uri);
		} catch (DeploymentException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		InputStreamReader ir=new InputStreamReader(System.in);
		try {
			while('x'!=ir.read()){}
			session.close();
			System.out.println("closed");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("exit");
	}
}
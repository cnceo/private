package vliu.websocket;
import java.io.IOException;

import javax.websocket.*;
// dependencies: tyrus-standalone-client-1.11.jar
@ClientEndpoint
public class ClientEP {

	@OnOpen
	public void onOpen(Session session,EndpointConfig conf){
		System.out.println("on open");
		String msg="hello server";
		System.out.println("send: "+msg);
		try {
			session.getBasicRemote().sendText(msg);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	@OnClose
	public void onClose(Session session,CloseReason reason){
		System.out.println("on close "+reason.getReasonPhrase());
	}

	@OnError
	public void onError(Session session,Throwable error){
		error.printStackTrace();
	}

	@OnMessage
	public void onMessage(Session session,String msg){
		System.out.println("received: "+msg);
	}
}

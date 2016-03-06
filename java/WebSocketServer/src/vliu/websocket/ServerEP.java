package vliu.websocket;
import java.io.IOException;

import javax.websocket.*;
import javax.websocket.server.*;
/* dependencies:
 * tyrus-container-grizzly-server-1.11.jar
 * tyrus-server-1.11.jar
 * tyrus-standalone-client-1.11.jar
 */
@ServerEndpoint(value="/game/{playerId}")
public class ServerEP {

	@OnOpen
	public void onOpen(Session session,EndpointConfig conf,@PathParam("playerId")long playerId){
		System.out.println("on open");
	}
	
	@OnClose
	public void onClose(Session session,CloseReason reson,@PathParam("playerId")long playerId){
		System.out.println("on close");
	}

	@OnError
	public void onError(Session session,Throwable error,@PathParam("playerId")long playerId){
		error.printStackTrace();
	}

	@OnMessage
	public void onMessage(Session session,String msg,@PathParam("playerId")long playerId){
		System.out.println("received: "+msg);
		try {
			msg="hello client";
			session.getBasicRemote().sendText(msg);
			//or send binary
			//session.getBasicRemote().sendBinary(ByteBuffer.wrap(msg.getBytes()));
			System.out.println("send: "+msg);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}

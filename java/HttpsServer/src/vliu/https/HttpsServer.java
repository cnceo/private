package vliu.https;

import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpsServer {
	int HTTPS_PORT=8080;//443
	public static String WEB_ROOT=System.getProperty("user.dir")+File.separator+"webroot";
	
	public static void main(String[]args){
		HttpsServer server=new HttpsServer();
		if(server!=null)
			server.run();
	}
	
	public void run(){
		try{
			SSLServer server=new TrustServer();
			ServerSocket serverSocket=server.serverSocket();
			System.out.println("server started at "+serverSocket.getInetAddress().toString()+":"+HTTPS_PORT);
			while(true){
				try{
					Socket client=serverSocket.accept();
					new SocketHandler(client);
				}catch(IOException e){
					e.printStackTrace();
				}
			}
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("server exit");
			System.exit(1);
		}
	}
}

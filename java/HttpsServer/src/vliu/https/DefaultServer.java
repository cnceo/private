package vliu.https;

import java.io.IOException;
import java.net.ServerSocket;

import javax.net.ssl.SSLServerSocketFactory;

public class DefaultServer extends SSLServer{
	public ServerSocket serverSocket()throws Exception{
		ServerSocket serverSocket=null;
		try{
			SSLServerSocketFactory ssf=(SSLServerSocketFactory)SSLServerSocketFactory.getDefault();
			int port=Integer.valueOf(Configuration.getConfig().getProperty("serverListenPort"));
			serverSocket=ssf.createServerSocket(port);
		}catch(IOException e){
			throw e;
		}
		return serverSocket;
	}
}

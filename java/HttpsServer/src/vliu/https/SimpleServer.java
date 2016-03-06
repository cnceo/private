package vliu.https;

import java.io.FileInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.security.KeyStore;

import javax.net.ServerSocketFactory;
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;

public class SimpleServer extends SSLServer{
	public ServerSocket serverSocket()throws Exception{
		ServerSocket serverSocket=null;
		try{
			String keystore="serverKeystore";
			char keystorepass[]="123456".toCharArray();
			char keypassword[]="123456".toCharArray();
			KeyStore ks=KeyStore.getInstance("JKS");
			ks.load(new FileInputStream(keystore), keystorepass);
			
			KeyManagerFactory kmf=KeyManagerFactory.getInstance("SunX509");
			kmf.init(ks, keypassword);
			SSLContext sslcontext=SSLContext.getInstance("TLSv1.2");
			sslcontext.init(kmf.getKeyManagers(), null, null);
			ServerSocketFactory ssf=sslcontext.getServerSocketFactory();
			int port=Integer.valueOf(Configuration.getConfig().getProperty("serverListenPort"));
			serverSocket=ssf.createServerSocket(port);
		}catch(IOException e){
			throw e;
		}
		return serverSocket;
	}
}

package vliu.https;

import java.io.FileInputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.security.KeyStore;
import java.util.Properties;

import javax.net.ssl.KeyManager;
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLServerSocketFactory;
import javax.net.ssl.TrustManager;
import javax.net.ssl.TrustManagerFactory;

public class TrustServer extends SSLServer{
	public ServerSocket serverSocket()throws Exception{
		Properties p = Configuration.getConfig();
		Integer serverListenPort = Integer.valueOf(p.getProperty("serverListenPort"));
		Integer serverRequestQueueSize = Integer.valueOf(p.getProperty("serverRequestQueueSize"));
		Integer authority = Integer.valueOf(p.getProperty("authority"));
		
		String protocol = p.getProperty("protocol");
		String serverCer = p.getProperty("serverCer");
		String serverCerPwd = p.getProperty("serverCerPwd");
		String serverKeyPwd = p.getProperty("serverKeyPwd");
		
		//Key Stroe
		KeyStore keyStore = KeyStore.getInstance("JKS");  
		keyStore.load(new FileInputStream(serverCer), 
				serverCerPwd.toCharArray());  
		
		KeyManagerFactory keyManagerFactory = KeyManagerFactory.getInstance("SunX509"); 
		keyManagerFactory.init(keyStore, serverKeyPwd.toCharArray()); 
		KeyManager[] kms = keyManagerFactory.getKeyManagers();
		
		TrustManager[] tms = null;
		if(Configuration.getConfig().getProperty("authority").equals("2")){
			String serverTrustCer = p.getProperty("serverTrustCer");
			String serverTrustCerPwd = p.getProperty("serverTrustCerPwd");
			
			//Trust Key Store
			keyStore = KeyStore.getInstance("JKS");  
			keyStore.load(new FileInputStream(serverTrustCer), 
					serverTrustCerPwd.toCharArray());  
			
			TrustManagerFactory trustManagerFactory = TrustManagerFactory.getInstance("SunX509"); 
			trustManagerFactory.init(keyStore); 
			tms = trustManagerFactory.getTrustManagers();
		}
		SSLContext sslContext = SSLContext.getInstance(protocol);
		sslContext.init(kms, tms, null);  
		
		SSLServerSocketFactory sslServerSocketFactory = sslContext.getServerSocketFactory();  
		//只是创建一个TCP连接，SSL handshake还没开始
		//客户端或服务端第一次试图获取socket输入流或输出流时，
		//SSL handshake才会开始
		SSLServerSocket sslServerSocket = (SSLServerSocket) sslServerSocketFactory.createServerSocket(); 
		String[] pwdsuits = sslServerSocket.getSupportedCipherSuites();
		sslServerSocket.setEnabledCipherSuites(pwdsuits);
		//默认是client mode，必须在握手开始之前调用
		sslServerSocket.setUseClientMode(false);
		if(authority.intValue() == 2){
			//只有设置为server mode，该配置才生效
			//如果客户端不提供其证书，通信将会结束
			sslServerSocket.setNeedClientAuth(true);
		}else{
			//只有设置为server mode，该配置才生效
			//即使客户端不提供其证书，通信也将继续
			sslServerSocket.setWantClientAuth(true);
		}

		sslServerSocket.setReuseAddress(true);
		sslServerSocket.setReceiveBufferSize(128*1024);
		sslServerSocket.setPerformancePreferences(3, 2, 1);
		sslServerSocket.bind(new InetSocketAddress(serverListenPort),serverRequestQueueSize);
		return sslServerSocket;
	}
}

package vliu.https;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.security.KeyStore;
import java.util.Properties;

import javax.net.ssl.KeyManager;
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManager;
import javax.net.ssl.TrustManagerFactory;

public class HttpsClient {
	private SSLSocket socket;
	
	public HttpsClient(){
		try {
			int port = 8080;
			String host = "127.0.0.1";
			Properties p = Configuration.getConfig();
			
			String protocol = p.getProperty("protocol");
			String clientTrustCerFile = p.getProperty("clientTrustCer");
			String clientTrustCerPwd = p.getProperty("clientTrustCerPwd");
			
			//Trust Key Store
			KeyStore keyStore = KeyStore.getInstance("JKS");
			keyStore.load(new FileInputStream(clientTrustCerFile), 
					clientTrustCerPwd.toCharArray());  
				
			
			TrustManagerFactory trustManagerFactory = TrustManagerFactory.getInstance("SunX509"); 
			trustManagerFactory.init(keyStore); 
			TrustManager[] tms = trustManagerFactory.getTrustManagers();
			
			KeyManager[] kms = null;
			if(Configuration.getConfig().getProperty("authority").equals("2")){	
				String clientCerFile = p.getProperty("clientCer");
				String clientCerPwd = p.getProperty("clientCerPwd");
				String clientKeyPwd = p.getProperty("clientKeyPwd");
				
				//Key Store
				keyStore = KeyStore.getInstance("JKS");  
				keyStore.load(new FileInputStream(clientCerFile), 
						clientCerPwd.toCharArray());  
				
				KeyManagerFactory keyManagerFactory = KeyManagerFactory.getInstance("SunX509"); 
				keyManagerFactory.init(keyStore, clientKeyPwd.toCharArray()); 
				kms = keyManagerFactory.getKeyManagers();
			}
			SSLContext sslContext = SSLContext.getInstance(protocol);
			sslContext.init(kms, tms, null);  
			
			
			SSLSocketFactory factory = (SSLSocketFactory) sslContext.getSocketFactory();  
			socket = (SSLSocket)factory.createSocket(); 
			String[] pwdsuits = socket.getSupportedCipherSuites();
			//socket可以使用所有支持的加密套件
			socket.setEnabledCipherSuites(pwdsuits);
			//默认就是true
			socket.setUseClientMode(true);
			
			SocketAddress address = new InetSocketAddress(host, port);
			socket.connect(address, 0);
			System.out.println("connected to "+address.toString());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void request(){
		try{
			String msg="GET /?SomeQuerry HTTP/1.0\r\n";

			DataOutputStream output = new DataOutputStream(socket.getOutputStream());
			Properties p = Configuration.getConfig();
			String encoding = p.getProperty("socketStreamEncoding");
			byte[] bytes=msg.getBytes(encoding);
			output.write(bytes);
			System.out.print("request: "+msg);

			BufferedReader input=new BufferedReader(new InputStreamReader(socket.getInputStream()));
			String response="";
			while(true){
				String line=input.readLine();
				if(line==null)break;
				else response+=line+"\r\n";
			}
			System.out.println("response: "+response);
		}catch(Exception e){
			e.printStackTrace();
		}finally{
			try {
				socket.close();
				System.out.println("closed");
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static void main(String[] args){
		HttpsClient client = new HttpsClient();
		client.request();
	}
}

package vliu.https;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Properties;

public class Configuration {
	private static Properties config;
	
	public static Properties getConfig(){
		try{
			if(null == config){
				File configFile = new File("./conf/conf.properties");
				if(configFile.exists() && configFile.isFile()&& configFile.canRead()){
					InputStream input = new FileInputStream(configFile);
					config = new Properties();
					config.load(input);
				}else throw new Exception();
			}
		}catch(Exception e){
			//default set
			config = new Properties();
			config.setProperty("authority", "1");
			config.setProperty("protocol", "TLSV1.2");
			config.setProperty("serverCer", "./conf/server.jks");
			config.setProperty("serverCerPwd", "123456");
			config.setProperty("serverKeyPwd", "123456");
			config.setProperty("serverTrustCer", "./conf/serverTrust.jks");
			config.setProperty("serverTrustCerPwd", "123456");
			config.setProperty("clientCer", "./conf/client.jks");
			config.setProperty("clientCerPwd", "123456");
			config.setProperty("clientKeyPwd", "123456");
			config.setProperty("clientTrustCer", "./conf/clientTrust.jks");
			config.setProperty("clientTrustCerPwd", "123456");
			config.setProperty("serverListenPort", "8080");
			config.setProperty("serverThreadPoolSize", "5");
			config.setProperty("serverRequestQueueSize", "10");
			config.setProperty("socketStreamEncoding", "UTF-8");
		}
		return config;
	}
}

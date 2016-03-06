package vliu.https;

import java.net.ServerSocket;

public abstract class SSLServer {
	public abstract ServerSocket serverSocket()throws Exception;
}

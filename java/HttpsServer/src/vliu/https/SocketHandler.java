package vliu.https;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.StringTokenizer;

public class SocketHandler extends Thread{
	Socket client;
	BufferedReader is;
	DataOutputStream os;
	
	public SocketHandler(Socket socket){
		if(socket!=null){
			client=socket;
			try{
				//char reader
				is=new BufferedReader(new InputStreamReader(client.getInputStream()));
				//or bytes input stream
				//DataInputStream din= new DataInputStream(new BufferedInputStream(client.getInputStream()));
				os=new DataOutputStream(client.getOutputStream());
			}catch(IOException e){
				e.printStackTrace();
			}
			start();
			/*
			InputStream input=socket.getInputStream();
			OutputStream output=socket.getOutputStream();
			Request request=new Request(input);
			request.parse();
			Response response=new Response(output);
			response.setRequest(request);
			response.sendStaticResource();
			*/
		}
	}
	
	public void run(){
		try{
			String request=is.readLine();
			System.out.println("request: "+request);
			
			StringTokenizer token=new StringTokenizer(request);
			if((token.countTokens()>=2)&&token.nextToken().equals("GET")){
				String content="";
				String str=token.nextToken();
				if(str.startsWith("/?"))
					content=str.substring(2);
				else if(str.startsWith("/"))
					content=str.substring(1);
				if(content.equals("")||content.equals("/"))
					content="null";
				try{
					content="<head><title>Echo Server</title></head><body>"+content+"</body>";
					String response="HTTP/1.0 200 OK\r\n"+
							"Content-type: text/html\r\n"+
							"Conten-length: "+content.length()+"\r\n\r\n"+
							content+"\r\n";
					os.writeBytes(response);
					System.out.println("response: "+response);
				}catch(Exception e){
					os.writeBytes("HTTP/1.0 400 "+e.getMessage()+"\r\n");
				}
			}else
				os.writeBytes("400 Bad Request");
			client.close();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}

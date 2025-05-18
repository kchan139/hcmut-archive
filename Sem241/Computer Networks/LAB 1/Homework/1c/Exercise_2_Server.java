import java.io.*;
import java.net.*;

public class Exercise_2_Server {
    public static void main(String[] args) {
        try(ServerSocket server = new ServerSocket(12345)) {
            System.out.println("Listening on port 12345");
            Socket socket = server.accept();

            System.out.println("New client connected");
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            
            String msg;
            while ((msg = in.readLine()) != null) {
                System.out.println("Client: " + msg);
                out.println("Server: " + msg);
            }
            socket.close();
        }
        catch(IOException e) {
            System.out.println("Server error: " + e.getMessage());
        }
    }
}
import java.io.*;
import java.net.*;

public class Exercise_2_Client {
    public static void main(String args[])
    {
        try(Socket socket = new Socket("localhost", 12345)) {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

            System.out.println("Connected to the chat server");

            String userMsg;
            while ((userMsg = input.readLine()) != null) {
                out.println(userMsg);
                System.out.println(in.readLine());
            }
            socket.close();
        }
        catch(IOException e) {
            e.getStackTrace();
            System.out.println("Client error: " + e.getMessage());
        }
    }
}
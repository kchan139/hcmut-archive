import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Exercise_3_Client {
    public static void main(String[] args) {
        String hostname = "localhost";
        int port = 8080;

        try {
            Socket socket = new Socket(hostname, port);

            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            Scanner scanner = new Scanner(System.in);

            while(true) 
            {
                System.out.println("Enter a message to send to the server:");

                String userInput = scanner.nextLine();
                out.println(userInput);
                
                String response = in.readLine();
                System.out.println("Server response: " + response);

                if (response.equals("goodbye"))  {
                    out.println("goodbye");
                    break;
                }
            }
            scanner.close();
            socket.close();
        } 
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
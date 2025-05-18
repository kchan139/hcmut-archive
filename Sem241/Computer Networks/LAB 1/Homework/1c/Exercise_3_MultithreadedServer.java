import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

class ClientHandler implements Runnable {
    private Socket clientSocket;

    ClientHandler(Socket socket) {
        this.clientSocket = socket;
    }

    public void run() {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)) {

            String inputLine;
            Scanner scanner = new Scanner(System.in);

            while ((inputLine = in.readLine()) != null) {
                System.out.println("Received from client: " + inputLine);
                System.out.println("Enter a message to send to the client:");
                String serverInput = scanner.nextLine();
                out.println(serverInput);
            }
            scanner.close();
        } catch (IOException e) {
            System.err.println("Error handling client: " + e.getMessage());
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                System.err.println("Error closing socket: " + e.getMessage());
            }
        }
    }
}

public class Exercise_3_MultithreadedServer {
    public static void main(String[] args) {
        int port = 8080;
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);
            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("New client connected: " + clientSocket.getInetAddress());
                ClientHandler handler = new ClientHandler(clientSocket);
                new Thread(handler).start();
            }
        }
        catch (IOException e) {
            System.err.println("Error in server: " + e.getMessage());
        }
    }
}
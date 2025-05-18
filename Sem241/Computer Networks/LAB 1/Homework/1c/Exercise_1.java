import java.io.*;
import java.net.*;

// Exercise 1: Connect to a web server and download homepage
public class Exercise_1 {
    public static void main(String[] args) {
        try {
            // Connecting to Google homepage
            URL url = new URL("http://www.google.com");
            BufferedReader in = new BufferedReader(new InputStreamReader(url.openStream()));
            BufferedWriter out = new BufferedWriter(new FileWriter("homepage.html"));

            String input;
            while ((input = in.readLine()) != null) {
                out.write(input);
                out.newLine();
            }

            in.close();
            out.close();
            System.out.println("Downloaded successfully.");
        } 
        catch (IOException e) {
            System.out.println(e.getMessage());
        }


        try {
            // Get hostname by textual representation of IP address
            InetAddress address = InetAddress.getByName("127.0.0.1");

            // Get hostname by a byte array containing the IP address
            byte[] IPaddress = new byte[]{127, 0, 0, 1};
            address = InetAddress.getByAddress(IPaddress);

            // Get the host name
            String hostname = address.getHostName();

            // Get canonical host name
            String canonicalHostName = address.getCanonicalHostName();
            System.out.println("Hostname: " + hostname);
            System.out.println("Canonical Hostname: " + canonicalHostName);

            // Get IP address from hostname
            InetAddress address2 = InetAddress.getByName("www.google.com");
            
            // Get the IP address
            String IPaddress2 = address2.getHostAddress();
            System.out.println("IP Address: " + IPaddress2);
            
            // Get all IP addresses of a host
            InetAddress[] addresses = InetAddress.getAllByName("www.google.com");
            for (int i = 0; i < addresses.length; i++) {
                System.out.println("IP Address " + (i + 1) + ": " + addresses[i].getHostAddress());
            }
        } 
        catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
        
    }
}
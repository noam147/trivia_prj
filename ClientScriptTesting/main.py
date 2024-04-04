import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 55555


def server():
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the address and port
    server_address = (SERVER_IP, SERVER_PORT)
    sock.bind(server_address)

    # Listen for incoming connections
    sock.listen(1)

    print("Server is listening on", SERVER_IP, "port", SERVER_PORT)

    while True:
        # Wait for a connection
        print("Waiting for a connection...")
        connection, client_address = sock.accept()

        try:
            print("Connection established with", client_address)

            # Send a welcome message to the client
            connection.sendall(b"Welcome to the server!")

            # Receive data from the client
            while True:
                data = connection.recv(1024)
                if data:
                    print("Received:", data.decode())
                    # Echo the received data back to the client
                    connection.sendall(data)
                else:
                    break

        finally:
            # Clean up the connection
            connection.close()

if __name__ == "__main__":
    server()
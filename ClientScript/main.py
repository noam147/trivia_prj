import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 55555


def handleSession():
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        sock.settimeout(10)  # Set a timeout of 10 seconds

        # Connecting to the server
        server_address = (SERVER_IP, SERVER_PORT)
        
        sock.connect(server_address)

        while True:
            # Receive server's opening message
            server_msg = sock.recv(1024).decode()
            print("Server:", server_msg)

            # Send message
            message = input("Enter message to send (type 'exit' to quit): ")
            if message.lower() == 'exit':
                break
            sock.sendall(message.encode())

    except socket.timeout:
        print("Connection timed out.")
    except ConnectionRefusedError:
        print("Connection refused. Make sure the server is running.")
    except Exception as e:
        print("Error:", e)
    finally:
        # Close the socket
        sock.close()


if __name__ == "__main__":
    handleSession()

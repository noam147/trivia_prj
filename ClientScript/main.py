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
            # Receive server's message
            server_msg = sock.recv(1024).decode()
            print("Server:", server_msg)
            example_msgs = ["""10051{"password":"1234","username":"user1"}""","""20080{"password":"1234","username":"user1","email":"1234567@gmail.com"}"""]
            # Send message
            message = input("Enter message to send (type 'exit' to quit): ")
            if len(message) > 2**32:
                continue
            if message.lower() == 'exit':
                break
            try:
                message = example_msgs[int(message)]
            except Exception:
                pass
            message = "{:04d}".format(len(message)) + message
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

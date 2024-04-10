
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
            server_msg = sock.recv(1024).decode()
            print("Server:", server_msg)
            msg = input("enter\n")
            chr1 = chr(1)
            chr2 = chr(2)
            exampleStr = chr1 + """0038{"password":"1234","username":"user4"}"""
            exampleStr2 = chr2 + """0066{"password":"1234","username":"user4","email":"1234567@gmail.com"}"""
            example_msgs = [exampleStr, exampleStr2]
            if msg == '1' or msg == '0':
                print("enterrrrrrrrr")
                sock.sendall(example_msgs[int(msg)].encode())
                print(example_msgs[int(msg)])
                continue
            print(msg)
            sock.sendall(msg.encode())
            continue
            # Receive server's message



            # Send message
            #message = input("Enter message to send (type 'exit' to quit): ")
            choice = input("1. signup\n2.login\n")
            if choice == 1:
                #message = ""
                #message = chr1
                user = input("enter username\n")
                password = input("enter password\n")
                email =input("enter email\n")
                headers = """{"password":"""
                headers += '"'+password +'","username":"'+user+'","email":'+'email"}'
                str:msgLen = ""
                if len(headers) < 1000:
                    if len(headers) <100:
                        if len(headers) <10:
                            msgLen = "000"+len(headers)
                        msgLen = "00" +len(headers)
                    msgLen = "000" +len(headers)
                message +=msgLen +headers


            if len(message) > 2**32:
                continue
            if message.lower() == 'exit':
                break
            try:
                message = example_msgs[int(message)]
                print(message)
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

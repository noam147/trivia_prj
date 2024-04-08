import socket
import MessagesFormats as Mf
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 55555
MESSAGE_TYPE = {'\x1': Mf.SignupMessage, 2: Mf.LoginMessage}


def formatJSON(msg_type: chr):
    """
    the function gets the msg wanted and results in the msg data as jason
    :param msg_type: int, the type(id) of the message
    :return: str, the message data as json or None, failed
    """
    print(msg_type in MESSAGE_TYPE)
    if msg_type in MESSAGE_TYPE:
        msg_class = MESSAGE_TYPE[msg_type]
        # checks if the arguments given are valid using exception handling
        try:
            msg = msg_class()
        except TypeError:
            return None
        json_msg = json.dumps(msg.__dict__)
        return json_msg
    return None


def getMessageType():
    """
    gets the type of the message from the client
    :return: chr, message type or None, failed
    """
    msgType = 0
    try:
        msgType = chr(int(input("Enter message type: ")))
    except ValueError:
        return None
    if msgType not in MESSAGE_TYPE:
        print(str(msgType) + " is not a valid type")
        return None
    return msgType


def createMessage():
    """
    formats a message with data given from the user
    :return: str, the message or None, failed
    """
    msg_type = getMessageType()
    if msg_type is None:
        print("Message type isn't valid")
        return None
    msg_data = formatJSON(int(msg_type))
    if msg_data is None:
        print("data given isn't valid")
        return None
    if chr.__sizeof__() + len(msg_data) > 9999:
        print("Message is too long")
        return None
    msg_len = "{:04d}".format(len(msg_type) + len(msg_data))
    msg = msg_type + msg_len + msg_data
    return msg


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

            # Send message
            message = createMessage()
            if message is None:
                continue
            if message.lower()[6:] == 'exit':
                break
            print("client: " + message)
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
    # handleSession()
    handleSession()

from socket import *
serverName = '127.0.0.1'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
while True:
    message = input('input lowercase sentence:')
    if message == 'q': break
    clientSocket.send(message.encode())
    print('success to send a message')
    modifiedMessage = clientSocket.recvfrom(2048)
    print(modifiedMessage.decode())
clientSocket.close()
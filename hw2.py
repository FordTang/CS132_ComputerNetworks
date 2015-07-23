# Ford Tang
# 46564602
# partnered with Ray Chou

#import socket module
from socket import *
from threading import Thread


def thread_connection(connectionSocket, addr):
        print("Thread Started")
        try:
                message = connectionSocket.recv(1024)
                filename = message.split()[1]
                print(message)
                f = open(filename[1:])
                outputdata = f.read()
                print(outputdata)
                #Send one HTTP header line into socket
 		#Fill in start
                connectionSocket.send("HTTP/1.1 200 OK\r\n\r\n")
                #Fill in end
 		#Send the content of the requested file to the client
                for i in range(0, len(outputdata)):
                	connectionSocket.send(outputdata[i])
                	#print(outputdata[i])
                #f.close()
                connectionSocket.close()
        except IOError:
 		#Send response message for file not found
 		#Fill in start
                connectionSocket.send("HTTP/1.1 404 Not Found\r\n\r\n")
 		#Fill in end
 		#Close client socket
 		#fill in start
                connectionSocket.close()
                #break
 		#Fill in end
        print("Thread Closed")



serverSocket = socket(AF_INET, SOCK_STREAM)

#Prepare a server socket
serverPort = 6789
serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print('The server is ready to receive')

while True:
        #Establish the connection
        print('Ready to serve...')
        connectionSocket, addr = serverSocket.accept()
        thread = Thread(target = thread_connection, args = (connectionSocket, addr))
        thread.start()
        
serverSocket.close()

import socket
import os
import sys
script_dir = os.path.dirname(__file__)
mymodule_dir = os.path.join(script_dir, "..", 'payload')
sys.path.append(mymodule_dir) 
import builder
import time
import json
class BasicClient(object):
    def __init__(self, name="frida_kahlo", ipaddr="127.0.0.1", port=4000):
        self._clt = None
        self.name = name
        self.ipaddr = ipaddr
        self.port = port

        self.group = "public"

        if self.ipaddr is None:
            raise ValueError("IP address is missing or empty")
        elif self.port is None:
            raise ValueError("port number is missing")

        self.connect()

    def __del__(self):
        self.stop()

    def stop(self):
        if self._clt is not None:
            self._clt.close()
        self._clt = None

    def connect(self):
        if self._clt is not None:
            return

        addr = (self.ipaddr,self.port)
        self._clt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._clt.connect(addr)
        #self._clt.setblocking(False)

    def join(self, group):
        self.group = group

    def sendMsg(self, text):
        if self._clt is None:
            raise RuntimeError("No connection to server exists")

        if len(text) == 0:
            print("Message is empty")
        elif len(text) >= 10000:
            chunk_start_index = 0
            chunk_end_index = 10000
            print("text: ",len(text))
            while(chunk_end_index < len(text)):
                print(f"sending to group {self.group} from {self.name}")
                bldr = builder.BasicBuilder()
                m = bldr.encode(self.name,self.group,text[chunk_start_index:chunk_end_index])
                #start timer
                start_time = time.time_ns()
                print("Message sent to server")
                #send message to server
                self._clt.send(bytes(m, "utf-8"))
                #get response from server and ouput to client
                from_server = self._clt.recv(3)
                print(from_server)
                #end timer and print result
                end_time = time.time_ns()
                elapsed_time = end_time - start_time
                print("Elapsed time:",elapsed_time)
                chunk_end_index += 10000
                chunk_start_index += 10000
            if chunk_start_index < len(text):
                print(f"sending to group {self.group} from {self.name}")
                bldr = builder.BasicBuilder()
                m = bldr.encode(self.name,self.group,text[chunk_start_index:chunk_end_index])
                #start timer
                start_time = time.time_ns()
                print("Message sent to server")
                #send message to server
                self._clt.send(bytes(m, "utf-8"))
                #get response from server and ouput to client
                from_server = self._clt.recv(3)
                print(from_server)
                #end timer and print result
                end_time = time.time_ns()
                elapsed_time = end_time - start_time
                print("Elapsed time:",elapsed_time)
        else:
            
            print(f"sending to group {self.group} from {self.name}")
            bldr = builder.BasicBuilder()
            m = bldr.encode(self.name,self.group,text)
            #start timer
            start_time = time.time_ns()
            print("Message sent to server")
            #send message to server
            self._clt.send(bytes(m, "utf-8"))
            #get response from server and ouput to client
            from_server = self._clt.recv(2048)
            print(from_server)
            #end timer and print result
            end_time = time.time_ns()
            elapsed_time = end_time - start_time
            print("Elapsed time:",elapsed_time)

    def groups(self):
        # return list of groups
        pass

    def getMsgs(self):
        # get the latest messages from a group
        pass

def sendToJava(m):
    pythonClient = BasicClient("python","127.0.0.1",3000)
    pythonClient.sendMsg(m)

def sendToCpp(m):
    pythonClient = BasicClient("python","127.0.0.1",2000)
    pythonClient.sendMsg(m)

def sendToPython(m):
    pythonClient = BasicClient("python","127.0.0.1",4000)
    pythonClient.sendMsg(m)
    
    
if __name__ == '__main__':
    with open('sampledata.json') as json_file:
        data = json.load(json_file)
    
    m1 = data['message1']
    m2 = data['message2']
    m3 = data['message3']
    m4 = data['message4']
    m5 = data['message5']
   
    print("message1 length: ", len(m1))
    print("message2 length: ", len(m2))
    print("message3 length: ", len(m3))
    print("message4 length: ", len(m4))
    print("message5 length: ", len(m5))
#connect to servers
#try:
 #   sendToJava(message)
#except:
#    print("error: Could not connect to java server")
#try:
#    sendToCpp(message)
#except:
#    print("error: Could not connect to cpp server")
try:
    sendToPython(m3)
except:
    print("error: Could not connect to python server")

    
    #Server for port 3000
    #javaClient = BasicClient()
    #javaClient.sendToJava()
    
    #Server for port 2000
    #cppClient = BasicClient()
    #cppClient.sendToCpp(message)
    
    #Server for port 4000
    #pythonClient = BasicClient()
    #pythonClient.sendToPython(message)
    
 

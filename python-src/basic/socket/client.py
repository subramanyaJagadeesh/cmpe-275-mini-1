import socket
import os
import sys
script_dir = os.path.dirname(__file__)
mymodule_dir = os.path.join(script_dir, "..", 'payload')
sys.path.append(mymodule_dir) 
import builder
import time
import json

json_file_path = os.path.join(os.path.dirname(__file__), 'sampledata.json')

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

       #(total_chars * num_iterations * 2) / ((end - start) / 1_000_000_000.0);
        #diveide message into chunks to server
        elif len(text) >= 10000:
            chunk_start_index = 0
            split_chunck_by_ten = len(text)//10
            print("divide by ten:", split_chunck_by_ten)
            chunk_end_index = split_chunck_by_ten
            elapsed_times_list = []
            #print("text1234: ",len(text))
            #total = (total_chars * num_iterations * 2) / ((end - start) / 1_000_000_000.0);
            start_time = time.time_ns()
            #Chunking logic
            while(chunk_end_index <= len(text)):
                print(f"sending to group {self.group} from {self.name}")
                bldr = builder.BasicBuilder()
                m = bldr.encode(self.name,self.group,text[chunk_start_index:chunk_end_index])
                #start timer
                #start_time = time.time_ns()
                #start_time = time.time_ns()
                print("Message sent to server")
                #send message to server
                self._clt.send(bytes(m, "utf-8"))
                #get response from server and ouput to client
                from_server = self._clt.recv(10)
                print(from_server)
                #end timer and print result
                #end_time = time.time_ns()
                #end_time = time.time()
                #elapsed_time = end_time - start_time
                #print("Elapsed time:",elapsed_time)
                #elapsed_times_list.append(elapsed_time)
                chunk_end_index += split_chunck_by_ten
                chunk_start_index += split_chunck_by_ten
            if chunk_start_index < len(text):
                print(f"sending to group {self.group} from {self.name}")
                bldr = builder.BasicBuilder()
                m = bldr.encode(self.name,self.group,text[chunk_start_index:chunk_end_index])
                #start timer
                #start_time = time.time_ns()
                #start_time = time.time()
                print("Message sent to server")
                #send message to server
                self._clt.send(bytes(m, "utf-8"))
                #get response from server and ouput to client
                from_server = self._clt.recv(10)
                print(from_server)
                #end timer and print result
                #end_time = time.time_ns()
                end_time = time.time_ns()
                #elapsed_time = end_time - start_time
                print("Elapsed time:",elapsed_time)
                #total = (total_chars * num_iterations * char in bytes) / ((end - start) / 1_000_000_000.0);
                total = (len(text) * 1 * 2) / ((end_time - start_time) / 1_000_000_000.0)
                #elapsed_times_list.append(elapsed_time)
                #return elapsed_times_list, total
                return total
            else:
                total=0
                end_time = time.time_ns()
                #total = (total_chars * num_iterations * char in bytes) / ((end - start) / 1_000_000_000.0);
                total = (len(text) * 1 * 2) / ((end_time - start_time) / 1_000_000_000.0)
                #return elapsed_times_list,total
                return total
        else:
            elapsed_times_list = []
            print("text: ",len(text))
            print(f"sending to group {self.group} from {self.name}")
            bldr = builder.BasicBuilder()
            m = bldr.encode(self.name,self.group,text)
            #start timer
            #start_time = time.time_ns()
            start_time = time.time_ns()
            print("Message sent to server")
            #send message to server
            self._clt.send(bytes(m, "utf-8"))
            #get response from server and ouput to client
            from_server = self._clt.recv(10)
            print(from_server)
            #end timer and print result
            #end_time = time.time_ns()
            end_time = time.time_ns()
            elapsed_time = end_time - start_time
            print("Elapsed time:",elapsed_time)
            #total = (total_chars * num_iterations * char in bytes) / ((end - start) / 1_000_000_000.0);
            total = (len(text) * 1 * 2) / ((end_time - start_time) / 1_000_000_000.0)
            #print("Elapsed time:",elapsed_time)
            #elapsed_times_list.append(elapsed_time)
            #return elapsed_times_list, total
            return total

    def groups(self):
        # return list of groups
        pass

    def getMsgs(self):
        # get the latest messages from a group
        pass

def sendToJava(m):
    total =0
    a1=0
    pythonClient = BasicClient("python","127.0.0.1",3000)
    a1 = pythonClient.sendMsg(m)
    #total = sum(my_list)
    print(a1)
    return total

def sendToCpp(m):
    total =0
    pythonClient = BasicClient("python","127.0.0.1",2000)
    my_list,a1 = pythonClient.sendMsg(m)
    #total = sum(my_list)
    return total

def sendToPython(m):
    total =0
    pythonClient = BasicClient("python","127.0.0.1",4000)
    a1 = pythonClient.sendMsg(m)
    print(a1)
    #total = sum(my_list)
    return total

if __name__ == '__main__':
    with open(json_file_path, 'r') as json_file:
        data = json.load(json_file)
    
    m1 = data['message1']#100
    m10 = data['message10']#1 000
    m3 = data['message3']#10 000
    m4 = data['message4']#100 000
    m5 = data['message5']#1 000 000
    m8 = "hi"


i =0
test_counter = 1
total_time =[]
try:
    for i in range(test_counter):
        total_time.append(sendToPython(m10))
    print(total_time)
except:
    print("error: Could not connect to python server")

i1 =0
test_counter1 = 1
total_time1 =[]
try:
    for i1 in range(test_counter1):
        total_time1.append(sendToJava(m10))
    print(total_time1)
    print("Average bytes/s", (sum(total_time1)/(len(m3)*test_counter1)))
except:
    print("error: Could not connect to Java server")

i2 =0
test_counter2 = 1
total_time2 =[]
try:
    for i2 in range(test_counter2):
        total_time2.append(sendToCpp(m4))
    print(total_time2)
except:
    print("error: Could not connect to Cpp server")

    
 

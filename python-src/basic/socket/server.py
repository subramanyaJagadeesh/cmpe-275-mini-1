import socket
import threading
import os
import sys
script_dir = os.path.dirname(__file__)
mymodule_dir = os.path.join(script_dir, "..", 'payload')
sys.path.append(mymodule_dir) 
import builder
import time

class BasicServer(object):
   def __init__(self, ipaddr ='', port=4000):
      self.ipaddr = ipaddr
      self.port = port
      self._svr = None
      self.good = True

      if self.ipaddr is None:
           raise ValueError("IP address is missing or empty")
      elif self.port is None:
           raise ValueError("port number is missing")
      elif self.port <=1024:
           raise ValueError(f"port number ({port}) must be above 1024")

   def __del__(self):
      # closs socket
      self.stop()

   def stop(self):
      self.good = False
      if self._svr is not None:
         self._svr.close()
         self._svr = None
 
   def run(self):
      addr = (self.ipaddr,self.port)
      if socket.has_dualstack_ipv6():
         self._svr = socket.create_server(addr, family=socket.AF_INET6, dualstack_ipv6=True)
      else:
         self._svr = socket.create_server(addr)
      self._svr.listen(10)

      print(f"server ({self.ipaddr}) is listening on {self.port}")

      while self.good:
        cltconn, caddr = self._svr.accept()
        print(f"Connection from {caddr[0]}")
        csession = SessionHandler(cltconn,caddr)
        csession.start()

# ----------------------------------------------

class SessionHandler(threading.Thread):
    #Set session id counter to zero
    counter =0#created using chatgptg
    
    def __init__(self,client_connection, client_addr):
        threading.Thread.__init__(self)
        self.daemon = False
        self._cltconn = client_connection
        self._cltaddr = client_addr
        self.session_id = SessionHandler.counter #created using chatgptg
        SessionHandler.counter += 1 #created using chatgptg
        self.good = True

    def __del__(self):
        self.close()

    def close(self):
        if self._cltconn is None:
            return
        else:
            self._cltconn.close()
            self._cltconn = None
            self.good = False

    def process(self,raw):
        try:
            bldr = builder.BasicBuilder()
            name,group,text = bldr.decode(raw)
            print(f"Session Id: {self.session_id},from {name}, to group: {group}, text: {text}")
        except Exception as e:
            pass

    def run(self):
        while self.good:
            try:
                ##set time out to give enough time for server to get the message from the client
                self._cltconn.settimeout(2000)

                buf = self._cltconn.recv(100000)
                if len(buf) <= 0:
                    self.good = False
                else:
                    self._cltconn.send(b"ACK")
                    self.process(buf.decode("utf-8"))
                    
            except Exception as e:
                print(e)
                self.good = False

        print(f"clossing session {self.session_id}:, from client: {self._cltaddr}")

    
    #ips set to '' otherwise program does not run on windows machines
def javaServer():
    server = BasicServer('', 3000)
    server.run()

def pythonServer():
    server = BasicServer('', 4000)
    server.run()

def cppServer():
    server = BasicServer('', 2000)
    server.run()

if __name__ == '__main__':
    pythonServer()


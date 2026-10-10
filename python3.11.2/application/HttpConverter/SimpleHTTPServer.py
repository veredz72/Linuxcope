
from http.server import HTTPServer, BaseHTTPRequestHandler
import sys
import socket

#HOST = "localHost"
#PORT = 8000
HTTP_PORT = int(sys.argv[1])	# 8000	
TCP_HOST = sys.argv[2]			# 'localHost'
TCP_PORT = int(sys.argv[3])		# 5100		
ROOT = "Elta"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect ((TCP_HOST,TCP_PORT))

def tohex (val, nbits):
    return hex((val+(1<<nbits)) % (1<<nbits))

class CustomHTTP (BaseHTTPRequestHandler):
    clientIpsList = []
    
    def do_GET (self):
        self.send_response (200)
        ContentType =  "text/html"

        if (self.path.find (".html")>0):
           ContentType =  "text/html"
        elif (self.path.find (".css")>0):
           ContentType =  "text/css"
        elif (self.path.find (".js")>0):
           ContentType =  "application/javascript"
        elif (self.path.find (".png")>0):
           ContentType =  "image/png"
        elif (self.path.find (".ttf")>0):
           ContentType =  "application/font-sfnt"
        elif (self.path.find (".ico")>0):
           ContentType =  "image/vnd.microsoft.icon"
        elif (self.path.find (".xml")>0):
           ContentType =  "text/xml"

        self.send_header ("Content-type", ContentType)
        self.end_headers ()

        if (self.path=="/"):
            Path=ROOT+"/index.html"
        else:
            Path=ROOT+self.path

        print ("File="+Path+' ' +ContentType)
        with open(Path, 'rb') as file:
            self.wfile.write(file.read())

    def log_message (self, format, *args):
        return

    def do_POST (self):

        #send OK
        self.send_response (200)
        #send response header
        self.send_header ("Content-type", "octet/stream")
        self.send_header ("Access-Control-Allow-Origin","*")
        self.end_headers ()
        ContentLength = int(self.headers['Content-Length']) # <--- Gets the size of data
        RequestBody = self.rfile.read(ContentLength) # <--- Gets the data itself
        #Remove '{' and '}' from string
        Data = RequestBody[1:-1].decode("utf-8")
        #Convert to list of strings
        List =  Data.split (",")
    
        #Convert to list of numbers
        NumList = [int(i) for i in List]
        #NumList = [0 if i=='undefined' else int(i) for i in List]
        
        Raw=[]
        #Convert to list of bytes (each number aligned to 4 bytes)
        for i in NumList:
            if i<0:
                ByteArray = i.to_bytes(4, byteorder = 'little',signed=True);
            else:
                ByteArray = i.to_bytes(4, byteorder = 'little');
            Raw.append (ByteArray)
        
        #Raw = [i.to_bytes(4, byteorder = 'little',signed=True) for i in NumList]
        #Convert to one byte array 
        Stream = b''.join (Raw)
        #Send to server
        s.sendall (Stream)
        #Receive reply from server
        Header = s.recv (12)
        #print ("Header={0}".format (len(Header)) )
        self.wfile.write (Header)
        Rest = int.from_bytes(Header[8:12], "little");
        Rest = Rest - len (Header)
        while Rest>0:
            #print (Rest)
            Body = s.recv (Rest)
            self.wfile.write (Body)
            #print ("Body={0}".format (len(Body)) )
            Rest = Rest-len (Body)

server = HTTPServer (('', HTTP_PORT), CustomHTTP)
server.serve_forever ()


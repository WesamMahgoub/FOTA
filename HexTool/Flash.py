import socket
import sys
from intelhex import IntelHex
import hashlib

hex_obj = IntelHex()
hex_obj.fromfile('Hled.hex',format='hex')

bin_data = hex_obj.tobinarray()
bin_data = bin_data.tolist()
entry_point = str(hex_obj.start_addr['EIP'])
#.to_bytes(4,byteorder='little')
#entry_point = str(list (entry_point))

#def Bl_u8calc_crc(data,lenth):
#	cr = 0
#	for i in (0,len,1):
#		cr = cr ^ data[i]
#	return cr
lis = [0,1,2,3,4,5]
def sum_loop(list_items):
    total = 0  # initialize with start number
    counter = 0# iterate through the list
    for item in list_items:
        # add item to total
        total ^= item
    return total
    
print(sum_loop(lis[1:4]))

print(entry_point)
code_size = str(len(bin_data))
cmd = 0x10
appInfo = 0x34
transferData = 0x36
exitTransfer = 0x37
add = 0x08010000
#.to_bytes(2, byteorder='big')
ip = "10.145.9.87"
port = 4210

# Create socket for server
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
print("Do Ctrl+c to exit the program !!")
s.bind(('', 4444))
s.connect(("10.145.9.87", port))
# Let's send data through UDP protocol
#.to_bytes(2, byteorder='little')
# first Address
####################################################################
    
#state = com.comMngr_send_data([0x34]+list(entry_point)+list(code_size))
print(len(bin_data))

s.sendto(str(cmd).encode('utf-8'), (ip, port))
print("\n\n 1. Client Sent : ", str(cmd), "\n\n")
receive_data, address = s.recvfrom(4210)
print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")

while int(receive_data) == 32:
    s.sendto(str(cmd).encode('utf-8'), (ip, port))
    print("\n\n 1. Client Sent : ", str(cmd), "\n\n")
    receive_data, address = s.recvfrom(4210)
    print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")

#if(receive_data == 0x7f)
s.sendto(str(appInfo).encode('utf-8'), (ip, port))
print("\n\n 1. Client Sent : ", str(appInfo), "\n\n")
receive_data, address = s.recvfrom(4210)
print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")
    
while int(receive_data) == 68:
    s.sendto(str(appInfo).encode('utf-8'), (ip, port))
    print("\n\n 1. Client Sent : ", str(appInfo), "\n\n")
    receive_data, address = s.recvfrom(4210)
    print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")
    
#if(receive_data == 0x7f)
s.sendto(code_size.encode('utf-8'), (ip, port))
print("\n\n 1. Client Sent : ", code_size, "\n\n")
s.sendto(entry_point.encode('utf-8'), (ip, port))
print("\n\n 1. Client Sent : ", entry_point, "\n\n")
s.sendto(str(add).encode('utf-8'), (ip, port))
print("\n\n 1. Client Sent : ", str(add), "\n\n")
receive_data, address = s.recvfrom(4210)
print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")
    
while int(receive_data) == 68:
    s.sendto(code_size.encode('utf-8'), (ip, port))
    print("\n\n 1. Client Sent : ", code_size, "\n\n")
    s.sendto(entry_point.encode('utf-8'), (ip, port))
    print("\n\n 1. Client Sent : ", entry_point, "\n\n")
    receive_data, address = s.recvfrom(4210)
    print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")
    
#if(receive_data == 0x7f)
s.sendto(str(transferData).encode('utf-8'), (ip, port))
print("\n\n 1. Client Sent : ", str(transferData), "\n\n")
receive_data, address = s.recvfrom(4210)
print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n") 

while int(receive_data) == 70:
    s.sendto(str(transferData).encode('utf-8'), (ip, port))
    print("\n\n 1. Client Sent : ", str(transferData), "\n\n")
    receive_data, address = s.recvfrom(4210)
    print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")   
    
block_size = 1024    
  
for start in range(0 , len(bin_data) , block_size):
    end = start + block_size
    if end > len(bin_data):
        end = len(bin_data)
    send_data = str(bin_data[start:end])
    crc = sum_loop(bin_data[start:end])
    s.sendto(send_data.encode('utf-8'), (ip, port))
    print("\n\n 1. Client Sent : ", send_data, "\n\n")
    s.sendto(str(crc).encode('utf-8'), (ip, port))
    print("\n\n 1. Client Sent : ", crc, "\n\n")
    receive_data, address = s.recvfrom(4092)
    print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")
    if int(receive_data) == 70:
        start = start - block_size

#if(receive_data == 0x7f)
s.sendto(str(exitTransfer).encode('utf-8'), (ip, port))
print("\n\n 1. Client Sent : ", str(exitTransfer), "\n\n")
receive_data, address = s.recvfrom(4210)
print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")

while int(receive_data) == 71:
    s.sendto(str(exitTransfer).encode('utf-8'), (ip, port))
    print("\n\n 1. Client Sent : ", str(exitTransfer), "\n\n")
    receive_data, address = s.recvfrom(4210)
    print("\n\n 2. Client received : ", receive_data.decode('utf-8'), "\n\n")
    
    #   readable_hash = hashlib.md5(bin_data[start:end]).hexdigest()
    #   s.sendto(readable_hash.encode('utf-8'), (ip, port))
    #   print("\n\n 1. Client Sent : ", code_size, "\n\n")
    #   data, address = s.recvfrom(4092)
    #   print("\n\n 2. Client received : ", data.decode('utf-8'), "\n\n")
    # close the socket
s.close()


  
#
#
#

import struct
import socket

UDP_IP = "192.168.1.136"
UDP_PORT = 2390
MESSAGE = b"CONNECT\r\n"

print("UDP target IP: %s" % UDP_IP)
print("UDP target port: %s" % UDP_PORT)
print("message: %s" % MESSAGE)

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
ok = sock.connect((UDP_IP, UDP_PORT))
print('ok', ok)

sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

ok = sock.recv(1024)
print('ok', ok)
data = sock.recv(1024)
print('data', data, len(data))
print(struct.unpack('LlllLLL', data))

CLOSE_MESSAGE = b"CLOSE\r\n"
sock.sendto(CLOSE_MESSAGE, (UDP_IP, UDP_PORT))



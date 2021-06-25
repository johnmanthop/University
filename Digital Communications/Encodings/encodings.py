import numpy
import matplotlib.pyplot as plt

#can be changed accordingly
PRECISION = 1000 #every second is divided into 100 parts
STEP      = 1 / PRECISION #smallest time interval possible in our simulation

def AST_s(t: float, b: str):
    if b == '0':
        return 0
    else:
        return numpy.sin(2*numpy.pi*4*t)

def FSK_s(t: float, b: str):
    if b == '0':
        return numpy.sin(2*numpy.pi*t)
    else:
        return numpy.sin(2*numpy.pi*4*t)

def PSK_s(t: float, b: str):
    if b == '0':
        return numpy.sin(2*numpy.pi*t)
    else:
        return numpy.sin(2*numpy.pi*t + numpy.pi)

phase = 0
def DPSK_s(t: float, b: str, changed: bool):
    global phase
    if changed and b == '1':
        if phase == 0: phase = numpy.pi
        else:          phase = 0
    
    return numpy.sin(2*numpy.pi*t + phase)

def QAM8_s(t: float, b1: str, b2: str, b3: str):
    ampl  = 0
    phase = 0

    if b3 == '1': ampl = 4
    else:         ampl = 1

    if b2 == '1': phase = numpy.pi / 4
    else:         phase = (3*numpy.pi) / 4

    if b1 == '0': phase = -phase

    return ampl * numpy.sin(2*numpy.pi*t + phase)

def encode(msg: str, signal):
    buffer = []
    t = 0 #time counter
    i = 0 #msg  counter
    while t < len(msg):
        buffer.append(signal(t, msg[i]))

        temp = t
        t += STEP

        if numpy.floor(t) > numpy.floor(temp): i += 1
    return buffer

def encode_dif(msg: str, signal):
    buffer = []
    t = 0 #time counter
    i = 0 #msg  counter
    changed = True
    while t < len(msg):
        buffer.append(signal(t, msg[i], changed))
        if changed: changed = False #send "changed" parameter to the differential encoding

        temp = t
        t += STEP

        if numpy.floor(t) > numpy.floor(temp): 
            i += 1
            changed = True
    return buffer

def encode_qam(msg: str, signal):
    buffer = []
    t = 0 #time counter
    i = 0 #msg  counter
    while i < len(msg) - 2:
        buffer.append(signal(t, msg[i], msg[i+1], msg[i+2])) #send 3 bits instead of 1 to the qam encoding

        temp = t
        t += STEP

        if numpy.floor(t) > numpy.floor(temp): 
            i += 3

    return buffer

msg1 = "101001110"
msg2 = "000010101011110111000"

ask  = encode(msg1, AST_s)
fsk  = encode(msg1, FSK_s)
psk  = encode(msg1, PSK_s)
dpsk = encode_dif(msg1, DPSK_s)
qam8 = encode_qam(msg2, QAM8_s)

x1 = numpy.arange(0, 9, STEP) #for ask to dpsk
x2 = numpy.arange(0, 7, STEP) #only for qam

#add x1 or x2 and the corresponding encoding to get the graph
plt.plot(x1, ask) 
plt.show()


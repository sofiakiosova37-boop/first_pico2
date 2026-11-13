import serial, time; s = serial.Serial('COM8', 115200, timeout=1); [print(s.read(100)) for _ in range(3)]

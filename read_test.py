import serial; s = serial.Serial('COM8', 115200, timeout=1); [print(s.readline().decode('utf-8', errors='ignore').strip()) for _ in range(10)]

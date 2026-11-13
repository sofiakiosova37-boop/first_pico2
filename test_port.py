import serial; print('Testing COM8...'); s = serial.Serial('COM8', 115200, timeout=1); print('Connected!'); s.close()

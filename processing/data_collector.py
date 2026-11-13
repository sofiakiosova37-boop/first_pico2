import serial
from datetime import datetime
import os

PORT = "COM8"   
BAUD = 115200
HEADER = "ms,ax,ay,az,gx,gy,gz,lat,lng,alt,sats"
FIELDS = len(HEADER.split(","))

# new data recordings
filename = datetime.now().strftime("data_%Y%m%d_%H%M%S.csv")

print(f"Connecting to {PORT} at {BAUD} baud...")

try:
    with serial.Serial(PORT, BAUD, timeout=1) as ser, open(filename, "w", encoding="utf-8") as f:
        f.write(HEADER + "\n")
        f.flush()
        print(f"Writing telemetry to {filename}. Press Ctrl+C to stop.")
        
        while True:
            line = ser.readline().decode("utf-8", errors="ignore").strip()
            if line:
                parts = line.split(",")
                if len(parts) == FIELDS and parts[0].isdigit():
                    f.write(line + "\n")
                    f.flush()
                    os.fsync(f.fileno())
                    print(line)
                    
except KeyboardInterrupt:
    print("\nStopped by user. Data saved.")
except Exception as e:
    print(f"\nError: {e}")
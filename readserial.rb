require 'rubygems'
require 'serialport'

ser = SerialPort.new("/dev/ttyACM0", 9600, 8, 1, SerialPort::NONE)

while(line = ser.readLine("\r")) do
  puts line
end


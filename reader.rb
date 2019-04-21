require 'serialport'

STDOUT.sync = true

@ser_write = SerialPort.new("/dev/ttyACM0", 115200, 8, 1, SerialPort::NONE)
@ser_read = SerialPort.new("/dev/ttyACM0", 115200, 8, 1, SerialPort::NONE)

@ser_write.syswrite(255.chr) # frame start
@ser_write.syswrite(60.chr) # minScanH
@ser_write.syswrite(120.chr) # maxScanH
@ser_write.syswrite(70.chr) # minScanV
@ser_write.syswrite(120.chr) # maxScanV
@ser_write.syswrite(100.chr) # frame delay

while true
  begin
    if @ser_read.readbyte == 255 && @ser_read.readbyte == 255
      scan_v = @ser_read.readbyte
      scan_h = @ser_read.readbyte
      return if(scan_v == 255 && scan_h == 255)
      distance = (@ser_read.readbyte << 8) | @ser_read.readbyte
      sig_strength = (@ser_read.readbyte << 8) | @ser_read.readbyte
      puts "#{scan_v},#{scan_h},#{distance},#{sig_strength}"
    end
  rescue
  end
end

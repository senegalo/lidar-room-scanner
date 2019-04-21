require 'serialport'

STDOUT.sync = true

SHIFT_RADIUS = 10

@ser_write = SerialPort.new("/dev/ttyACM0", 115200, 8, 1, SerialPort::NONE)
@ser_read = SerialPort.new("/dev/ttyACM0", 115200, 8, 1, SerialPort::NONE)

@ser_write.syswrite(255.chr) # frame start
@ser_write.syswrite(0.chr) # minScanH
@ser_write.syswrite(200.chr) # maxScanH
@ser_write.syswrite(60.chr) # minScanV
@ser_write.syswrite(120.chr) # maxScanV
@ser_write.syswrite(100.chr) # frame delay

def get_r(distance)
  Math.sqrt(distance**2 + SHIFT_RADIUS**2)
end

def get_xyz(distance, theta, phi)
  adjusted_theta = to_rad(180 - theta)
  adjusted_phi = 0.9 * phi
  [
    get_r(distance) * Math.sin(adjusted_theta) * Math.cos(to_rad(adjusted_phi)),
    get_r(distance) * Math.sin(adjusted_theta) * Math.sin(to_rad(adjusted_phi)),
    get_r(distance) * Math.cos(adjusted_theta)
  ]
end

def to_rad(angle)
  angle * Math::PI / 180
end

while true
  begin
    if @ser_read.readbyte == 255 && @ser_read.readbyte == 255
      scan_v = @ser_read.readbyte
      scan_h = @ser_read.readbyte
      return if(scan_v == 255 && scan_h == 255)
      distance = (@ser_read.readbyte << 8) | @ser_read.readbyte
      sig_strength = (@ser_read.readbyte << 8) | @ser_read.readbyte

      x, y, z = get_xyz(distance, scan_h, scan_v)

      puts "#{x},#{y},#{z},#{distance},#{scan_h},#{scan_v}#{get_r(distance)},#{scan_h*0.9},#{180-scan_v}"
    end
  rescue
  end
end

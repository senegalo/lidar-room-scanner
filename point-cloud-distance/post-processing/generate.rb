L1 = 2.4
L2 = 2.4

def to_rad(deg)
  deg * Math::PI / 180
end

IO.foreach(ARGV[0]) do |l|
  phy, a1, d = l.split(',').map(&:to_f)

  next if d > 75

  phy = to_rad(phy)
  a1 = to_rad(a1)

  c_square = L1**2 + L2**2 - 2 * L1 * L2 * Math.cos(a1)
  c = Math.sqrt(c_square)

  b1 = Math.asin(L1 * Math.sin(a1) / c)

  r_square = c_square + d**2 - 2 * c * d * Math.cos(b1 + to_rad(90))
  r = Math.sqrt(r_square)

  theta = b1 + a1 + Math.asin(d * Math.sin(b1 + to_rad(90)) / r) - to_rad(90)

  x = r * Math.sin(theta) * Math.cos(phy)
  y = r * Math.sin(theta) * Math.sin(theta)
  z = r * Math.cos(theta)

  puts "#{x} #{y} #{z}"
end

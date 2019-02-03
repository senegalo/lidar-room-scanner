(1..180).each do |y|
  (0..180).each do |x|
    if x > 30 && y < 60
      puts "#{x},#{y},20"
    else
      puts "#{x},#{y},500"
    end
  end
end

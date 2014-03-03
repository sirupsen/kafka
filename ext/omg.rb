require_relative 'kafkarb.so'

kafka = Kafka.new

loop do
  p kafka.consume
end

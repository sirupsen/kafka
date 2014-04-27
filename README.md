# Kafka

Note that nothing currently works, and maybe it never will. This is currently a
pet project.

Apache Kafka client built as a wrapper for `librdkafka`. This library was
motivated by the current lack of a fast, solid Ruby library for producing and
consuming messages 100s of messages a second from/to Kafka without a measurable
performance impact.

```ruby
kafka = Kafka.new(brokers: ["kafka01.example.com:9092", "kafka02.example.com:9092"])
topic = kafka.topics.first

# defaults to consuming from all partitions from tail
topic.messages.each do |message|
  putes message
end

# consume from the tail of a set of partitions
topic.messages(partitions: {0 => :latest, 1, => :latest}).each do |message|
  puts message
end

# consume from beginning of all partitions
topic.messages(partitions: {0 => :earliest, 1 => :earliest}).each do |message|
  puts message
end

# consume from partitions starting at an offset
topic.messages(partitions: {1 => 29393, 2 => 39923}).each do |message|
  puts message
end

# produce async to a single partition
topic.produce({name: "test", id: 822}.to_json, partition: 3)

# produce async to a random partition
topic.produce({name: "test", id: 822}.to_json, partition: :random)

# produce and acknowledge from kafka syncronously
topic.produce({name: "test", id: 822}.to_json, blocking: true)

# error handler invoked when the producer fails to send a message
# TODO: how should consume errors be handled? exception in block?
kafka.produce_error do |error|
  puts error
end
```

require 'mkmf'

LIBDIR      = RbConfig::CONFIG['libdir']
INCLUDEDIR  = RbConfig::CONFIG['includedir']

HEADER_DIRS = [
  '/opt/local/include',
  '/usr/local/include',
  INCLUDEDIR,
  '/usr/include',
]

LIB_DIRS = [
  '/opt/local/lib',
  '/usr/local/lib',
  LIBDIR,
  '/usr/lib',
]

dir_config('rdkafka', HEADER_DIRS, LIB_DIRS)

unless find_library("rdkafka", "rd_kafka_topic_name")
  abort "omg no librdkafka"
end

find_header('librdkafka/rdkafka.h')

create_makefile 'kafkarb'

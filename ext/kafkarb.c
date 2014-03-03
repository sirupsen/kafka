#include <ctype.h>
#include <ruby.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>

#include "librdkafka/rdkafka.h"


/* static void msg_consume (rd_kafka_message_t *rkmessage, */
/*     void *opaque) { */
/*   if (rkmessage->err) { */
/*     if (rkmessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF) { */
/*       fprintf(stderr, */
/*           "%% Consumer reached end of %s [%"PRId32"] " */
/*           "message queue at offset %"PRId64"\n", */
/*           rd_kafka_topic_name(rkmessage->rkt), */
/*           rkmessage->partition, rkmessage->offset); */

/*       return; */
/*     } */

/*     fprintf(stderr, "%% Consume error for topic \"%s\" [%"PRId32"] " */
/*         "offset %"PRId64": %s\n", */
/*         rd_kafka_topic_name(rkmessage->rkt), */
/*         rkmessage->partition, */
/*         rkmessage->offset, */
/*         rd_kafka_message_errstr(rkmessage)); */
/*     return; */
/*   } */

/*   fprintf(stdout, "%% Message (offset %"PRId64", %zd bytes):\n", */
/*       rkmessage->offset, rkmessage->len); */

/*   if (rkmessage->key_len) { */
/*       printf("Key: %.*s\n", */
/*           (int)rkmessage->key_len, (char *)rkmessage->key); */
/*   } */

/*     printf("%.*s\n", */
/*         (int)rkmessage->len, (char *)rkmessage->payload); */
/* } */
/* /1* int main (int argc, char **argv) { *1/ */
/* /1*   rd_kafka_topic_t *rkt; *1/ */
/* /1*   char *brokers = "kafka01.chi.shopify.com:9092"; *1/ */
/* /1*   char *topic = "checkout"; *1/ */
/* /1*   int partition = 0; *1/ */
/* /1*   rd_kafka_conf_t *conf; *1/ */
/* /1*   rd_kafka_topic_conf_t *topic_conf; *1/ */
/* /1*   char errstr[512]; *1/ */
/* /1*   const char *debug = NULL; *1/ */
/* /1*   int64_t start_offset = 0; *1/ */

/* /1*   quiet = !isatty(STDIN_FILENO); *1/ */

/* /1*   /2* Kafka configuration *2/ *1/ */
/* /1*   conf = rd_kafka_conf_new(); *1/ */

/* /1*   /2* Topic configuration *2/ *1/ */
/* /1*   topic_conf = rd_kafka_topic_conf_new(); *1/ */


/* /1*   signal(SIGINT, stop); *1/ */
/* /1*   signal(SIGUSR1, sig_usr1); *1/ */

/* /1*   if (debug && *1/ */
/* /1*       rd_kafka_conf_set(conf, "debug", debug, errstr, sizeof(errstr)) != *1/ */
/* /1*       RD_KAFKA_CONF_OK) { *1/ */
/* /1*     fprintf(stderr, "%% Debug configuration failed: %s: %s\n", *1/ */
/* /1*         errstr, debug); *1/ */
/* /1*     exit(1); *1/ */
/* /1*   } *1/ */


/* /1*     /2* Create Kafka handle *2/ *1/ */
/* /1*     if (!(rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, *1/ */
/* /1*             errstr, sizeof(errstr)))) { *1/ */
/* /1*       fprintf(stderr, *1/ */
/* /1*           "%% Failed to create new consumer: %s\n", *1/ */
/* /1*           errstr); *1/ */
/* /1*       exit(1); *1/ */
/* /1*     } *1/ */


/* /1*     /2* Add brokers *2/ *1/ */
/* /1*     if (rd_kafka_brokers_add(rk, brokers) == 0) { *1/ */
/* /1*       fprintf(stderr, "%% No valid brokers specified\n"); *1/ */
/* /1*       exit(1); *1/ */
/* /1*     } *1/ */

/* /1*     /2* Create topic *2/ *1/ */
/* /1*     rkt = rd_kafka_topic_new(rk, topic, topic_conf); *1/ */

/* /1*     /2* Start consuming *2/ *1/ */
/* /1*     if (rd_kafka_consume_start(rkt, partition, start_offset) == -1){ *1/ */
/* /1*       fprintf(stderr, "%% Failed to start consuming: %s\n", *1/ */
/* /1*           rd_kafka_err2str(rd_kafka_errno2err(errno))); *1/ */
/* /1*       exit(1); *1/ */
/* /1*     } *1/ */

/* /1*     while (run) { *1/ */
/* /1*       rd_kafka_message_t *rkmessage; *1/ */

/* /1*       /2* Consume single message. *1/ */
/* /1*        * See rdkafka_performance.c for high speed *1/ */
/* /1*        * consuming of messages. *2/ *1/ */
/* /1*       rkmessage = rd_kafka_consume(rkt, partition, 1000); *1/ */
/* /1*       if (!rkmessage) /2* timeout *2/ *1/ */
/* /1*         continue; *1/ */

/* /1*       msg_consume(rkmessage, NULL); *1/ */

/* /1*       /2* Return message to rdkafka *2/ *1/ */
/* /1*       rd_kafka_message_destroy(rkmessage); *1/ */
/* /1*     } *1/ */

/* /1*     /2* Stop consuming *2/ *1/ */
/* /1*     rd_kafka_consume_stop(rkt, partition); *1/ */

/* /1*     rd_kafka_topic_destroy(rkt); *1/ */

/* /1*     rd_kafka_destroy(rk); *1/ */

/* /1*   /2* Let background threads clean up and terminate cleanly. *2/ *1/ */
/* /1*   rd_kafka_wait_destroyed(2000); *1/ */

/* /1*   return 0; *1/ */
/* /1* } *1/ */

// C struct linked to all Ruby objects
typedef struct {
  char* brokers;

  rd_kafka_topic_t *rkt;
  rd_kafka_t *rk;
  rd_kafka_conf_t *conf;

  char errstr[512];
  char* debug;

  // TODO: Move somewhere else?
  rd_kafka_topic_conf_t *topic_conf;
  int partition;
  char* topic;
  int64_t start_offset;
} kafka_t;

void
kafka_free(void *ptr)
{
  // LEAK ALL THE THINGS
  //
  /* kafka_t* kafka = ptr; */
  /* xfree(kafka->rkt); */
  /* xfree(kafka->brokers); */
  /* xfree(kafka->topic); */
  /* xfree(kafka->conf); */
  /* xfree(kafka->topic_conf); */
  /* xfree(kafka->debug); */

  /* xfree(kafka); */
}


VALUE
kafka_alloc(VALUE klass)
{
  kafka_t* kafka = malloc(sizeof(kafka_t));
  VALUE obj = Data_Wrap_Struct(klass, NULL, kafka_free, kafka);

  kafka->brokers = (char*) "kafka01.chi.shopify.com:9092";
  kafka->topic = (char*) "checkout";
  kafka->partition = 0;
  kafka->debug = NULL;
  kafka->start_offset = 0;

  // TODO: Error?
  kafka->conf = rd_kafka_conf_new();
  kafka->topic_conf = rd_kafka_topic_conf_new();

  /* Create Kafka handle */
  if (!(kafka->rk = rd_kafka_new(RD_KAFKA_CONSUMER, kafka->conf, kafka->errstr, sizeof(kafka->errstr)))) {
    fprintf(stderr, "%% Failed to create new consumer: %s\n", kafka->errstr);
    exit(1);
  }

  if (rd_kafka_brokers_add(kafka->rk, kafka->brokers) == 0) {
    fprintf(stderr, "%% No valid brokers specified\n");
    exit(1);
  }

  // TODO: Error?
  kafka->rkt = rd_kafka_topic_new(kafka->rk, kafka->topic, kafka->topic_conf);

  // TODO: Start_offset should be specified
  if (rd_kafka_consume_start(kafka->rkt, kafka->partition, kafka->start_offset) == -1){
    fprintf(stderr, "%% Failed to start consuming: %s\n", rd_kafka_err2str(rd_kafka_errno2err(errno)));
    exit(1);
  }

  return obj;
}

/* static VALUE */
/* kafka_alloc(VALUE klass) */
/* { */
/*   kafka_t* kafka = malloc(sizeof(kafka_t)); */

/*   return Data_Wrap_Struct(klass, NULL, kafka_free, kafka); */
/* } */

VALUE
kafka_consume(VALUE self)
{
  kafka_t* kafka;
  rd_kafka_message_t *rkmessage;

  Data_Get_Struct(self, kafka_t, kafka);

  fprintf(stderr, "Partition: %d, Rkt: %d\n", kafka->partition, kafka->rkt);

  // TODO: Error checking
  rkmessage = rd_kafka_consume(kafka->rkt, kafka->partition, 1000);
  if (!rkmessage) {
    fprintf(stderr, "Timeout\n");
    return Qnil;
  }

  if (rkmessage->err) {
    fprintf(stderr, "Consume error\n");

    /* if (rkmessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF) { */
    /*   fprintf(stderr, */
    /*       "%% Consumer reached end of %s [%"PRId32"] " */
    /*       "message queue at offset %"PRId64"\n", */
    /*       rd_kafka_topic_name(rkmessage->rkt), */
    /*       rkmessage->partition, rkmessage->offset); */

    /*   return; */
    /* } */

    /* fprintf(stderr, "%% Consume error for topic \"%s\" [%"PRId32"] " */
    /*     "offset %"PRId64": %s\n", */
    /*     rd_kafka_topic_name(rkmessage->rkt), */
    /*     rkmessage->partition, */
    /*     rkmessage->offset, */
    /*     rd_kafka_message_errstr(rkmessage)); */
    /* return Qnil; */
    return Qnil;
  }

  rd_kafka_message_destroy(rkmessage);

  return rb_str_new(rkmessage->payload, rkmessage->len);
}

VALUE
kafka_initialize(VALUE self)
{
  /* kafka_t* kafka; */
  /* Data_Get_Struct(self, kafka_t, kafka); */

  return self;
}

void Init_kafkarb()
{
  VALUE kafkarb = rb_define_class("Kafka", rb_cObject);

  rb_define_alloc_func(kafkarb, kafka_alloc);
  rb_define_method(kafkarb, "initialize", kafka_initialize, 0);
  rb_define_method(kafkarb, "consume", kafka_consume, 0);
}

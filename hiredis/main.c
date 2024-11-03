/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "redis_lib.h"

int main() {
    // Connect to Redis database 0
    RedisDB *db = redis_connect(0);
    if (db == NULL) {
        printf("Failed to connect to Redis\n");
        return 1;
    }

    // Set a key
    if (redis_set(db, "test_key", "Hello from Redis lib!") == 0) {
        printf("Successfully set key\n");
    } else {
        printf("Failed to set key\n");
    }

    // Get the value
    char *value = redis_get(db, "test_key");
    if (value) {
        printf("Got value: %s\n", value);
        free(value);  // Don't forget to free the returned string
    } else {
        printf("Failed to get value\n");
    }

    // Increment a counter
    long long counter = redis_incr(db, "counter");
    if (counter != -1) {
        printf("Counter value: %lld\n", counter);
    } else {
        printf("Failed to increment counter\n");
    }

    // Close connection
    redis_close(db);
    return 0;
}
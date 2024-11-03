/* redis_lib.h */
#ifndef REDIS_LIB_H
#define REDIS_LIB_H

#include <hiredis/hiredis.h>

// Redis connection handle
typedef struct {
    redisContext *context;
    int db_number;
} RedisDB;

// Initialize connection to Redis with specific database number
RedisDB* redis_connect(int db_number);

// Free Redis connection
void redis_close(RedisDB *db);

// Get string value for key
char* redis_get(RedisDB *db, const char *key);

// Set string value for key
int redis_set(RedisDB *db, const char *key, const char *value);

// Increment value for key
long long redis_incr(RedisDB *db, const char *key);

#endif

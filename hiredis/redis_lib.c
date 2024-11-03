/* redis_lib.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "redis_lib.h"

RedisDB* redis_connect(int db_number) {
    RedisDB *db = malloc(sizeof(RedisDB));
    if (db == NULL) {
        return NULL;
    }

    // Connect to Redis
    db->context = redisConnect("127.0.0.1", 6379);
    if (db->context == NULL || db->context->err) {
        if (db->context) {
            printf("Connection error: %s\n", db->context->errstr);
            redisFree(db->context);
        }
        free(db);
        return NULL;
    }

    // Select the specified database
    redisReply *reply = redisCommand(db->context, "SELECT %d", db_number);
    if (reply == NULL || reply->type == REDIS_REPLY_ERROR) {
        if (reply) {
            freeReplyObject(reply);
        }
        redisFree(db->context);
        free(db);
        return NULL;
    }
    freeReplyObject(reply);

    db->db_number = db_number;
    return db;
}

void redis_close(RedisDB *db) {
    if (db) {
        if (db->context) {
            redisFree(db->context);
        }
        free(db);
    }
}

char* redis_get(RedisDB *db, const char *key) {
    if (!db || !db->context || !key) {
        return NULL;
    }

    redisReply *reply = redisCommand(db->context, "GET %s", key);
    if (reply == NULL) {
        return NULL;
    }

    char *result = NULL;
    if (reply->type == REDIS_REPLY_STRING) {
        result = strdup(reply->str);  // Create a copy of the string
    }

    freeReplyObject(reply);
    return result;  // Caller must free this memory
}

int redis_set(RedisDB *db, const char *key, const char *value) {
    if (!db || !db->context || !key || !value) {
        return 1;  // Error
    }

    redisReply *reply = redisCommand(db->context, "SET %s %s", key, value);
    if (reply == NULL) {
        return 1;  // Error
    }

    int result = (reply->type == REDIS_REPLY_STATUS && 
                 strcmp(reply->str, "OK") == 0) ? 0 : 1;

    freeReplyObject(reply);
    return result;
}

long long redis_incr(RedisDB *db, const char *key) {
    if (!db || !db->context || !key) {
        return -1;  // Error
    }

    redisReply *reply = redisCommand(db->context, "INCR %s", key);
    if (reply == NULL) {
        return -1;  // Error
    }

    long long result = -1;
    if (reply->type == REDIS_REPLY_INTEGER) {
        result = reply->integer;
    }

    freeReplyObject(reply);
    return result;
}
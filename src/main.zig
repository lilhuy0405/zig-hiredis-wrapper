const std = @import("std");
const redis = @cImport({
    @cInclude("./hiredis/redis_lib.h");
});
pub fn main() !void {
    // Prints to stderr (it's a shortcut based on `std.io.getStdErr()`)
    const db = redis.redis_connect(0) orelse {
        std.debug.print("Failed to connect to Redis\n", .{});
        return error.ConnectionFailed;
    };
    defer redis.redis_close(db);

    const value = redis.redis_get(db, "test_key");
    if (value) |val| {
        // Value exists, print it
        std.debug.print("Got value: {s}\n", .{val});
        // Free the C-allocated string
        std.c.free(value);
    } else {
        std.debug.print("Failed to get value\n", .{});
    }
}

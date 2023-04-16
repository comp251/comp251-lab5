#ifndef __RR_SERVICE_H__
#define __RR_SERVICE_H__

// Implements the service layer for Rhodes Ramble. Services requests by clients
// by delegating to the rr_core for handling of messages.

// Command names
#define RR_POST "POST"
#define RR_COMMENT "COMMENT"
#define RR_REGISTER "REGISTER"
#define RR_GET "POSTS"
#define RR_COMMENTS "COMMENTS"
#define RR_USER_INFO "USER"
#define RR_VOTE "VOTE"

// Initialize the service and all dependencies.
void init_rr_service();

// Clean up the service and all dependencies.
void destroy_rr_service();

// Handle a client request.
//
// msg is the request from the client and is parsed/handled using the
// Rhodes Ramble protocol definition. Response messages are written to
// response_fd (e.g., a client socket).
void parse_and_dispatch(int response_fd, char *msg, int msg_len);

#endif

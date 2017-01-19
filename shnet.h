#ifndef _SHNET_H
#define _SHNET_H
/*
 * Kernel-based shared networking driver - API
 *
 * Copyright 2016 Red Hat, Inc.
 * Copyright 2016 Oracle
 *
 * Authors:
 *   Marcel Apfelbaum <marcel@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 */

#include <linux/uio.h>

#define SHNET_FILE_NAME "/dev/shnet"
#define SHNET_MAX_PORTS 255

#define SHNET_IOC_MAGIC 0xBA

#define SHNET_REGISTER_PORT       _IOR(SHNET_IOC_MAGIC, 0, int)
#define SHNET_UNREGISTER_PORT     _IOW(SHNET_IOC_MAGIC, 1, int)
#define SHNET_IOC_MAX               2

#define SHNET_MAX_IOVEC_LEN        UIO_FASTIOV


enum shnet_ack_type {
    SHNET_ACK_IMMEDIATE,
    SHNET_ACK_DELAYED,
};

struct shnet_connection {
    unsigned long connection_id;
    unsigned long local_queue_id;
    unsigned long remote_id;
    unsigned long remote_queue_id;
    enum shnet_ack_type ack_type;
};

struct shnet_req {
    unsigned long req_id;
    unsigned long connection_id;
    struct iovec vec[SHNET_MAX_IOVEC_LEN];
    int vlen; /* <= SHNET_MAX_IOVEC_LEN */
};

struct shnet_completion {
    unsigned long req_id;
    int status; /* 0 = Success */
};

#define SHNET_PORT_IOC_MAGIC 0xBB

#define SHNET_PORT_OPEN_CONN     _IOR(SHNET_PORT_IOC_MAGIC, 0, struct shnet_connection)
#define SHNET_PORT_CLOSE_CONN    _IOR(SHNET_PORT_IOC_MAGIC, 1, struct shnet_connection)
#define SHNET_PORT_RECV          _IOR(SHNET_PORT_IOC_MAGIC, 2, struct shnet_req)
#define SHNET_PORT_SEND          _IOW(SHNET_PORT_IOC_MAGIC, 3, struct shnet_req)
#define SHNET_PORT_IOC_MAX 4

#endif


#include "debug.h"
#include "dependencies.h"
#include "types.h"

#define ODI_DEBUG_MSG_LEN 4096

struct odi_debug_queue dqueue[ODI_DEBUG_MAX_TAGS] = {
    {
        .tag = ODI_DTAG_ERROR,
        .entries = 0x0
    },
    {
        .tag = ODI_DTAG_INFO,
        .entries = 0x0
    },
    {
        .tag = ODI_DTAG_WARN,
        .entries = 0x0
    },
    {
        .tag = ODI_DTAG_DEBUG,
        .entries = 0x0
    },
    [4 ... ODI_DEBUG_MAX_TAGS - 1] = {
        .tag = ODI_DTAG_NONE,
        .entries = 0x0
    }
};

struct odi_debug_queue* get_queue(const char* tag) {
    for (int i = 0; i < ODI_DEBUG_MAX_TAGS; i++) {
        if (!odi_dep_strcmp(dqueue[i].tag, tag)) {
            return &dqueue[i];
        }
    }
    return 0x0;
}

void clear_entries(struct odi_debug_entry* head) {
    struct odi_debug_entry* current = head;
    while (current != 0x0) {
        struct odi_debug_entry* next = current->next;
        odi_dep_free(current);
        current = next;
    }
}

void odi_debug_append(const char* tag, char * message, ...) {
    struct odi_debug_queue* queue = get_queue(tag);
    if (queue == 0x0) {
        return;
    }

    struct odi_debug_entry* current = queue->entries;
    //entries starts uninitialized, so we need to check if it's null
    if (current == 0x0) {
        current = odi_dep_malloc(sizeof(struct odi_debug_entry));
        queue->entries = current;
    } else {
        while (current->next != 0x0) {
            current = current->next;
        }
        current->next = odi_dep_malloc(sizeof(struct odi_debug_entry));
        current = current->next;
    }

    current->message = odi_dep_malloc(ODI_DEBUG_MSG_LEN);
    va_list args;
    va_start(args, message);
    odi_dep_vsnprintf(current->message, ODI_DEBUG_MSG_LEN, message, args);
    va_end(args);
    current->next = 0x0;

    return;
}

void odi_debug_flusha() {
    for (int i = 0; i < ODI_DEBUG_MAX_TAGS; i++) {
        odi_debug_flush(dqueue[i].tag);
    }
}
void odi_debug_cleara() {
    for (int i = 0; i < ODI_DEBUG_MAX_TAGS; i++) {
        odi_debug_clear(dqueue[i].tag);
    }
}

void odi_debug_flush(const char * tag) {
    struct odi_debug_queue* queue = get_queue(tag);
    if (queue == 0x0) {
        return;
    }

    struct odi_debug_entry* current = queue->entries;
    while (current != 0x0) {
        odi_dep_printf("[%s] %s\n", tag, current->message);
        current = current->next;
    }

    clear_entries(queue->entries);
}

//Delete all entries in the queue
void odi_debug_clear(const char * tag) {
    struct odi_debug_queue* queue = get_queue(tag);
    if (queue == 0x0) {
        return;
    }

    clear_entries(queue->entries);
}
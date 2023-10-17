#include "debug.h"
#include "dependencies.h"

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
    [4 ... ODI_DEBUG_MAX_TAGS] = {
        .tag = ODI_DTAG_NONE,
        .entries = 0x0
    }
};

struct odi_debug_entry* get_entries(const char* tag) {
    for (int i = 0; i < ODI_DEBUG_MAX_TAGS; i++) {
        if (!odi_dep_strcmp(dqueue[i].tag, tag)) {
            return dqueue[i].entries;
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
    struct odi_debug_entry* entries = get_entries(tag);
    if (entries == 0x0) {
        return;
    }

    struct odi_debug_entry* current = entries;
    while (current->next != 0x0) {
        current = current->next;
    }

    struct odi_debug_entry* new_entry = odi_dep_malloc(sizeof(struct odi_debug_entry));
    current->next = new_entry;
    new_entry->next = 0x0;

    odi_va_list args;
    odi_dep_va_start(args, message);
    int len = odi_dep_vsnprintf(0x0, 0, message, args);
    odi_dep_va_end(args);

    new_entry->message = odi_dep_malloc(len + 1);

    odi_dep_va_start(args, message);
    odi_dep_vsnprintf(new_entry->message, len + 1, message, args);
    odi_dep_va_end(args);

}

void odi_debug_flush(const char * tag) {
    struct odi_debug_entry* entries = get_entries(tag);
    if (entries == 0x0) {
        return;
    }

    struct odi_debug_entry* current = entries;
    while (current != 0x0) {
        odi_deps_printf("[%s] %s\n", tag, current->message);
        current = current->next;
    }

    clear_entries(entries);
}

//Delete all entries in the queue
void odi_debug_clear(const char * tag) {
    struct odi_debug_entry* entries = get_entries(tag);
    if (entries == 0x0) {
        return;
    }

    clear_entries(entries);
}
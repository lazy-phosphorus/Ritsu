#ifndef RITSU_COLLECTION_LIST_H
#define RITSU_COLLECTION_LIST_H

#define __ListNode(Type) struct Type##ListNode

#define ListNode(Type) __ListNode(Type) *

#define __List(Type) struct Type##List

#define List(Type) __List(Type) *

#define UseList(Type)        \
    struct Type##ListNode {  \
        Type data;           \
        ListNode(Type) next; \
    };                       \
    struct Type##List {      \
        ListNode(Type) head; \
        ListNode(Type) tail; \
        unsigned int size;   \
    };

#define ListNew(Type)                                               \
    ({                                                              \
        List(Type) this = (List(Type))malloc(sizeof(__List(Type))); \
        this->head = NULL;                                          \
        this->tail = NULL;                                          \
        this->size = 0;                                             \
        this;                                                       \
    })

#define ListDelete(Type, this, release)            \
    ListNode(Type) node = this->head, temp = NULL; \
    while (node != NULL) {                         \
        temp = node;                               \
        node = node->next;                         \
        if (release != NULL) release(temp->data);  \
        free(temp);                                \
    }                                              \
    free(this);

#define ListPushBack(Type, this, value)                                      \
    if (this->size == 0) {                                                   \
        this->head = (ListNode(Type))malloc(sizeof(__ListNode(Type)));       \
        this->tail = this->head;                                             \
    } else {                                                                 \
        this->tail->next = (ListNode(Type))malloc(sizeof(__ListNode(Type))); \
        this->tail = this->tail->next;                                       \
    }                                                                        \
    this->tail->data = value;                                                \
    this->size++;

#endif  // RITSU_COLLECTION_LIST_H

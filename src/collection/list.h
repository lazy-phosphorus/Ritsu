#ifndef RITSU_COLLECTION_LIST_H
#define RITSU_COLLECTION_LIST_H

#define __ListNode(Type) struct __##Type##ListNode
#define ListNode(Type) __ListNode(Type) *
#define __List(Type) struct __##Type##List
#define List(Type) __List(Type) *

#define DECLARE_LIST(Type) __List(Type);

#define USE_LIST(Type)           \
    __ListNode(Type) {           \
        Type value;              \
        ListNode(Type) next;     \
        ListNode(Type) previous; \
    };                           \
    __List(Type) {               \
        ListNode(Type) head;     \
        ListNode(Type) tail;     \
        unsigned int size;       \
    }

#define __ListNodeNew(Type, v, p, n)                          \
    ({                                                        \
        ListNode(Type) node =                                 \
            (ListNode(Type))malloc(sizeof(__ListNode(Type))); \
        assert(node != NULL);                                 \
        node->value = v;                                      \
        node->previous = p;                                   \
        node->next = n;                                       \
        node;                                                 \
    })

#define ListNew(Type)                                               \
    ({                                                              \
        List(Type) this = (List(Type))malloc(sizeof(__List(Type))); \
        assert(this != NULL);                                       \
        this->head = NULL;                                          \
        this->tail = NULL;                                          \
        this->size = 0;                                             \
        this;                                                       \
    })

#define ListDelete(Type, this)                        \
    assert(this != NULL);                             \
    ListNode(Type) node = (*this)->head, temp = NULL; \
    while (node != NULL) {                            \
        temp = node;                                  \
        node = node->next;                            \
        free(temp);                                   \
    }                                                 \
    free(*this);                                      \
    *this = NULL;

#define ListDelete1(Type, this, destructor) \
    assert(this != NULL);                   \
    assert(destructor != NULL);             \
    ListNode(Type) node = (*this)->head;    \
    ListNode(Type) temp = NULL;             \
    while (node != NULL) {                  \
        temp = node;                        \
        node = node->next;                  \
        destructor(temp->value);            \
        free(temp);                         \
    }                                       \
    free(*this);                            \
    *this = NULL;

#define ListPushBack(Type, this, value)                                  \
    assert(this != NULL);                                                \
    if (this->size == 0) {                                               \
        this->head = __ListNodeNew(Type, value, NULL, NULL);             \
        this->tail = this->head;                                         \
    } else {                                                             \
        this->tail->next = __ListNodeNew(Type, value, this->tail, NULL); \
        this->tail = this->tail->next;                                   \
    }                                                                    \
    this->size++;

#endif  // RITSU_COLLECTION_LIST_H

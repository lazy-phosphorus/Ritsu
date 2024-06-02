#ifndef RITSU_COLLECTION_ARRAY_H
#define RITSU_COLLECTION_ARRAY_H

#include <assert.h>
#include <malloc.h>

#define __Array(Type) struct __##Type##Array
#define Array(Type) __Array(Type) *

#define DECLARE_ARRAY(Type) __Array(Type);

#define USE_ARRAY(Type)        \
    __Array(Type) {            \
        Type *array;           \
        unsigned int size;     \
        unsigned int capacity; \
    };

#define ArrayNew(Type, initialCapacity)                                \
    ({                                                                 \
        assert(initialCapacity != 0);                                  \
        Array(Type) this = (Array(Type))malloc(sizeof(__Array(Type))); \
        assert(this != NULL);                                          \
        this->array = (Type *)calloc(initialCapacity, sizeof(Type));   \
        assert(this->array != NULL);                                   \
        this->capacity = initialCapacity;                              \
        this->size = 0;                                                \
        this;                                                          \
    })

#define ArrayDelete(Type, this) \
    assert(this != NULL);       \
    free((*this)->array);       \
    free(*this);                \
    *this = NULL;

#define ArrayDelete1(Type, this, destructor)        \
    assert(this != NULL);                           \
    assert(destructor != NULL);                     \
    for (unsigned int i = 0; i < this->size; i++) { \
        destructor(this->array[i]);                 \
    }                                               \
    free((*this)->array);                           \
    free(*this);                                    \
    *this = NULL;

#define ArrayGet(Type, this, index)  \
    ({                               \
        assert(this != NULL);        \
        assert(this->array != NULL); \
        assert(index >= 0);          \
        assert(index < this->size);  \
        this->array[index];          \
    })

#define ArraySet(Type, this, index, value) \
    assert(this != NULL);                  \
    assert(this->array != NULL);           \
    assert(index >= 0);                    \
    assert(index < this->size);            \
    this->array[index] = value;

#define ArrayPushBack(Type, this, value)                                 \
    assert(this != NULL);                                                \
    if (this->size == this->capacity) {                                  \
        this->capacity *= 2;                                             \
        this->array =                                                    \
            (Type *)realloc(this->array, this->capacity * sizeof(Type)); \
        assert(this->array != NULL);                                     \
    }                                                                    \
    this->array[this->size] = value;                                     \
    this->size++;

#define ArrayPushBack1(Type, this, values, len)                          \
    assert(this != NULL);                                                \
    assert(values != NULL);                                              \
    while (this->size + len > this->capacity) {                          \
        this->capacity *= 2;                                             \
        this->array =                                                    \
            (Type *)realloc(this->array, this->capacity * sizeof(Type)); \
        assert(this->array != NULL);                                     \
    }                                                                    \
    memcpy(this->array + this->size, values, len * sizeof(Type));        \
    this->size += len;

#endif  // RITSU_COLLECTION_ARRAY_H

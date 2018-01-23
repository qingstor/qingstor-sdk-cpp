#pragma once

#include "QsSdkOption.h"

#include <memory>
#include <stdlib.h>

namespace QingStor
{

template <typename T>
T *New()
{
    void *rawMemory = malloc(sizeof(T));
    T *constructedMemory = new (rawMemory) T();
    return constructedMemory;
}

template <typename T>
void Delete(T *pointerToT)
{
    if (pointerToT == NULL)
    {
        return;
    }
    pointerToT->~T();
    free(pointerToT);
}
}
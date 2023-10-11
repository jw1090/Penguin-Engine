#pragma once

#include "BlockAllocator.h"

namespace PenguinEngine::Core
{
    template<class DataType>
    class TypedAllocator : private BlockAllocator
    {
    public:
        TypedAllocator(const char* name, size_t capacity)
            : BlockAllocator(name, sizeof(DataType), capacity)
        {

        }

        template<class... Args>
        DataType* New(Args&&... args)
        {
            auto* instance = static_cast<DataType*>(Allocate());
            new(instance) DataType(std::forward<Args>(args)...); //placement new, calls constructor on a designate location

            return instance;
        }

        void Delete(DataType* ptr)
        {
            if (ptr == nullptr)
            {
                return;
            }

            ptr->~DataType();
            Free(ptr);
        }
    };
}
// Exercise 7-2 from C++ Crash Course

#include <cstddef>
#include <cstdio>
#include <new>

// Create a LargeBucket class that can hold up to 1MB. Extend Heap so that it
// gives a LargeBucket for allocations bigger than 4096 bytes. Throw
// std::bad_alloc if the properly-sized bucket can't be allocated.

struct Bucket {
    const static size_t data_size {4096};
    std::byte data[data_size];
};

struct LargeBucket {
    const static size_t data_size {1'000'000};
    std::byte data[data_size];
};

class Heap {
public:
    void* allocate(size_t bytes) {
        if (bytes > Bucket::data_size) {
            if (bytes > LargeBucket::data_size) throw std::bad_alloc{};
            return allocate_large_bucket();
        } else {
            for (size_t i{}; i < n_heap_buckets; i++) {
                if (!bucket_used[i]) {
                    bucket_used[i] = true;
                    return buckets[i].data;
                }
            }
            return allocate_large_bucket();
        }
    }

    void* allocate_large_bucket() {
        for (size_t i{}; i < n_heap_large_buckets; i++) {
            if (!large_bucket_used[i]) {
                large_bucket_used[i] = true;
                return buckets[i].data;
            }
        }
        throw std::bad_alloc{};
    }

    void free(void* p) {
        for (size_t i{}; i < n_heap_buckets; i++) {
            if (buckets[i].data == p) {
                large_bucket_used[i] = false;
                return;
            }
        }
    } 

    const static size_t n_heap_buckets {10};
    const static size_t n_heap_large_buckets {10};
    Bucket buckets[n_heap_buckets];
    bool bucket_used[n_heap_buckets];
    LargeBucket large_buckets[n_heap_buckets];
    bool large_bucket_used[n_heap_buckets];
};

Heap heap;

void* operator new(size_t n_bytes) {
    return heap.allocate(n_bytes);
}

void operator delete(void* p) {
    return heap.free(p);
}

int main() {
   printf("Buckets:          %p\n", heap.buckets); 
   printf("Large Buckets:    %p\n", heap.large_buckets);
   auto breakfast = new unsigned int {0xC0FFEE};
   auto dinner = new unsigned int {0xDEADBEEF};
   delete breakfast;
   delete dinner;
   try {
       while (true) {
           new char;
           printf("Allocated a char.\n");
       }
   } catch (const std::bad_alloc&) {
       printf("std::bad_alloc caught.\n");
   }
}

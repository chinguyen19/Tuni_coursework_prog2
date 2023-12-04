#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int greatest = *itemptr; // Initialize with the first element

        for (int i = 1; i < size; ++i) {
            if (*(itemptr + i) > greatest) {
                greatest = *(itemptr + i);
            }
        }

        return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = *itemptr; // Initialize with the first element

        while (itemptr < endptr) {
            if (*itemptr > greatest) {
                greatest = *itemptr;
            }
            ++itemptr;
        }

        return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while (itemptr < endptr) {
            *targetptr = *itemptr;
            ++itemptr;
            ++targetptr;
        }
}

void reverse(int *leftptr, int *rightptr)
{
    --rightptr; // Move rightptr to the last element

        while (leftptr < rightptr) {
            // Swap the elements at leftptr and rightptr
            int temp = *leftptr;
            *leftptr = *rightptr;
            *rightptr = temp;

            ++leftptr;
            --rightptr;
        }
}

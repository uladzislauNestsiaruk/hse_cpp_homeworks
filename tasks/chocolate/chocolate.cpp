#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    if (height * width == slices_amount) {
        return false;
    } else if (slices_amount % height == 0 && slices_amount / height <= width) {
        return true;
    } else if (slices_amount % width == 0 && slices_amount / width <= height) {
        return true;
    } else {
        return false;
    }
};
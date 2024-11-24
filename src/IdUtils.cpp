#include "IdUtils.hpp"
static int counter = 1;
namespace IdUtils {
int getUniqueId() {
    return counter++;
}
}

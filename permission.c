
#include "permission.h"

bool check_root() {
    return !getuid();
//    return true;
}
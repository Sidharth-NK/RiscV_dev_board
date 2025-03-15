#include <time.h>

// Simple busy-wait delay function
void delayForSeconds(unsigned seconds) {
    time_t timeout = time(NULL) + seconds;
    while (timeout > time(NULL));  // Wait for timeout
}

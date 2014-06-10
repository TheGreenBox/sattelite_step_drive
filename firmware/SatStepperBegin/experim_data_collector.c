#include <stdlib.h>
#include "state.h"
#include "sensors/encoder/encoder.h"
#include "experim_data_collector.h"

#define BUFFER_SIZE 1000

static uint16_t timeDeltaBuf[BUFFER_SIZE];
static int32_t encTicksBuf[BUFFER_SIZE];

static void encoderEntry() {
    static uint16_t index = 0;

    // if (index < BUFFER_SIZE - 1) {
        encTicksBuf[index] = gState.encoder.total;
        ++index;
    // }

    index %= BUFFER_SIZE;
}

static void timeDeltaEntry() {
    static uint16_t index = 0;

    // if (index < BUFFER_SIZE - 1) {
        timeDeltaBuf[index] = gState.encoder.invSpeed;
        ++index;
    // }

    index %= BUFFER_SIZE;
}

void enableDataLogging() {
    installDataLogger(encoderEntry);
    installDataLogger(timeDeltaEntry);
}

void disableDataLogging() {
    removeAllDataLoggers();
}

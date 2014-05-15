#include "modules_list.h"
#include "commutation_angle.h"

typedef void (* moduleExecuter)(void);
moduleExecuter controlModules[MODULE_LIST_END];
unsigned modulesStatus[MODULE_LIST_END] = {MODULE_DISABLED};

controlModules[COMMUT_ANGLE_MODULE] = &computeCommutationAngle;

void setModuleStatus(unsigned moduleId, unsigned status) {
    // TODO: add static assert moduleId < MODULE_ENABLED
    // and status == MODULE_ENABLED || status == MODULE_DISABLED

    modulesStatus[moduleId] = status;
}

void runEnabledModules() {
    for (unsigned moduleId = 0; moduleId < MODULE_LIST_END; ++moduleId) {
        if (modulesStatus[moduleId] == MODULE_ENABLED) {
            (*controlModules[moduleId])();
        }
    }
}

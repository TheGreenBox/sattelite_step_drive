enum {
    COMMUT_ANGLE_MODULE = 0,
    MODULE_LIST_END     = 1
};

enum {
    MODULE_DISABLED   = 0,
    MODULE_ENABLED    = 1
};

void setModuleStatus(unsigned moduleId, unsigned status);
void runEnabledModules();

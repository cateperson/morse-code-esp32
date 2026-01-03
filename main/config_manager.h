#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <stdbool.h>

void config_load(void);
bool config_save_and_apply(const char *json_str);

#endif

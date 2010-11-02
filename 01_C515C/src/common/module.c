/*
 * vim: set expandtab:
 */

#define MAX_MODULES     10

struct module   *modules[MAX_MODULES];
int              modules_map[MAX_MODULES];

int init_module_subsystem(void)
{
    int n;

    /* Mark all modules as unloaded */
    for (n = 0; n < MAX_MODULES; n++)
    {
        modules_map[n] = 0;
    }

    return 0;
}

/*
 * @brief   This registers a new module in the module subsystem
 *
 * @param   mod     The new module to be registered
 *
 * @return  > 0 if module is successfully register, <= 0 if module is not successfully
 *          registed
 */
int register_module(struct module *mod)
{
    int n;
    int new_module_index = -1;
    int rc = 0;

    /* find first free module position in module array */
    for (n = 0; n < MAX_MODULES; n++)
    {
        if (modules_map[n] == 0)
        {
            new_module_index = n;
            break;
        }
    }

    /* If we found a index for the new module we append it to the array on that position */
    if (new_module_index >= 0)
    {
        modules[new_module_index] = mod;
        rc = 1;
    }

    return rc;
}

/*
 * FIXME
 */
int unregister_module(struct module *mod)
{
    /* FIXME */
    return 0;
}

/* 
 * @brief   Initialize all registered modules
 */
void init_all_modules(void)
{
    int n;

    for (n = 0; n < MAX_MODULES; n++)
    {
        if (modules_map[n] > 0 && modules_map[n] != NULL)
        {
            modules_map[n]->init();
        }
    }
}

/*
 * @brief   Release all registered modules
 */
void release_all_modules(void)
{
    int n;

    for (n = 0; n < MAX_MODULES; n++)
    {
        if (modules_map[n] > 0 && modules_map[n] != NULL)
        {
            modules_map[n]->release();
        }
    }
}

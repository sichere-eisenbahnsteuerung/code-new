#ifndef _MODULE_H_
#define _MODULE_H_

struct module
{
    const char      *name;
    int (*init)     (void);
    int (*release)  (void);
};

int register_module     (struct module *module);
int unregister_module   (struct module *module);

#endif


#ifndef _MODULE_H_
#define _MODULE_H_

struct module
{
	const char		*name;
	int (*init)		(void);
	int (*release)	(void);
};

#endif


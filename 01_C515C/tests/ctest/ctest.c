
#include <linuxlist.h>
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct _ctest_test_func_container
{
    struct llist_head list;
    ctest_test_func func;
    char *name;
};

struct _ctest_suite
{
    char *name;
    struct llist_head list;
    struct llist_head func_list;
};

struct _ctest_runner
{
    struct llist_head suite_list;
};

#define LLIST_INIT_MEMBER(p, member) \
    p->member.next = &p->member; \
    p->member.prev = &p->member;

static ctest_wait_for_func current_wait_for_func = NULL;

/* 
 * Test-Suite
 */

ctest_suite *ctest_suite_create(const char *name)
{
    ctest_suite *suite = NULL;

    suite = (ctest_suite*) malloc(sizeof(ctest_suite));
    suite->name = strdup(name);
    LLIST_INIT_MEMBER(suite, func_list);

    return suite;
}

void ctest_suite_add_test_func_with_name(ctest_suite *suite, const char *name, ctest_test_func *test_func)
{
    struct _ctest_test_func_container *fcnt = NULL;

    assert(suite != NULL);
    assert(test_func != NULL);

    /* Neuen Container für die Test-Funktion anlegen */
    fcnt = (struct _ctest_test_func_container*) malloc(sizeof(struct _ctest_test_func_container));
    fcnt->func = test_func;
    fcnt->name = strdup(name);

    /* Der neue Test-Container gehört zu der übergebenen Test-Suite */
    llist_add(&fcnt->list, &suite->func_list);
}

void ctest_suite_free(ctest_suite *suite)
{
    struct _ctest_test_func_container *fcnt;

    assert(suite != NULL);

    /* Alle anhängenden Test-Funktionen freigeben */
    if (llist_empty(&suite->func_list))
    {
        llist_for_each_entry(fcnt, &suite->func_list, list)
        {
            llist_del(&fcnt->list);
            if (fcnt->name != NULL)
            {
                free(fcnt->name);
            }
            free(fcnt);
        }
    }

    /* Speicherplatz des Test-Suite Objektes freigeben */
    if (suite->name != NULL)
    {
        free(suite->name);
    }
    free(suite);
}

void _ctest_suite_execute_all(ctest_suite *suite)
{
    struct _ctest_test_func_container *fcnt;
    int rc = 0;

    assert(suite != NULL);

    if (!llist_empty(&suite->func_list))
    {
        llist_for_each_entry(fcnt, &suite->func_list, list)
        {
            rc = fcnt->func();
            if (rc < 0)
            {
                printf("[SUITE: %s] test func '%s': FAILED\n", suite->name, fcnt->name);
            }
            else
            {
                printf("[SUITE: %s] test func '%s': PASSED\n", suite->name, fcnt->name);
            }
        }
    }
}


/*
 * Test-Runner
 */

ctest_runner *ctest_runner_create(void)
{
    ctest_runner *runner = NULL;

    runner = (ctest_runner*) malloc(sizeof(ctest_runner));
    LLIST_INIT_MEMBER(runner, suite_list);
 
    return runner;
}

void ctest_runner_add_suite(ctest_runner *runner, ctest_suite *suite)
{
    assert(runner != NULL);
    assert(suite != NULL);

    llist_add(&suite->list, &runner->suite_list);
}

void ctest_runner_execute_all(ctest_runner *runner)
{
    ctest_suite *suite;

    assert(runner != NULL);


    if (!llist_empty(&runner->suite_list))
    {
        llist_for_each_entry(suite, &runner->suite_list, list)
        {
            _ctest_suite_execute_all(suite);
        }
    }
}

void ctest_runner_free(ctest_runner *runner)
{
    ctest_suite *suite = NULL;

    assert(runner != NULL);

    /* Alle anhängigen Test-Suite ebenfalls freigeben und aus der Liste löschen */
    if (llist_empty(&runner->suite_list))
    {
        llist_for_each_entry(suite, &runner->suite_list, list) 
        {
            ctest_suite_free(suite);
            llist_del(&suite->list);
        }
    }

    /* Abschliessend geben wir den Speicherplatz des Test-Runners frei */
    free(runner);
    runner = NULL;
}

void ctest_register_wait_for_handler(ctest_wait_for_func *func)
{
    current_wait_for_func = func;
}

void ctest_trigger_wait_for_handler(void)
{
    if (current_wait_for_func != NULL)
    {
        current_wait_for_func();
    }
}

int ctest_assert_is_true(unsigned int value, char *message, const char *file, unsigned int line)
{
    int rc = value ? 0 : -1;

    if (rc < 0)
    {
        printf("[%s, %i]: assert_is_true FAILED: %s\n", file, line, message); 
    }
    
    return rc;
}

int ctest_assert_is_false(unsigned int value, char *message, const char *file, unsigned int line)
{
    int rc = !value ? 0 : -1;

    if (rc < 0)
    {
        printf("[%s, %i]: assert_is_false FAILED: %s\n", file, line, message); 
    }
    
    return rc;
}

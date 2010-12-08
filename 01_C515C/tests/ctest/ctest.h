/**
 * @file ctest.h
 * @ingroup ctest
 * @brief Einfaches UnitTest-Framework
 *
 * @author Simon Busch
 * @date 08.12.2010
 */
#ifndef _CTEST_H_
#define _CTEST_H_

typedef struct  _ctest_suite ctest_suite;
typedef struct  _ctest_runner ctest_runner;
typedef int     (*ctest_test_func)(void);
typedef void    (*ctest_wait_for_func)(void);

#define START_TEST_FUNC(name) int name(void)
#define END_TEST_FUNC

/*
 * @brief Erstellt eine neue Test-Suite mit einem bezeichnemden Namen
 *
 * @param name Namen der Suite
 * @return Suite-Objekt
 */
ctest_suite     *ctest_suite_create(const char *name);

/*
 * @brief Freigeben des verwendeten Speichers einer Test-Suite
 *
 * @param Suite, die nicht weiter verwendet werden soll
 */
void             ctest_suite_free(ctest_suite *suite);

/*
 * @brief Hinzufügen einer einzelnen Test-Funktion in eine Test-Suite
 *
 * @param suite Test-Suite der die neue Test-Funktion hinzugefügt werden soll
 * @param test_func Test-Funktion die der Test-Suite hinzugefügt wird
 */
void             ctest_suite_add_test_func_with_name(ctest_suite *suite, const char *name, ctest_test_func test_func);

#define ctest_suite_add_test_func(suite, func) ctest_suite_add_test_func_with_name(suite, #func, func)

/*
 * @brief Erstellt einen Test-Runner
 *
 * @return Test-Runner Objekt
 */
ctest_runner    *ctest_runner_create(void);

/*
 * @brief Freigeben eines nicht mehr verwendeten Test-Runner Objektes
 *
 * @param runner Test-Runner Objekt
 */
void             ctest_runner_free(ctest_runner *runner);

/*
 * @brief Mehre Test-Suite können einem Test-Runner hinzugefügt werden und gemeinsam zur
 *        Ausführung gebracht werden.
 * 
 * @param runner Test-Runner dem die Test-Suite hinzugefügt wird
 * @param suite Test-Suite die dem Test-Runner hinzugefügt wird
 */
void             ctest_runner_add_suite(ctest_runner *runner, ctest_suite *suite);

/*
 * @brief Ausführen der Tests in allen Test-Suiten, die dem Test-Runner hinzugefügt wurden
 *
 * @param runner Test-Runner der zur Ausführung gebracht werden soll
 */
void             ctest_runner_execute_all(ctest_runner *runner);

/*
 * @brief Setzen des aktuellen Handlers für das WAIT_FOR Makro. Sobald das WAIT_FOR Makro
 *        im Code aufgerufen wird, wird die übergebene Callback-Funktion aufgerufen.
 *
 * @param func Callback-Funktion die aufgerufen wird, sobald das WAIT_FOR-Makro aufgerufen
 *             wird
 */
void             ctest_register_wait_for_handler(ctest_wait_for_func func);

/*
 * @brief Ruft den aktuell gesetzten WAIT_FOR-Makro Handler auf. Diese Funktion sollte
 *        nicht  manuell aufgerufen werden, sondern sie wird innerhalb des neudefinierten
 *        WAIT_FOR-Makros automatisch aufgerufen.
 */
void             ctest_trigger_wait_for_handler(void);

#ifdef WAIT_FOR
#undef WAIT_FOR
#endif
/* 
 * @brief Redefinition des WAIT_FOR-Makros, die bei jedem Warte-Schleifen-Durchlauf die
 *        ctest_trigger_wait_for_handler Funktion aufruft.
 */
#define WAIT_FOR(condition) \
    while(!condition) { ctest_trigger_wait_for_handler(); } 

int ctest_assert_is_true(unsigned int value, char *message, const char *file, unsigned int line);
int ctest_assert_is_false(unsigned int value, char *message, const char *file, unsigned int line);

#define assert_is_true(value, message) if (ctest_assert_is_true(value, message, __FILE__, __LINE__) < 0) return -1
#define assert_is_false(value, message) if (ctest_assert_is_true(value, message, __FILE__, __LINE__) < 0) return -1

#endif


/**
 * @file
 * @ingroup unittest
 * @brief Leitzentrale Test-Script
 *
 * Führt den Leitzentrale-Unittest durch (Initialisierung und zyklisches
 * Senden der Fahrbefehle).
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */

#include <test_helper.h>
#include <leitzentrale.h>
#include <betriebsmittelverwaltung.h>
#include <xpressnet_shared_memory.h>

/**
 * @brief Leitzentrale initialisieren.
 * @pre Keine.
 */
START_TEST_FUNC(test_leitzentrale_init)
{
    leitzentrale_init();
}
END_TEST_FUNC

/**
 * @brief Wechsel zwischen den Fahrgeschwindigkeiten testen.
 * @pre Keine.
 */
START_TEST_FUNC(test_leitzentrale_fahrstufe_wechseln)
{
    int i, g;

    for(g=0; g<10; g++)
    {
        streckenbefehl_xpressnet.target = IDLE;
        for(i=0;i<1000;i++)
        {
            timer_value[TIMER_LEITZENTRALE] = i;
            leitzentrale_work();
            assert_is_true(streckenbefehl_xpressnet.target == IDLE, "Aktion vor 10sec");
        }

        timer_value[TIMER_LEITZENTRALE] = 1000;
        leitzentrale_work();
        assert_is_true(streckenbefehl_xpressnet.target == LOK_BLACK, "Falsches Steuerziel!");
        assert_is_true(streckenbefehl_xpressnet.command == 0x01, "Falscher Steuerbefehl!");

        streckenbefehl_xpressnet.target = IDLE;
        for(i=0;i<1000;i+=2) 
        {
            timer_value[TIMER_LEITZENTRALE] = i;
            leitzentrale_work();
            assert_is_true(streckenbefehl_xpressnet.target == IDLE, "Aktion vor 10sec");
        }

        timer_value[TIMER_LEITZENTRALE] = 1001;
        leitzentrale_work();
        assert_is_true(streckenbefehl_xpressnet.target == LOK_BLACK, "Falsches Steuerziel!");
        assert_is_true(streckenbefehl_xpressnet.command == 0x03, "Falscher Steuerbefehl!");

        timer_value[TIMER_LEITZENTRALE] = 1001;
        leitzentrale_work();
        assert_is_true(streckenbefehl_xpressnet.target == LOK_BLACK, "Falsches Steuerziel (überschrieben)!");
        assert_is_true(streckenbefehl_xpressnet.command == 0x03, "Falscher Steuerbefehl! (überschrieben)");

        streckenbefehl_xpressnet.target = IDLE;
        leitzentrale_work();
        assert_is_true(streckenbefehl_xpressnet.target == LOK_BLACK, "Falsches Steuerziel (überschrieben)!");
        assert_is_true(streckenbefehl_xpressnet.command == 0x01, "Falscher Steuerbefehl! (überschrieben)");

        timer_value[TIMER_LEITZENTRALE] = 999;
        leitzentrale_work();
        assert_is_true(streckenbefehl_xpressnet.target == LOK_BLACK, "Falsches Steuerziel (überschrieben)!");
        assert_is_true(streckenbefehl_xpressnet.command == 0x01, "Falscher Steuerbefehl! (überschrieben)");

        timer_value[TIMER_LEITZENTRALE] = 1000;
        streckenbefehl_xpressnet.target = IDLE;
        leitzentrale_work();
        assert_is_true(streckenbefehl_xpressnet.target == LOK_BLACK, "Falsches Steuerziel (überschrieben)!");
        assert_is_true(streckenbefehl_xpressnet.command == 0x03, "Falscher Steuerbefehl! (überschrieben)");
    }
}
END_TEST_FUNC

/**
 * @brief Erstellt die Test Suite
 *
 * Erstellt eine Test Suite, die Leitzentrale testet.
 */
ctest_suite *test_leitzentrale_create_suite(void)
{
    ctest_suite *suite = ctest_suite_create("Leitzentrale");
    
    ctest_suite_add_test_func(suite, test_leitzentrale_init);
    ctest_suite_add_test_func(suite, test_leitzentrale_fahrstufe_wechseln);

    return suite;
}

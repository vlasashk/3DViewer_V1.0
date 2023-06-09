#include "./s21_3dviewer_tests.h"

#include <check.h>

int main() {
  SRunner *runner;
  Suite *list[] = {s21_common_suite()};

  int tests_count = sizeof(list) / sizeof(list[0]);
  int failed = 0;

  runner = srunner_create(list[0]);
  for (int i = 1; i < tests_count; i++) srunner_add_suite(runner, list[i]);

  srunner_run_all(runner, CK_NORMAL);  // CK_VERBOSE - ALL | CK_ENV - ONLY FAILS
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  printf("\nFAILED TESTS ARE: %d \n\n", failed);

  return (!failed) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// WRITE YOUR OWN
// Build  gcc -I ./include/ unit_test_strcmp.c str_cmp.c -o unit_test_str_cmp.bin

#include <acutest.h>
#include <stdint.h>
#include <str_cmp.h>

struct TestVector {
  const int index;
  const char *s1;
  const char *s2;
  int expected;
};

struct TestVector test_vectors[] = {
    // Inorder,Preorder,Postorder(Expected)
    {0, "a", "b", 1},
    {1, "apple", "appl@ ", 1},
    {2, "apple and oranges", "apple and oranges", 0},
    {3, "123456", "123456", 0},
    {4, "342342;", "afasdfsafd;", 1},
    {5, "Helloworld", "helloworld", 1},
    {6, "Hello", "Helloworld", 1},
    {7, "", "",0},
    {6, "Helloworld", "Hello", 1},
};

void test(void) {
  for (int i = 0; i < 9; i++) {
    int result = my_str_cmp(test_vectors[i].s1, test_vectors[i].s2);

    TEST_CHECK(result == test_vectors[i].expected);
    TEST_MSG("String s1: %s", test_vectors[i].s1);
    TEST_MSG("String s2: %s", test_vectors[i].s2);
    TEST_MSG("Test index: %d", test_vectors[i].index);
    TEST_MSG("Expected: %d, Getting: %d", test_vectors[i].expected, result);
  }
}

TEST_LIST = {{"Test", test}, {NULL, NULL}};
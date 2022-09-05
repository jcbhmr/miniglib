#include <stdio.h>
#include <stdlib.h>

#include <check.h>

#include "glist.h"

int32_t simple_comp_func(const void *a, const void *b)
{
    return ((int32_t) (int64_t) a) - ((int32_t) (int64_t) b);
}


START_TEST(test_glist_append)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 1);

    list = g_list_append(list, "Element 2");
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 2);

    list = g_list_append(list, "Element 3");
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    ck_assert_str_eq(list->data, "Element 1");
    ck_assert_str_eq(list->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->data, "Element 3");

    GList *last = list->next->next;

    ck_assert_str_eq(last->data, "Element 3");
    ck_assert_str_eq(last->prev->data, "Element 2");
    ck_assert_str_eq(last->prev->prev->data, "Element 1");

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_prepend)
{
    GList *list = NULL;
    list = g_list_prepend(list, "Element 1");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 1);

    list = g_list_prepend(list, "Element 2");
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 2);

    list = g_list_prepend(list, "Element 3");
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    ck_assert_str_eq(list->data, "Element 3");
    ck_assert_str_eq(list->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->data, "Element 1");

    GList *last = list->next->next;

    ck_assert_str_eq(last->data, "Element 1");
    ck_assert_str_eq(last->prev->data, "Element 2");
    ck_assert_str_eq(last->prev->prev->data, "Element 3");

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_insert)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    g_list_insert(list, "New Element", 1);

    ck_assert_str_eq(list->data, "Element 1");
    ck_assert_str_eq(list->next->data, "New Element");
    ck_assert_str_eq(list->next->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->next->data, "Element 3");

    list = g_list_reverse(list);

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 4);

    ck_assert_str_eq(list->data, "Element 3");
    ck_assert_str_eq(list->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->data, "New Element");
    ck_assert_str_eq(list->next->next->next->data, "Element 1");

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_insert_before)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    g_list_insert_before(list, list->next, "New Element");

    ck_assert_str_eq(list->data, "Element 1");
    ck_assert_str_eq(list->next->data, "New Element");
    ck_assert_str_eq(list->next->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->next->data, "Element 3");

    list = g_list_reverse(list);

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 4);

    ck_assert_str_eq(list->data, "Element 3");
    ck_assert_str_eq(list->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->data, "New Element");
    ck_assert_str_eq(list->next->next->next->data, "Element 1");

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_remove)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    list = g_list_remove(list, "Element 2");
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 2);

    ck_assert_str_eq(list->data, "Element 1");
    ck_assert_str_eq(list->next->data, "Element 3");

    list = g_list_remove(list, "Element 3");
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 1);

    ck_assert_str_eq(list->data, "Element 1");

    list = g_list_remove(list, "Element 1");
    ck_assert_ptr_null(list);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_remove_link)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    list = g_list_remove_link(list, list->next);
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 2);

    ck_assert_str_eq(list->data, "Element 1");
    ck_assert_str_eq(list->next->data, "Element 3");

    list = g_list_remove_link(list, list->next);
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 1);

    ck_assert_str_eq(list->data, "Element 1");

    list = g_list_remove_link(list, list);
    ck_assert_ptr_null(list);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_delete_link)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    list = g_list_delete_link(list, list->next);
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 2);

    ck_assert_str_eq(list->data, "Element 1");
    ck_assert_str_eq(list->next->data, "Element 3");

    list = g_list_delete_link(list, list->next);
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 1);

    ck_assert_str_eq(list->data, "Element 1");

    list = g_list_delete_link(list, list);
    ck_assert_ptr_null(list);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_remove_all)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Delete Me");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");
    list = g_list_append(list, "Delete Me");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 5);

    list = g_list_remove_all(list, "Delete Me");
    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    ck_assert_str_eq(list->data, "Element 1");
    ck_assert_str_eq(list->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->data, "Element 3");

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_copy)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    GList *new_list = g_list_copy(list);
    ck_assert_ptr_nonnull(new_list);
    ck_assert_int_eq(g_list_length(new_list), 3);

    ck_assert_str_eq(new_list->data, "Element 1");
    ck_assert_str_eq(new_list->next->data, "Element 2");
    ck_assert_str_eq(new_list->next->next->data, "Element 3");

    ck_assert_ptr_ne(new_list, list);
    ck_assert_ptr_ne(new_list->next, list->next);
    ck_assert_ptr_ne(new_list->next->next, list->next->next);

    g_list_free(list);
    g_list_free(new_list);
}
END_TEST

START_TEST(test_glist_concat)
{
    GList *list1 = NULL;
    list1 = g_list_append(list1, "Element 1");
    list1 = g_list_append(list1, "Element 2");
    list1 = g_list_append(list1, "Element 3");

    ck_assert_ptr_nonnull(list1);
    ck_assert_int_eq(g_list_length(list1), 3);

    GList *list2 = NULL;
    list2 = g_list_append(list2, "List 2 Element 1");
    list2 = g_list_append(list2, "List 2 Element 2");

    ck_assert_ptr_nonnull(list2);
    ck_assert_int_eq(g_list_length(list2), 2);

    list1 = g_list_concat(list1, list2);

    ck_assert_str_eq(list1->data, "Element 1");
    ck_assert_str_eq(list1->next->data, "Element 2");
    ck_assert_str_eq(list1->next->next->data, "Element 3");
    ck_assert_str_eq(list1->next->next->next->data, "List 2 Element 1");
    ck_assert_str_eq(list1->next->next->next->next->data, "List 2 Element 2");

    g_list_free(list1);
}
END_TEST

START_TEST(test_glist_reverse)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    ck_assert_str_eq(list->data, "Element 1");
    ck_assert_str_eq(list->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->data, "Element 3");

    list = g_list_reverse(list);

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(g_list_length(list), 3);

    ck_assert_str_eq(list->data, "Element 3");
    ck_assert_str_eq(list->next->data, "Element 2");
    ck_assert_str_eq(list->next->next->data, "Element 1");

    g_list_free(list);
}
END_TEST

uint32_t foreach_num_values = 3;

void test_foreach(void *data, void *user_data)
{
    static GList *expected_values = NULL;

    if (expected_values == NULL) {
        expected_values = g_list_append(expected_values, "Element 1");
        expected_values = g_list_append(expected_values, "Element 2");
        expected_values = g_list_append(expected_values, "Element 3");
    }

    ck_assert_str_eq("USER DATA", user_data);
    ck_assert_str_eq(data, expected_values->data);
    expected_values = g_list_delete_link(expected_values, expected_values);
    foreach_num_values--;
}

START_TEST(test_glist_foreach)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    char *user_data = "USER DATA";

    ck_assert_int_eq(foreach_num_values, 3);
    g_list_foreach(list, test_foreach, user_data);
    ck_assert_int_eq(foreach_num_values, 0);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_first)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_eq(g_list_first(list), list);
    ck_assert_ptr_eq(g_list_first(list->next), list);
    ck_assert_ptr_eq(g_list_first(list->next->next), list);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_last)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    GList *last = list->next->next;

    ck_assert_ptr_eq(g_list_last(list), last);
    ck_assert_ptr_eq(g_list_last(list->next), last);
    ck_assert_ptr_eq(g_list_last(list->next->next), last);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_nth)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_ptr_eq(g_list_nth(list, -2), NULL);
    ck_assert_ptr_eq(g_list_nth(list, -1), NULL);
    ck_assert_ptr_eq(g_list_nth(list, 0), list);
    ck_assert_ptr_eq(g_list_nth(list, 1), list->next);
    ck_assert_ptr_eq(g_list_nth(list, 2), list->next->next);
    ck_assert_ptr_eq(g_list_nth(list, 3), NULL);
    ck_assert_ptr_eq(g_list_nth(list, 4), NULL);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_nth_data)
{
    GList *list = NULL;

    char *element1 = "Element 1";
    char *element2 = "Element 2";
    char *element3 = "Element 3";

    list = g_list_append(list, element1);
    list = g_list_append(list, element2);
    list = g_list_append(list, element3);

    ck_assert_ptr_eq(g_list_nth_data(list, -2), NULL);
    ck_assert_ptr_eq(g_list_nth_data(list, -1), NULL);
    ck_assert_ptr_eq(g_list_nth_data(list, 0), element1);
    ck_assert_ptr_eq(g_list_nth_data(list, 1), element2);
    ck_assert_ptr_eq(g_list_nth_data(list, 2), element3);
    ck_assert_ptr_eq(g_list_nth_data(list, 3), NULL);
    ck_assert_ptr_eq(g_list_nth_data(list, 4), NULL);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_nth_prev)
{
    GList *list = NULL;
    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    GList *last = list->next->next;

    ck_assert_ptr_eq(g_list_nth_prev(last, -2), NULL);
    ck_assert_ptr_eq(g_list_nth_prev(last, -1), NULL);
    ck_assert_ptr_eq(g_list_nth_prev(last, 0), last);
    ck_assert_ptr_eq(g_list_nth_prev(last, 1), last->prev);
    ck_assert_ptr_eq(g_list_nth_prev(last, 2), last->prev->prev);
    ck_assert_ptr_eq(g_list_nth_prev(last, 3), NULL);
    ck_assert_ptr_eq(g_list_nth_prev(last, 4), NULL);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_find)
{
    GList *list = NULL;

    char *element1 = "Element 1";
    char *element2 = "Element 2";
    char *element3 = "Element 3";

    list = g_list_append(list, element1);
    list = g_list_append(list, element2);
    list = g_list_append(list, element3);

    ck_assert_ptr_eq(g_list_find(list, element1), list);
    ck_assert_ptr_eq(g_list_find(list, element2), list->next);
    ck_assert_ptr_eq(g_list_find(list, element3), list->next->next);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_find_custom)
{
    GList *list = NULL;

    char *element1 = "Element 1";
    char *element2 = "Element 2";
    char *element3 = "Element 3";

    list = g_list_append(list, element1);
    list = g_list_append(list, element2);
    list = g_list_append(list, element3);

    ck_assert_ptr_eq(g_list_find_custom(list, element1, simple_comp_func), list);
    ck_assert_ptr_eq(g_list_find_custom(list, element2, simple_comp_func), list->next);
    ck_assert_ptr_eq(g_list_find_custom(list, element3, simple_comp_func), list->next->next);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_position)
{
    GList *list = NULL;

    list = g_list_append(list, "Element 1");
    list = g_list_append(list, "Element 2");
    list = g_list_append(list, "Element 3");

    ck_assert_int_eq(g_list_position(list, list), 0);
    ck_assert_int_eq(g_list_position(list, list->next), 1);
    ck_assert_int_eq(g_list_position(list, list->next->next), 2);
    ck_assert_int_eq(g_list_position(list, NULL), -1);

    g_list_free(list);
}
END_TEST

START_TEST(test_glist_index)
{
    GList *list = NULL;

    char *element1 = "Element 1";
    char *element2 = "Element 2";
    char *element3 = "Element 3";

    list = g_list_append(list, element1);
    list = g_list_append(list, element2);
    list = g_list_append(list, element3);

    ck_assert_int_eq(g_list_index(list, element1), 0);
    ck_assert_int_eq(g_list_index(list, element2), 1);
    ck_assert_int_eq(g_list_index(list, element3), 2);
    ck_assert_int_eq(g_list_index(list, NULL), -1);

    g_list_free(list);
}
END_TEST

Suite* glist_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("GList");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_glist_append);
    tcase_add_test(tc_core, test_glist_prepend);
    tcase_add_test(tc_core, test_glist_insert);
    tcase_add_test(tc_core, test_glist_insert_before);
    tcase_add_test(tc_core, test_glist_remove);
    tcase_add_test(tc_core, test_glist_remove_link);
    tcase_add_test(tc_core, test_glist_delete_link);
    tcase_add_test(tc_core, test_glist_remove_all);
    tcase_add_test(tc_core, test_glist_copy);
    tcase_add_test(tc_core, test_glist_reverse);
    tcase_add_test(tc_core, test_glist_concat);
    tcase_add_test(tc_core, test_glist_foreach);
    tcase_add_test(tc_core, test_glist_first);
    tcase_add_test(tc_core, test_glist_last);
    tcase_add_test(tc_core, test_glist_nth);
    tcase_add_test(tc_core, test_glist_nth_data);
    tcase_add_test(tc_core, test_glist_nth_prev);
    tcase_add_test(tc_core, test_glist_find);
    tcase_add_test(tc_core, test_glist_find_custom);
    tcase_add_test(tc_core, test_glist_position);
    tcase_add_test(tc_core, test_glist_index);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, char **argv)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = glist_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

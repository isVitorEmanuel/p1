#include <array>
#include <cassert>   // assert()
#include <iostream>  // cout, endl
#include <iterator>  // std::begin(), std::end()
#include <random>    // random_device, mt19937

// The test manager header
#include "include/tm/test_manager.h"

// The graal header in which the solution is coded.
#include "graal.h"

#define which_lib graal // uncomment this if you wanna run the graal library
// #define which_lib std  // uncomment this if you wanna run the std library.

int main() {
  // Creates a test manager for the DAL class.
  TestManager tm{ "Graal Test Suite" };

  {
    //=== Test #1
    BEGIN_TEST(tm, "MinMax1", "Unique Values Sorted.");
    // DISABLE();
    std::array A{ 1, 2, 3, 4, 5 };

    // const auto [ min, max ] = graal::minmax( std::begin(A), std::end(A), std::less< int >() );
    auto result = which_lib::minmax(std::begin(A), std::end(A), std::less<>());
    auto min = result.first;
    auto max = result.second;

    EXPECT_NE(min, nullptr);
    EXPECT_EQ(min, std::begin(A));
    EXPECT_EQ(*min, 1);

    EXPECT_NE(max, nullptr);
    EXPECT_EQ(max, std::prev(std::end(A)));
    EXPECT_EQ(*max, 5);
  }

  {
    //=== Test #1
    BEGIN_TEST(tm, "MinMax2", "Unique Values Reverse Sorted.");
    // DISABLE();
    std::array A{ 5, 4, 3, 2, 1 };

    // const auto [ min, max ] = graal::minmax( std::begin(A), std::end(A), std::less< int >() );
    auto result = which_lib::minmax(std::begin(A), std::end(A), std::less<>());
    auto min = result.first;
    auto max = result.second;

    EXPECT_NE(min, nullptr);
    EXPECT_EQ(min, std::prev(std::end(A)));
    EXPECT_EQ(*min, 1);

    EXPECT_NE(max, nullptr);
    EXPECT_EQ(max, std::begin(A));
    EXPECT_EQ(*max, 5);
  }

  {
    BEGIN_TEST(tm, "MinMax3", "All Equal.");
    // DISABLE();
    std::array A{ 1, 1, 1, 1, 1 };

    // const auto [ min, max ] = graal::minmax( std::begin(A), std::end(A), std::less< int >() );
    auto result = which_lib::minmax(std::begin(A), std::end(A), std::less<>());
    auto min = result.first;
    auto max = result.second;
    EXPECT_NE(min, nullptr);
    EXPECT_EQ(min, std::begin(A));
    EXPECT_EQ(*min, 1);

    EXPECT_NE(max, nullptr);
    EXPECT_EQ(max, std::prev(std::end(A)));
    EXPECT_EQ(*max, 1);
  }

  {
    BEGIN_TEST(tm, "MinMax4", "Unique Values Random Order");
    std::array A{ 2, 3, 5, 4, 1 };

    // const auto [ min, max ] = graal::minmax( std::begin(A), std::end(A), std::less< int >() );
    // const auto [ emin, emax ] = std::minmax_element( std::begin(A), std::end(A) );
    auto result = which_lib::minmax(std::begin(A), std::end(A), std::less<>());
    auto min = result.first;
    auto max = result.second;
    auto eresult = std::minmax_element(std::begin(A), std::end(A));
    auto emin = eresult.first;
    auto emax = eresult.second;

    EXPECT_NE(min, nullptr);
    EXPECT_EQ(min, emin);
    EXPECT_EQ(*min, 1);

    EXPECT_NE(max, nullptr);
    EXPECT_EQ(max, emax);
    EXPECT_EQ(*max, 5);
  }

  {
    BEGIN_TEST(tm, "MinMax5", "RepeatedValuesRandomOrder");
    std::array A{ 2, 3, 2, 5, 1, 4, 5, 4, 1 };

    // const auto [ min, max ] = graal::minmax( std::begin(A), std::end(A), std::less< int >() );
    // const auto [ emin, emax ] = std::minmax_element( std::begin(A), std::end(A) );
    auto result = which_lib::minmax(std::begin(A), std::end(A), std::less<>());
    auto min = result.first;
    auto max = result.second;
    auto eresult = std::minmax_element(std::begin(A), std::end(A));
    auto emin = eresult.first;
    auto emax = eresult.second;
    EXPECT_NE(min, nullptr);
    EXPECT_EQ(min, emin);
    EXPECT_EQ(*min, 1);

    EXPECT_NE(max, nullptr);
    EXPECT_EQ(max, emax);
    EXPECT_EQ(*max, 5);
  }

  {
    BEGIN_TEST(tm, "MinMax6", "EmptyList");
    std::array A{ 1 };

    // const auto [ min, max ] = graal::minmax( std::begin(A), std::begin(A), std::less< int >() );
    // const auto [ emin, emax ] = std::minmax_element( std::begin(A), std::begin(A) );
    auto result = which_lib::minmax(std::begin(A), std::begin(A), std::less<>());
    auto min = result.first;
    auto max = result.second;
    auto eresult = std::minmax_element(std::begin(A), std::begin(A));
    auto emin = eresult.first;
    auto emax = eresult.second;

    EXPECT_NE(min, nullptr);
    EXPECT_EQ(min, emin);
    EXPECT_EQ(*min, 1);

    EXPECT_NE(max, nullptr);
    EXPECT_EQ(max, emax);
    EXPECT_EQ(*max, 1);
  }

  {
    BEGIN_TEST(tm, "MinMax7", "SingleElement ");
    std::array A{ 1 };

    // const auto [ min, max ] = graal::minmax( std::begin(A), std::end(A), std::less< int >() );
    // const auto [ emin, emax ] = std::minmax_element( std::begin(A), std::end(A) );
    auto result = which_lib::minmax(std::begin(A), std::end(A), std::less<>());
    auto min = result.first;
    auto max = result.second;
    auto eresult = std::minmax_element(std::begin(A), std::end(A));
    auto emin = eresult.first;
    auto emax = eresult.second;

    EXPECT_NE(min, nullptr);
    EXPECT_EQ(min, emin);
    EXPECT_EQ(*min, 1);

    EXPECT_NE(max, nullptr);
    EXPECT_EQ(max, emax);
    EXPECT_EQ(*max, 1);
  }

  //== Reverse

  {
    BEGIN_TEST(tm, "Reverse", "ReverseEntireArrayEven");
    std::array A{ 1, 2, 3, 4, 5, 6 };
    std::array result{ 6, 5, 4, 3, 2, 1 };

    which_lib::reverse(std::begin(A), std::end(A));

    EXPECT_TRUE(std::equal(std::begin(A), std::end(A), std::begin(result)));
  }

  {
    BEGIN_TEST(tm, "Reverse2", "ReverseEntireArrayOdd");
    std::array A{ 1, 2, 3, 4, 5 };
    std::array A_E{ 5, 4, 3, 2, 1 };

    which_lib::reverse(std::begin(A), std::end(A));
    EXPECT_TRUE(std::equal(std::begin(A), std::end(A), std::begin(A_E)));
  }

  {
    BEGIN_TEST(tm, "Reverse3", "ReversePartOfArrayEven");
    std::array A{ 1, 2, 3, 4, 5, 6, 7 };
    std::array A_E{ 1, 2, 6, 5, 4, 3, 7 };

    which_lib::reverse(std::begin(A) + 2, std::begin(A) + 6);
    EXPECT_TRUE(std::equal(std::begin(A), std::end(A), std::begin(A_E)));
  }

  {
    BEGIN_TEST(tm, "Reverse4", "ReversePartOfArrayOdd");
    std::array A{ 1, 2, 3, 4, 5, 6, 7 };
    std::array A_E{ 1, 6, 5, 4, 3, 2, 7 };

    which_lib::reverse(std::begin(A) + 1, std::begin(A) + 6);
    EXPECT_TRUE(std::equal(std::begin(A), std::end(A), std::begin(A_E)));
  }

  //== Copy

  {
    BEGIN_TEST(tm, "Copy", "CopyEntireArray");
    std::array A{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
    std::array A_E{ 'a', 'a', 'a', 'a', 'a', 'a', 'a' };

    which_lib::copy(std::begin(A), std::end(A), std::begin(A_E));
    EXPECT_TRUE(std::equal(std::begin(A), std::end(A), std::begin(A_E)));
  }

  {
    BEGIN_TEST(tm, "Copy2", "CopyPartOfArray");
    std::array A{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
    std::array A_E{ 'a', 'b', 'a', 'a', 'a', 'a', 'a' };

    which_lib::copy(std::begin(A) + 2, std::end(A), std::begin(A_E) + 2);
    EXPECT_TRUE(std::equal(std::begin(A), std::end(A), std::begin(A_E)));
  }

  {
    BEGIN_TEST(tm, "Copy3", "CopyFinalPartOfArray");
    std::array A{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
    std::array A_E{ 'a', 'b', 'c', 'd', 'e', 'b', 'a' };

    which_lib::copy(std::begin(A) + 5, std::end(A), std::begin(A_E) + 5);
    EXPECT_TRUE(std::equal(std::begin(A), std::end(A), std::begin(A_E)));
  }

  {
    BEGIN_TEST(tm, "Copy4", "CopySingleElementArray");
    std::array A{ 'a' };
    std::array A_E{ 'x' };

    which_lib::copy(std::begin(A), std::end(A), std::begin(A_E));
    EXPECT_TRUE(std::equal(std::begin(A), std::end(A), std::begin(A_E)));
  }

  //== fund_if()

  {
    BEGIN_TEST(tm, "FindIf", "SeveralAreTrue");
    std::array A{ 1, 6, 3, 6, 5, 2, 6 };
    auto result
      = which_lib::find_if(std::begin(A), std::end(A), [](int e) -> bool { return e > 5; });
    EXPECT_EQ(std::begin(A) + 1, result);
  }

  {
    BEGIN_TEST(tm, "FindIf2", "NoneIsTrue");
    std::array A{ 1, 2, 3, 4, 5 };
    auto result
      = which_lib::find_if(std::begin(A), std::end(A), [](int e) -> bool { return e > 5; });
    EXPECT_EQ(std::end(A), result);
  }

  {
    BEGIN_TEST(tm, "FindIf3", "AllAreTrue");
    std::array A{ 6, 7, 8, 9, 10 };
    auto result
      = which_lib::find_if(std::begin(A), std::end(A), [](int e) -> bool { return e > 5; });
    EXPECT_EQ(std::begin(A), result);
  }

  {
    BEGIN_TEST(tm, "FindIf4", "PredicateTrueAtBeginning");
    std::array A{ 6, 2, 3, 4, 5, 2, 1 };
    auto result
      = which_lib::find_if(std::begin(A), std::end(A), [](int e) -> bool { return e > 5; });
    EXPECT_EQ(std::begin(A), result);
  }

  {
    BEGIN_TEST(tm, "FindIf5", "PredicateTrueAtMiddle");
    std::array A{ 1, 2, 3, 6, 5, 2, 1 };
    auto result
      = which_lib::find_if(std::begin(A), std::end(A), [](int e) -> bool { return e > 5; });
    EXPECT_EQ(std::begin(A) + 3, result);
  }

  {
    BEGIN_TEST(tm, "FindIf6", "PredicateTrueAtEnd");
    std::array A{ 1, 2, 3, 4, 5, 2, 6 };
    auto result
      = which_lib::find_if(std::begin(A), std::end(A), [](int e) -> bool { return e > 5; });
    EXPECT_EQ(std::prev(std::end(A)), result);
  }

  //== all_of

  {
    BEGIN_TEST(tm, "AllOf", "AllAreOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::all_of(std::begin(A), std::end(A), [](const int& e) { return e > 0; });

    EXPECT_TRUE(result);
  }

  {
    BEGIN_TEST(tm, "AllOf2", "AllAreNotOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::all_of(std::begin(A), std::end(A), [](const int& e) { return e < 0; });

    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "AllOf3", "FewAreOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::all_of(std::begin(A), std::end(A), [](const int& e) { return e > 30; });

    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "AllOf4", "EmptyInput");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::all_of(std::begin(A), std::begin(A), [](const int& e) { return e > 30; });

    EXPECT_TRUE(result);
  }

  //== any_of

  {
    BEGIN_TEST(tm, "AnyOf", "AllAreOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::any_of(std::begin(A), std::end(A), [](const int& e) { return e > 0; });

    EXPECT_TRUE(result);
  }

  {
    BEGIN_TEST(tm, "AnyOf1", "AllAreNotOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::any_of(std::begin(A), std::end(A), [](const int& e) { return e < 0; });

    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "AnyOf2", "FewAreOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::any_of(std::begin(A), std::end(A), [](const int& e) { return e > 30; });

    EXPECT_TRUE(result);
  }

  {
    BEGIN_TEST(tm, "AnyOf3", "EmptyInput");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::any_of(std::begin(A), std::begin(A), [](const int& e) { return e > 30; });

    EXPECT_FALSE(result);
  }

  //== none_of

  {
    BEGIN_TEST(tm, "NoneOf", "AllAreOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::none_of(std::begin(A), std::end(A), [](const int& e) { return e > 0; });

    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "NoneOf2", "AllAreNotOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::none_of(std::begin(A), std::end(A), [](const int& e) { return e < 0; });

    EXPECT_TRUE(result);
  }

  {
    BEGIN_TEST(tm, "NoneOf3", "FewAreOk");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::none_of(std::begin(A), std::end(A), [](const int& e) { return e > 30; });

    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "NoneOf4", "EmptyInput");
    std::array A{ 10, 20, 30, 40, 50, 60, 70 };
    bool result;

    result = which_lib::none_of(std::begin(A), std::begin(A), [](const int& e) { return e > 30; });

    EXPECT_TRUE(result);
  }

  //=== equal, version #1
  {
    BEGIN_TEST(tm, "Equal", "AllAreEqualSameSize ");
    std::array A{ 'a', 'b', 'c', 'd' };
    std::array A_E{ 'a', 'b', 'c', 'd' };

    bool result;
    result = which_lib::equal(
      std::begin(A), std::end(A), std::begin(A_E), [](int a, int b) -> bool { return a == b; });
    EXPECT_TRUE(result);
  }

  {
    BEGIN_TEST(tm, "Equal2", "AllAreNotEqualSameSize");
    std::array A{ 'a', 'b', 'c', 'd' };
    std::array A_E{ 'x', 'y', 'z', 'w' };

    bool result;
    result = which_lib::equal(
      std::begin(A), std::end(A), std::begin(A_E), [](int a, int b) -> bool { return a == b; });
    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "Equal3", "PartAreEqualSameSize");
    std::array A{ 'a', 'b', 'c', 'd' };
    std::array A_E{ 'x', 'y', 'c', 'd' };

    bool result;
    result = which_lib::equal(
      std::begin(A), std::end(A), std::begin(A_E), [](int a, int b) -> bool { return a == b; });
    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "Equal4", "AllAreEqual1stGreater2nd");
    std::array A{ 'a', 'b', 'c', 'd', 'e', 'f' };
    std::array A_E{ 'a', 'b', 'c', 'd' };

    bool result;
    result = which_lib::equal(
      std::begin(A), std::end(A), std::begin(A_E), std::end(A_E), [](int a, int b) -> bool {
        return a == b;
      });
    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "Equal5", "AllAreEqual1stGreater2ndCorrectRange");
    std::array A{ 'a', 'b', 'c', 'd', 'e', 'f' };
    std::array A_E{ 'a', 'b', 'c', 'd' };

    bool result;
    result = which_lib::equal(std::begin(A),
                              std::begin(A) + std::distance(std::begin(A_E), std::end(A_E)),
                              std::begin(A_E),
                              std::end(A_E),
                              [](int a, int b) -> bool { return a == b; });
    EXPECT_TRUE(result);
  }

  {
    BEGIN_TEST(tm, "Equal6", "PartIsNotEqual");
    std::array A{ 'a', 'b', 'c', 'd', 'e', 'f' };
    std::array A_E{ 'x', 'y', 'a', 'b', 'c', 'd', 'h', 'i' };

    bool result;
    result = which_lib::equal(
      std::begin(A), std::end(A), std::begin(A_E) + 2, std::end(A_E) + 6, [](int a, int b) -> bool {
        return a == b;
      });
    EXPECT_FALSE(result);
  }

  {
    BEGIN_TEST(tm, "Equal7", "PartIsEqual");
    std::array A{ 'a', 'b', 'c', 'd' };
    std::array A_E{ 'x', 'y', 'a', 'b', 'c', 'd', 'h', 'i' };

    bool result;
    result = which_lib::equal(std::begin(A),
                              std::end(A),
                              std::begin(A_E) + 2,
                              std::begin(A_E) + 6,
                              [](int a, int b) -> bool { return a == b; });
    EXPECT_TRUE(result);
  }

  //== unique()
  {
    BEGIN_TEST(tm, "Unique", "SomeRepetitions");
    std::array A{ 1, 2, 3, 4, 5, 5, 4, 4, 4, 3, 2, 3, 2, 1 };
    std::array A_E{ 1, 2, 3, 4, 5 };

    auto result = which_lib::unique(std::begin(A), std::end(A), std::equal_to<>());
    // []( const int& a, const int& b )->bool{ return a == b; } );

    EXPECT_TRUE(std::equal(std::begin(A), result, std::begin(A_E)));
  }

  {
    BEGIN_TEST(tm, "Unique2", "AllEquals");
    std::array A{ 1, 1, 1, 1, 1, 1, 1 };
    std::array A_E{ 1 };

    auto result = which_lib::unique(
      std::begin(A), std::end(A), [](const int& a, const int& b) -> bool { return a == b; });

    EXPECT_TRUE(std::equal(std::begin(A), result, std::begin(A_E)));
  }

  {
    BEGIN_TEST(tm, "Unique3", "AllAreUnique");
    std::array A{ 1, 2, 3, 4, 5, 6, 7 };
    std::array A_E{ 1, 2, 3, 4, 5, 6, 7 };

    auto result = which_lib::unique(
      std::begin(A), std::end(A), [](const int& a, const int& b) -> bool { return a == b; });

    EXPECT_TRUE(std::equal(std::begin(A), result, std::begin(A_E)));
  }

  {
    BEGIN_TEST(tm, "Unique4", "MirrorUnique");
    std::array A{ 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
    std::array A_E{ 1, 2, 3, 4, 5 };

    auto result = which_lib::unique(
      std::begin(A), std::end(A), [](const int& a, const int& b) -> bool { return a == b; });

    EXPECT_TRUE(std::equal(std::begin(A), result, std::begin(A_E)));
  }

  //== partition()
  {
    BEGIN_TEST(tm, "Partition", "AllAreTrue");
    std::array A{ 6, 7, 8, 9, 10 };
    std::array A_E{ 6, 7, 8, 9, 10 };

    auto predicate = [](const int& e) -> bool { return e > 5; };

    auto result = which_lib::partition(std::begin(A), std::end(A), predicate);

    // Location of the pointer must be correct.
    EXPECT_EQ(result, std::end(A));
    // Uset STL function to test whether the partion worked.
    EXPECT_TRUE(std::is_partitioned(std::begin(A), std::end(A), predicate));
    // Let us see if the elements have been preserved.
    std::sort(std::begin(A), std::end(A));
    std::vector<int> v_intersection;
    std::set_intersection(std::begin(A),
                          std::end(A),
                          std::begin(A_E),
                          std::end(A_E),
                          std::back_inserter(v_intersection));
    EXPECT_EQ((size_t)std::distance(std::begin(A), std::end(A)), v_intersection.size());
  }

  {
    BEGIN_TEST(tm, "Partition2", "NoneAreTrue");
    std::array A{ 0, 1, 2, 3, 4 };
    std::array A_E{ 0, 1, 2, 3, 4 };

    auto predicate = [](const int& e) -> bool { return e > 5; };

    auto result = which_lib::partition(std::begin(A), std::end(A), predicate);

    // Location of the pointer must be correct.
    EXPECT_EQ(std::distance(std::begin(A), result), 0);
    // Uset STL function to test whether the partion worked.
    EXPECT_TRUE(std::is_partitioned(std::begin(A), std::end(A), predicate));
    EXPECT_EQ(result, std::begin(A));
    // Let us see if the elements have been preserved.
    std::sort(std::begin(A), std::end(A));
    std::vector<int> v_intersection;
    std::set_intersection(std::begin(A),
                          std::end(A),
                          std::begin(A_E),
                          std::end(A_E),
                          std::back_inserter(v_intersection));
    EXPECT_EQ((size_t)std::distance(std::begin(A), std::end(A)), v_intersection.size());
  }

  {
    BEGIN_TEST(tm, "Partition3", "SomeAreTrueInverted");
    std::array A{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array A_E{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 };
    // Lambda
    auto predicate = [](const int& e) -> bool { return e > 5; };

    auto result = which_lib::partition(std::begin(A), std::end(A), predicate);
    EXPECT_EQ(std::distance(std::begin(A), result), 5);
    // Uset STL function to test whether the partion worked.
    EXPECT_TRUE(std::is_partitioned(std::begin(A), std::end(A), predicate));
    // Let us see if the elements have been preserved.
    std::sort(std::begin(A), std::end(A));
    std::sort(std::begin(A_E), std::end(A_E));
    std::vector<int> v_intersection;
    std::set_intersection(std::begin(A),
                          std::end(A),
                          std::begin(A_E),
                          std::end(A_E),
                          std::back_inserter(v_intersection));
    EXPECT_EQ((size_t)std::distance(std::begin(A), std::end(A)), v_intersection.size());
  }

  {
    BEGIN_TEST(tm, "Partition4", "SomeAreTrueInterleaved");
    std::array A{ 1, 10, 2, 9, 3, 8, 4, 7, 5, 6 };
    std::array A_E{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto predicate = [](const int& e) -> bool { return e > 5; };

    auto result = which_lib::partition(std::begin(A), std::end(A), predicate);
    EXPECT_EQ(std::distance(std::begin(A), result), 5);
    // Uset STL function to test whether the partion worked.
    EXPECT_TRUE(std::is_partitioned(std::begin(A), std::end(A), predicate));
    // Let us see if the elements have been preserved.
    std::sort(std::begin(A), std::end(A));
    std::vector<int> v_intersection;
    std::set_intersection(std::begin(A),
                          std::end(A),
                          std::begin(A_E),
                          std::end(A_E),
                          std::back_inserter(v_intersection));
    EXPECT_EQ((size_t)std::distance(std::begin(A), std::end(A)), v_intersection.size());
  }

  tm.summary();
  std::cout << std::endl;

  return EXIT_SUCCESS;
}

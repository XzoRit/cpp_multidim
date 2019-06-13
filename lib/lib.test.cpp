#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <iterator>
#include <multidim.hpp>
#include <vector>

BOOST_AUTO_TEST_CASE(multidim_flat_view)
{
  {
    const std::vector<int> a{ { 1, 22, 333 } };
    const auto& flatView{ multidim::makeFlatView(a) };
    BOOST_TEST(std::equal(begin(a), end(a), begin(flatView), end(flatView)));
  }
  {
    const std::vector<std::vector<int>> a{ { 1, 22, 333 },
                                           { 1, 22, 333 },
                                           { 1, 22, 333 } };
    const std::vector<int> b{ { 1, 22, 333, 1, 22, 333, 1, 22, 333 } };
    const auto& flatView{ multidim::makeFlatView(a) };
    BOOST_TEST(std::equal(begin(b), end(b), begin(flatView), end(flatView)));
  }
  {
    const std::vector<std::vector<std::vector<int>>> a{
      { { 1, 22, 333 }, { 1, 22, 333 } },
      { { 1, 22, 333 }, { 1, 22, 333 } },
      { { 1, 22, 333 }, { 1, 22, 333 } }
    };
    const std::vector<int> b{
      { 1, 22, 333, 1, 22, 333, 1, 22, 333, 1, 22, 333, 1, 22, 333, 1, 22, 333 }
    };
    const auto& flatView{ multidim::makeFlatView(a) };
    BOOST_TEST(std::equal(begin(b), end(b), begin(flatView), end(flatView)));
  }
}

#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <iterator>
#include <multidim.hpp>
#include <vector>

BOOST_AUTO_TEST_CASE(multidim_flat_view)
namespace
{
BOOST_AUTO_TEST_SUITE(multidim_lib)

const std::vector<int> oneDim{ { 1, 22, 333 } };
const std::vector<int> oneDimFlat{ { 1, 22, 333 } };
const std::vector<std::vector<int>> twoDim{ { 1, 22, 333 },
                                            { 1, 22, 333 },
                                            { 1, 22, 333 } };
const std::vector<int> twoDimFlat{ { 1, 22, 333, 1, 22, 333, 1, 22, 333 } };
const std::vector<std::vector<std::vector<int>>> threeDim{
  { { 1, 22, 333 }, { 1, 22, 333 } },
  { { 1, 22, 333 }, { 1, 22, 333 } },
  { { 1, 22, 333 }, { 1, 22, 333 } }
};
const std::vector<int> threeDimFlat{
  { 1, 22, 333, 1, 22, 333, 1, 22, 333, 1, 22, 333, 1, 22, 333, 1, 22, 333 }
};

BOOST_AUTO_TEST_CASE(dimensionality)
BOOST_AUTO_TEST_CASE(flat_view)
{
  {
    const auto& flatView{ multidim::makeFlatView(oneDim) };
    BOOST_TEST(std::equal(
      begin(oneDimFlat), end(oneDimFlat), begin(flatView), end(flatView)));
  }
  {
    const auto& flatView{ multidim::makeFlatView(twoDim) };
    BOOST_TEST(std::equal(
      begin(twoDimFlat), end(twoDimFlat), begin(flatView), end(flatView)));
  }
  {
    const auto& flatView{ multidim::makeFlatView(threeDim) };
    BOOST_TEST(std::equal(
      begin(threeDimFlat), end(threeDimFlat), begin(flatView), end(flatView)));
  }
}

BOOST_AUTO_TEST_SUITE_END()
}

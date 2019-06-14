#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <iterator>
#include <multidim.hpp>
#include <vector>

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
{
  BOOST_TEST(multidim::dimensionality(oneDim) == 1u);
  BOOST_TEST(multidim::dimensionality(twoDim) == 2u);
  BOOST_TEST(multidim::dimensionality(threeDim) == 3u);
}

BOOST_AUTO_TEST_CASE(bounds)
{
  {
    const auto& bounds{ multidim::bounds(oneDim) };
    const auto& expected{ std::vector<size_t>{ 3 } };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      begin(bounds), end(bounds), begin(expected), end(expected));
  }
  {
    const auto& bounds{ multidim::bounds(twoDim) };
    const auto& expected{ std::vector<size_t>{ 3, 3 } };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      begin(bounds), end(bounds), begin(expected), end(expected));
  }
  {
    const auto& bounds{ multidim::bounds(threeDim) };
    const auto& expected{ std::vector<size_t>{ 3, 2, 3 } };
    BOOST_CHECK_EQUAL_COLLECTIONS(
      begin(bounds), end(bounds), begin(expected), end(expected));
  }
}

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

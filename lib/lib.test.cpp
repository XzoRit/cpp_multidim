#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <iterator>
#include <multidim.hpp>
#include <type_traits>
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
std::vector<std::vector<std::vector<int>>> muteableThreeDim{
  { { 1, 22, 333 }, { 1, 22, 333 } },
  { { 1, 22, 333 }, { 1, 22, 333 } },
  { { 1, 22, 333 }, { 1, 22, 333 } }
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

BOOST_AUTO_TEST_CASE(scalar_size)
{
  BOOST_TEST(multidim::scalarSize(oneDim) == 3u);
  BOOST_TEST(multidim::scalarSize(twoDim) == 9u);
  BOOST_TEST(multidim::scalarSize(threeDim) == 18u);
}

BOOST_AUTO_TEST_CASE(scalar_type)
{
  static_assert(
    std::is_same<decltype(multidim::scalarType(oneDim)), int>::value, "");
  static_assert(
    std::is_same<decltype(multidim::scalarType(twoDim)), int>::value, "");
  static_assert(
    std::is_same<decltype(multidim::scalarType(threeDim)), int>::value, "");
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
  {
    auto flatView{ multidim::makeFlatView(muteableThreeDim) };
    flatView[11] = 17;
    BOOST_TEST(flatView[11] == muteableThreeDim[1][1][2]);
    muteableThreeDim[1][1][2] = 11;
    BOOST_TEST(flatView[11] == 11);
  }
}

BOOST_AUTO_TEST_CASE(boxed_view)
{
  const std::vector<std::vector<int>> notBoxed{ { 1 },
                                              { 1, 22 },
                                              { 1, 22, 333 } };
  const auto& boxedView{ multidim::makeBoxedView(notBoxed, 0, {}) };
  auto expectedBoxedView = std::vector<std::vector<int>>{{1,0,0},{1,22,0}, {1,22,333}};
  const auto& bounds{ multidim::bounds(notBoxed) };
  for (auto i{ 0u }; i < bounds[0]; ++i)
  {
    BOOST_TEST_INFO("index = " << i);
    BOOST_CHECK_EQUAL_COLLECTIONS(
      begin(boxedView[i]), end(boxedView[i]), begin(expectedBoxedView[i]), end(expectedBoxedView[i]));
  }
}

BOOST_AUTO_TEST_SUITE_END()
}

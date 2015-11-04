//
// Unit tests for block-chain checkpoints
//
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include "../checkpoints.h"
#include "../util.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p11111 = uint256("0xf725cd1001c73e756ad4ac6632a2c0b5de64393a9ef12d087811b9616a8d3e9e");
    uint256 p134444 = uint256("0x7408a53214c0eb798e2c7a777d32cabc2d42402db6bcd80f0833b3fe6df05f6a");
    BOOST_CHECK(Checkpoints::CheckHardened(11111, p11111));
    BOOST_CHECK(Checkpoints::CheckHardened(134444, p134444));


    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckHardened(11111, p134444));
    BOOST_CHECK(!Checkpoints::CheckHardened(134444, p11111));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckHardened(11111+1, p134444));
    BOOST_CHECK(Checkpoints::CheckHardened(134444+1, p11111));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 134444);
}

BOOST_AUTO_TEST_SUITE_END()

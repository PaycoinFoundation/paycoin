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
    uint256 p8055 = uint256("0x24046864d432565d46481b469611d0f97b9ac0fd3dff0a8f71fb7d8e3a983994");
    uint256 p50008 = uint256("0x18ceab3202f1f7e1208fc8241de41c47265dc5f5b0599130b06a26da9139e3d6");
    BOOST_CHECK(Checkpoints::CheckHardened(8055, p8055));
    BOOST_CHECK(Checkpoints::CheckHardened(50008, p50008));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckHardened(8055, p50008));
    BOOST_CHECK(!Checkpoints::CheckHardened(50008, p8055));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckHardened(8055+1, p50008));
    BOOST_CHECK(Checkpoints::CheckHardened(50008+1, p8055));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 50008);
}    

BOOST_AUTO_TEST_SUITE_END()

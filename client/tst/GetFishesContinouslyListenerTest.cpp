//
// Created by clejacquet on 18/03/17.
//

#include <fructose/fructose.h>
#include <network/listener/impl/GetFishesContinuouslyListener.h>

class MockGetFishesContinouslyListener : public GetFishesContinuouslyListener {
public:
    MockGetFishesContinouslyListener() {}

    std::string encodeRequest() const { return GetFishesContinuouslyListener::encodeRequest(); }
    std::list<FishInfo> decodeResponse(std::string response_msg) const { return GetFishesContinuouslyListener::decodeResponse(response_msg); }
};

struct GetFishesContinouslyListenerTest : public fructose::test_base<GetFishesContinouslyListenerTest> {
    void testEncodeRequest(const std::string &test_name) {
        MockGetFishesContinouslyListener listener;
        fructose_assert(listener.encodeRequest() == "getFishesContinuously");
    }

    void testDecodeResponse(const std::string &test_name) {
        MockGetFishesContinouslyListener listener;

        std::list<FishInfo> fish_info_list = listener.decodeResponse("list [PoissonRouge at 92x40,10x4,5] [PoissonClown at 22x80,12x6,5]");

        fructose_assert_eq(fish_info_list.size(), 2);
        FishInfo info1 = fish_info_list.front();
        FishInfo info2 = *(++fish_info_list.begin());

        fructose_assert_eq(info1.name, "PoissonRouge");
        fructose_assert_eq(info1.target_x, 92);
        fructose_assert_eq(info1.target_y, 40);
        fructose_assert_eq(info1.width, 10);
        fructose_assert_eq(info1.height, 4);
        fructose_assert_eq(info1.duration, 5);

        fructose_assert_eq(info2.name, "PoissonClown");
        fructose_assert_eq(info2.target_x, 22);
        fructose_assert_eq(info2.target_y, 80);
        fructose_assert_eq(info2.width, 12);
        fructose_assert_eq(info2.height, 6);
        fructose_assert_eq(info2.duration, 5);
    }
};

int main(int argc, char** argv) {
    GetFishesContinouslyListenerTest tests;
    tests.add_test("TestEncodingRequest", &GetFishesContinouslyListenerTest::testEncodeRequest);
    tests.add_test("TestDecodingResponse", &GetFishesContinouslyListenerTest::testDecodeResponse);
    return tests.run(argc, argv);
}
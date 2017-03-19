//
// Created by clejacquet on 15/03/17.
//

#include <fructose/fructose.h>
#include <network/request/impl/HelloRequest.h>

class MockHelloRequest : public HelloRequest {
public:
    MockHelloRequest() {}
    MockHelloRequest(int id) : HelloRequest(id) {}

    std::string encodeRequest() const { return HelloRequest::encodeRequest(); }
    int decodeResponse(std::string response_msg) const { return HelloRequest::decodeResponse(response_msg); }
};

struct HelloRequestTest : public fructose::test_base<HelloRequestTest> {
    void testEncodeRequest(const std::string &test_name) {
        MockHelloRequest hello_request(40);
        fructose_assert(hello_request.encodeRequest() == "hello in as N40");

        MockHelloRequest hello_request_empty;
        fructose_assert(hello_request_empty.encodeRequest() == "hello");
    }

    void testDecodeResponse(const std::string &test_name) {
        MockHelloRequest hello_request;

        fructose_assert_eq(hello_request.decodeResponse("greeting N43"), 43);
        fructose_assert_eq(hello_request.decodeResponse("greeting N0"), 0);
        fructose_assert_eq(hello_request.decodeResponse("no greeting"), -1);

        fructose_assert_eq(hello_request.decodeResponse("greetin N21"), -1);
        fructose_assert_eq(hello_request.decodeResponse("greeting N21 "), -1);
    }
};

int main(int argc, char** argv) {
    HelloRequestTest tests;
    tests.add_test("TestEncodingRequest", &HelloRequestTest::testEncodeRequest);
    tests.add_test("TestDecodingResponse", &HelloRequestTest::testDecodeResponse);
    return tests.run(argc, argv);
}

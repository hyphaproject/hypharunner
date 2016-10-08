// Copyright (c) 2016 Hypha

#include "hypharunner/controller/pointercontroller.h"
#include <hypha/core/cache/cache.h>
#include <gmock/gmock.h>
#include <iostream>

class pointercontroller_test : public testing::Test {
 public:
};

TEST_F(pointercontroller_test, CheckSomeResults) {
    PointerController *controller = PointerController::instance();
    std::string testdata = "testdata";
    std::string testkey = controller->put(testdata);
    ASSERT_TRUE(testdata == controller->get(testkey));
    std::cout << testkey << "  " << testdata << std::endl;
}

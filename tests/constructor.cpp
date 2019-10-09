#include <gtest/gtest.h>
#include "env/arguments.hpp"

TEST(Construct, Default) {
    env::arguments args1;
    EXPECT_FALSE(args1);

    env::arguments args2 { };
    ASSERT_FALSE(args2);
}

TEST(Construct, Empty) {
    int argc = 0;
    char* argv[] = { };

    env::arguments args1({ argv, argv + argc });
    EXPECT_FALSE(args1);

    env::arguments args2 { { argv, argv + argc } };
    ASSERT_FALSE(args2);
}

TEST(Construct, Prog) {
    int argc = 1;
    const char* argv[] = { "prog" };

    env::arguments args1({ argv, argv + argc });
    EXPECT_TRUE(args1);

    env::arguments args2 { { argv, argv + argc } };
    ASSERT_TRUE(args2);
}

TEST(CopyConstruct, Default) {
    env::arguments args1;
    env::arguments args2 = args1;
    ASSERT_FALSE(args2);
}

TEST(CopyConstruct, Empty) {
    int argc = 0;
    char* argv[] = { };
    env::arguments args1 { { argv, argv + argc } };
    env::arguments args2 = args1;
    ASSERT_FALSE(args2);
}

TEST(CopyConstruct, Prog) {
    int argc = 1;
    const char* argv[] = { "prog" };
    env::arguments args1 { { argv, argv + argc } };
    env::arguments args2 = args1;
    ASSERT_TRUE(args2);
}

TEST(Get, Empty) {
    env::arguments args { };
    auto sa = args.get("prog");
    ASSERT_FALSE(sa);
}

TEST(Get, Prog) {
    int argc = 1;
    const char* argv[] = { "prog" };
    env::arguments args { { argv, argv + argc } };
    auto sa = args.get("prog");
    ASSERT_TRUE(sa);
}


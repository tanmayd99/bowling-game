#include "pch.h"

#include "../src/Frame.h"
TEST(FrameTest, ConstructorInitializesCorrectly)
{
    Frame frame;
    EXPECT_EQ(frame.GetFrameScore(), 0);
    EXPECT_FALSE(frame.GetIsSpare());
    EXPECT_FALSE(frame.GetIsStrike());
    EXPECT_FALSE(frame.GetIsLastFrame());
    EXPECT_FALSE(frame.GetIsBonusThrowAwarded());
    EXPECT_FALSE(frame.NextThrowNeeded());
}
TEST(FrameTest, ResetResetsFrameState) 
{
    Frame frame;
    frame.ProcessThrow(10);
    frame.Reset();
    EXPECT_EQ(frame.GetFrameScore(), 0);
    EXPECT_FALSE(frame.GetIsSpare());
    EXPECT_FALSE(frame.GetIsStrike());
    EXPECT_FALSE(frame.GetIsLastFrame());
    EXPECT_FALSE(frame.GetIsBonusThrowAwarded());
    EXPECT_FALSE(frame.NextThrowNeeded());
}
TEST(FrameTest, ProcessThrowHandlesStrike)
{
    Frame frame;
    frame.ProcessThrow(10);
    EXPECT_TRUE(frame.GetIsStrike());
    EXPECT_EQ(frame.GetFrameScore(), 10);
    EXPECT_FALSE(frame.NextThrowNeeded());
}
TEST(FrameTest, ProcessThrowHandlesSpare)
{
    Frame frame;
    frame.ProcessThrow(5);
    frame.ProcessThrow(5);
    EXPECT_TRUE(frame.GetIsSpare());
    EXPECT_EQ(frame.GetFrameScore(), 10);
    EXPECT_FALSE(frame.NextThrowNeeded());
}
TEST(FrameTest, ProcessThrowThrowsExceptionForInvalidThrow)
{
    Frame frame;
    frame.ProcessThrow(5);
    EXPECT_THROW(frame.ProcessThrow(6), std::out_of_range);
}
TEST(FrameTest, AwardAdditionalBonusThrowWorks) {
    Frame frame;
    frame.AwardAdditionalBonusThrow();
    EXPECT_TRUE(frame.GetIsBonusThrowAwarded());
}
TEST(FrameTest, ClearAdditionalBonusThrowWorks) 
{
    Frame frame;
    frame.AwardAdditionalBonusThrow();
    frame.ClearAdditionalBonusThrow();
    EXPECT_FALSE(frame.GetIsBonusThrowAwarded());
}
TEST(FrameTest, SetAsLastFrameWorks)
{
    Frame frame;
    frame.SetAsLastFrame();
    EXPECT_TRUE(frame.GetIsLastFrame());
}
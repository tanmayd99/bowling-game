#include "pch.h"

#include "../src/BonusEvaluator.h"
#include "../src/Frame.h"
TEST(BonusEvaluatorTest, ConstructorInitializesCorrectly) 
{
    BonusEvaluator evaluator;
    EXPECT_EQ(evaluator.GetBonusValue(), 0);
}
TEST(BonusEvaluatorTest, AwardBonusIfApplicableAddsBonus) 
{
    BonusEvaluator evaluator;
    Frame frame;
    frame.ProcessThrow(10);

    evaluator.AllotBonusForFrame(&frame);
    evaluator.AwardBonusIfApplicable(10, &frame);

    EXPECT_EQ(evaluator.GetBonusValue(), 10);
}
TEST(BonusEvaluatorTest, AllotBonusForFrameHandlesStrike) 
{
    BonusEvaluator evaluator;
    Frame frame;

    frame.ProcessThrow(10);
    evaluator.AllotBonusForFrame(&frame);

    evaluator.AwardBonusIfApplicable(5, &frame);
    evaluator.AwardBonusIfApplicable(5, &frame);

    EXPECT_EQ(evaluator.GetBonusValue(), 10);
}
TEST(BonusEvaluatorTest, ClearBonusResetsBonusValue) 
{
    BonusEvaluator evaluator;
    Frame frame;

    evaluator.AllotBonusForFrame(&frame);
    evaluator.AwardBonusIfApplicable(10, &frame);
    evaluator.ClearBonus();

    EXPECT_EQ(evaluator.GetBonusValue(), 0);
}
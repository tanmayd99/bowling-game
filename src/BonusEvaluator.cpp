#include "BonusEvaluator.h"
#include "Frame.h"

BonusEvaluator::BonusEvaluator()
	: BonusTracker(0)
	, BonusValue(0)
{
}

BonusEvaluator::~BonusEvaluator()
{
}

void BonusEvaluator::AwardBonusIfApplicable(unsigned int valueFromCurrentThrow, Frame* frameToBeAwarded)
{
	if (BonusTracker > 0)
	{
		BonusValue += valueFromCurrentThrow;
		BonusTracker--;
	}
	if (frameToBeAwarded->GetIsLastFrame())
	{
		if (frameToBeAwarded->GetIsBonusThrowAwarded())
		{
			frameToBeAwarded->ClearAdditionalBonusThrow();
		}
		else if (frameToBeAwarded->GetIsStrike() || frameToBeAwarded->GetIsSpare())
		{
			frameToBeAwarded->AwardAdditionalBonusThrow();
		}
	}
}

void BonusEvaluator::AllotBonusForFrame(Frame* frameToBeEvaluated)
{
	if (!frameToBeEvaluated->GetIsLastFrame())
	{
		if (frameToBeEvaluated->GetIsStrike())
		{
			BonusTracker += 2;
		}
		else if (frameToBeEvaluated->GetIsSpare())
		{
			BonusTracker++;
		}
	}
}

unsigned int BonusEvaluator::GetBonusValue() const
{
	return BonusValue;
}

void BonusEvaluator::ClearBonus()
{
	BonusValue = 0;
}

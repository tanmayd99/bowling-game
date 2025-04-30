#pragma once

class Frame;

class BonusEvaluator
{
public:
	BonusEvaluator();
	~BonusEvaluator();

	void AwardBonusIfApplicable(unsigned int valueFromCurrentThrow, Frame* frameToBeAwarded);
	void AllotBonusForFrame(Frame* frameToBeEvaluated);
	unsigned int GetBonusValue() const;
	void ClearBonus();

private:
	unsigned int BonusTracker;
	unsigned int BonusValue;
};


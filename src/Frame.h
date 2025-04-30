#pragma once

class Frame
{
public:
	Frame();
	~Frame();

	void Reset();
	void StartFrame();
	void SetAsLastFrame();
	void ProcessThrow(unsigned int value);
	void AwardAdditionalBonusThrow();
	void ClearAdditionalBonusThrow();
	unsigned int GetFrameScore() const;
	bool NextThrowNeeded() const;
	bool GetIsSpare() const;
	bool GetIsStrike() const;
	bool GetIsLastFrame() const;
	bool GetIsBonusThrowAwarded() const;

private:
	void CheckIfFrameIsCompleted();

	unsigned int FrameScore;
	unsigned int ThrowCount;
	bool AcceptNextThrow;
	bool IsSpare;
	bool IsStrike;
	bool IsLastFrame;
	bool IsBonusThrowAwarded;
};


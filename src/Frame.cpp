#include "Frame.h"
#include <stdexcept>

namespace
{
	constexpr unsigned int MAX_THROW_VALUE = 10;
	constexpr unsigned int MAX_THROWS_PER_FRAME = 2;
}

Frame::Frame()
	: FrameScore(0)
	, ThrowCount(0)
	, AcceptNextThrow(false)
	, IsSpare(false)
	, IsStrike(false)
	, IsLastFrame(false)
	, IsBonusThrowAwarded(false)
{
}

Frame::~Frame()
{
}

void Frame::Reset()
{
	FrameScore = 0;
	ThrowCount = 0;
	AcceptNextThrow = false;
	IsSpare = false;
	IsStrike = false;
	IsLastFrame = false;
	IsBonusThrowAwarded = false;
}

void Frame::StartFrame()
{
	AcceptNextThrow = true;
}

void Frame::SetAsLastFrame()
{
	IsLastFrame = true;
}

void Frame::ProcessThrow(unsigned int value)
{
	++ThrowCount;

	if (ThrowCount == 1)
	{
		if (value == MAX_THROW_VALUE)
		{
			IsStrike = true;
			AcceptNextThrow = false;
		}
	}
	else if (ThrowCount == 2)
	{
		if ((FrameScore + value) == MAX_THROW_VALUE)
		{
			IsSpare = true;
		}
		if (((FrameScore + value) > MAX_THROW_VALUE) && !IsBonusThrowAwarded)
		{
			--ThrowCount;
			throw std::out_of_range("Bad Throw: Throw exeeds maximum PINs available to knock down. Please throw again.");
		}
	}

	CheckIfFrameIsCompleted();

	FrameScore += value;
}

void Frame::AwardAdditionalBonusThrow()
{
	IsBonusThrowAwarded = true;
}

void Frame::CheckIfFrameIsCompleted()
{
	if (ThrowCount == MAX_THROWS_PER_FRAME)
	{
		AcceptNextThrow = false;
	}
}

void Frame::ClearAdditionalBonusThrow()
{
	IsBonusThrowAwarded = false;
}

unsigned int Frame::GetFrameScore() const
{
	return FrameScore;
}

bool Frame::NextThrowNeeded() const
{
	return AcceptNextThrow || IsBonusThrowAwarded;
}

bool Frame::GetIsSpare() const
{
	return IsSpare;
}

bool Frame::GetIsStrike() const
{
	return IsStrike;
}

bool Frame::GetIsLastFrame() const
{
	return IsLastFrame;
}

bool Frame::GetIsBonusThrowAwarded() const
{
	return IsBonusThrowAwarded;
}

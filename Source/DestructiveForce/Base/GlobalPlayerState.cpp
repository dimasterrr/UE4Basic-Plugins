#include "GlobalPlayerState.h"

int AGlobalPlayerState::GetScores() const
{
	return CurrentScores;
}

void AGlobalPlayerState::AddScores(const int Scores)
{
	CurrentScores += Scores;
}
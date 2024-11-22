package main

import (
	"JamJam/grapevine/proto/gen/pb-go/JamJam/grapevine"
	"context"
	"fmt"

	"google.golang.org/protobuf/types/known/emptypb"
)

func (s *ScoreBoardManager) PostNewScore(_ context.Context, userScore *grapevine.UserScore) *emptypb.Empty {
	fmt.Printf("Posting score!")

	return &emptypb.Empty{}
}

func (s *ScoreBoardManager) GetTopThreeUserScores(_ context.Context, _ *emptypb.Empty) (*grapevine.TopScores, error) {

	fmt.Printf("Getting scores!")

	return &grapevine.TopScores{}, context.Background().Err()
}

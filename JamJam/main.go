package main

import (
	"JamJam/grapevine/proto/gen/pb-go/JamJam/grapevine"
	"flag"
	"fmt"
	"log"
	"net"

	"google.golang.org/grpc"
)

type ScoreBoardManager struct {
	server    grapevine.ScoreBoardManagerServer
	tableName string
}

func main() {
	fmt.Printf("Trying to run server")

	lis, err := net.Listen("tcp", "127.0.0.1:8059")
	if err != nil {
		log.Fatal("Cannot create listener: %s", err)
	}
	table_name := flag.String("table-name", "invalid", "name of the dynamo db table")

	serviceRegistrar := grpc.NewServer()
	ScoreBoardManager := &ScoreBoardManager{
		server:    &grapevine.UnimplementedScoreBoardManagerServer{},
		tableName: *table_name,
	}
	grapevine.RegisterScoreBoardManagerServer(serviceRegistrar, ScoreBoardManager.server)
	err = serviceRegistrar.Serve(lis)
	if err != nil {
		log.Fatal("impossible to serve: %s", err)
	}
}

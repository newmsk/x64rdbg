#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/base.grpc.pb.h"
#include "proto/bridgemain.grpc.pb.h"

using grpc::Status;

class BridgeMain final : public ::bridgemain::BridgeMain::Service
{
	Status DbgCmdExec(::grpc::ServerContext* context, const ::base::String* request, ::base::Boolean* response) override;
	Status DbgCmdExecDirect(::grpc::ServerContext* context, const ::base::String* request, ::base::Boolean* response) override;
	Status DbgEval(::grpc::ServerContext* context, const ::base::String* request, ::bridgemain::DbgExprValue* response) override;
	Status GuiCloseApplication(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status DbgGetBpList(::grpc::ServerContext* context, const ::base::Empty* request, ::bridgemain::BPList* response) override;
	Status DbgGetRegDumpEx(::grpc::ServerContext* context, const ::base::Empty* request, ::bridgemain::RegDump* response) override;
};
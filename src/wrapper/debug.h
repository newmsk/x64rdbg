#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/base.grpc.pb.h"
#include "proto/debug.grpc.pb.h"

using grpc::Status;

class Debug final : public ::debug::Debug::Service
{
	Status Hello(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status Wait(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status Run(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status Pause(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status Stop(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status StepIn(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status StepOver(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status StepOut(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override;
	Status SetBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override;
	Status DeleteBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override;
	Status DisableBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override;
	Status SetHardwareBreakpoint(::grpc::ServerContext* context, const ::debug::HardwareBreakpoint* request, ::base::Boolean* response) override;
	Status DeleteHardwareBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override;
};
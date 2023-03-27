#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/base.grpc.pb.h"
#include "proto/register.grpc.pb.h"

using grpc::Status;

class Register final : public ::reg::Register::Service
{
	Status Get(::grpc::ServerContext* context, const ::reg::RegisterId* request, ::reg::RegisterValue* response) override;
	Status Set(::grpc::ServerContext* context, const ::reg::RegisterIdValuePair* request, ::base::Boolean* response) override;
	Status Size(::grpc::ServerContext* context, const ::base::Empty* request, ::base::UnsignedNumberValue* response) override;
};
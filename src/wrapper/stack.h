#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/base.grpc.pb.h"
#include "proto/stack.grpc.pb.h"

using grpc::Status;

class Stack final : public ::stack::Stack::Service
{
	Status Pop(::grpc::ServerContext* context, const ::base::Empty* request, ::base::UnsignedNumberValue* response);
	Status Push(::grpc::ServerContext* context, const ::base::UnsignedNumberValue* request, ::base::UnsignedNumberValue* response);
	Status Peek(::grpc::ServerContext* context, const ::base::UnsignedNumberValue* request, ::base::UnsignedNumberValue* response);
};
#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/base.grpc.pb.h"
#include "proto/memory.grpc.pb.h"

using grpc::Status;

class Memory final : public ::memory::Memory::Service
{
	Status Read(::grpc::ServerContext* context, const ::memory::AddressAndSizePair* request, ::base::BinaryData* response) override;
	Status Write(::grpc::ServerContext* context, const ::memory::MemoryWriteParam* request, ::base::UnsignedNumberValue* response) override;
	Status IsValidPtr(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override;
	Status RemoteAlloc(::grpc::ServerContext* context, const ::memory::AddressAndSizePair* request, ::base::Address* response) override;
	Status RemoteFree(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override;
	Status GetProtect(::grpc::ServerContext* context, const ::base::Address* request, ::base::UnsignedNumberValue* response) override;
	Status GetBase(::grpc::ServerContext* context, const ::base::Address* request, ::base::Address* response) override;
	Status GetSize(::grpc::ServerContext* context, const ::base::Address* request, ::base::UnsignedNumberValue* response) override;
};
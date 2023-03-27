#pragma once

#include <grpcpp/grpcpp.h>

#include "proto/base.grpc.pb.h"
#include "proto/module.grpc.pb.h"

using grpc::Status;


class Module final : public ::module::Module::Service
{
	Status GetMainModuleBase(::grpc::ServerContext * context, const ::base::Empty * request, ::base::Address * response) override;
	Status GetMainModuleSize(::grpc::ServerContext* context, const ::base::Empty* request, ::base::UnsignedNumberValue* response) override;
	Status GetMainModuleEntry(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Address* response) override;
	Status GetList(::grpc::ServerContext * context, const ::base::Empty * request, ::module::ModulesList * response) override;
};
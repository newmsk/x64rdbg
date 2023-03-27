#include <grpcpp/grpcpp.h>

#include "proto/base.grpc.pb.h"
#include "proto/debug.grpc.pb.h"

#include "pluginmain.h"

#include "debug.h"

//using grpc::Server;
//using grpc::ServerBuilder;
//using grpc::ServerContext;
//using grpc::Status;



//class Debug final : public ::debug::Debug::Service
//{
//	Status Hello(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override {
//		(void)context; (void)request; (void)response;
//		dprintf("%s", "Got Hello command !!!");
//		return Status::OK;
//	}
//
//	Status Wait(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override {
//		(void)context; (void)request; (void)response;
//		Script::Debug::Wait();
//		return Status::OK;
//	}
//
//	Status Run(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override {
//		(void)context; (void)request; (void)response;
//		Script::Debug::Run();
//		return Status::OK;
//	}
//
//	Status Pause(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override {
//		(void)context; (void)request; (void)response;
//		Script::Debug::Pause();
//		return Status::OK;
//	}
//
//	Status Stop(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override {
//		(void)context; (void)request; (void)response;
//		Script::Debug::Stop();
//		return Status::OK;
//	}
//
//	Status StepIn(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override {
//		(void)context; (void)request; (void)response;
//		Script::Debug::StepIn();
//		return Status::OK;
//	}
//
//	Status StepOver(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override {
//		(void)context; (void)request; (void)response;
//		Script::Debug::StepOver();
//		return Status::OK;
//	}
//
//	Status StepOut(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) override {
//		(void)context; (void)request; (void)response;
//		Script::Debug::StepOut();
//		return Status::OK;
//	}
//
//	Status SetBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override {
//		(void)context;
//		response->set_boolean(Script::Debug::SetBreakpoint(static_cast<duint>(request->address())));
//		return Status::OK;
//	}
//
//	Status DeleteBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override {
//		(void)context;
//		response->set_boolean(Script::Debug::DeleteBreakpoint(static_cast<duint>(request->address())));
//		return Status::OK;
//	}
//
//	Status DisableBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override {
//		(void)context;
//		response->set_boolean(Script::Debug::DisableBreakpoint(static_cast<duint>(request->address())));
//		return Status::OK;
//	}
//
//	Status SetHardwareBreakpoint(::grpc::ServerContext* context, const ::debug::HardwareBreakpoint* request, ::base::Boolean* response) override {
//		(void)context;
//		::base::Address address_obj = request->address();
//		duint address = static_cast<duint>(address_obj.address());
//		Script::Debug::HardwareType type = static_cast<Script::Debug::HardwareType>(request->type());
//		response->set_boolean(Script::Debug::SetHardwareBreakpoint(address, type));
//		return Status::OK;
//	}
//
//	Status DeleteHardwareBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) override {
//		(void)context;
//		response->set_boolean(Script::Debug::DeleteHardwareBreakpoint(static_cast<duint>(request->address())));
//		return Status::OK;
//	}
//};


Status Debug::Hello(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) 
{
	(void)context; (void)request; (void)response;
	dprintf("%s", "Got Hello command !!!");
	return Status::OK;
}

Status Debug::Wait(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) 
{
	(void)context; (void)request; (void)response;
	Script::Debug::Wait();
	return Status::OK;
}

Status Debug::Run(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) 
{
	(void)context; (void)request; (void)response;
	Script::Debug::Run();
	return Status::OK;
}

Status Debug::Pause(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) 
{
	(void)context; (void)request; (void)response;
	Script::Debug::Pause();
	return Status::OK;
}

Status Debug::Stop(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) 
{
	(void)context; (void)request; (void)response;
	Script::Debug::Stop();
	return Status::OK;
}

Status Debug::StepIn(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) 
{
	(void)context; (void)request; (void)response;
	Script::Debug::StepIn();
	return Status::OK;
}

Status Debug::StepOver(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) 
{
	(void)context; (void)request; (void)response;
	Script::Debug::StepOver();
	return Status::OK;
}

Status Debug::StepOut(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response) 
{
	(void)context; (void)request; (void)response;
	Script::Debug::StepOut();
	return Status::OK;
}

Status Debug::SetBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) 
{
	(void)context;
	response->set_boolean(Script::Debug::SetBreakpoint(static_cast<duint>(request->address())));
	return Status::OK;
}

Status Debug::DeleteBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) 
{
	(void)context;
	response->set_boolean(Script::Debug::DeleteBreakpoint(static_cast<duint>(request->address())));
	return Status::OK;
}

Status Debug::DisableBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) 
{
	(void)context;
	response->set_boolean(Script::Debug::DisableBreakpoint(static_cast<duint>(request->address())));
	return Status::OK;
}

Status Debug::SetHardwareBreakpoint(::grpc::ServerContext* context, const ::debug::HardwareBreakpoint* request, ::base::Boolean* response) 
{
	(void)context;
	::base::Address address_obj = request->address();
	duint address = static_cast<duint>(address_obj.address());
	Script::Debug::HardwareType type = static_cast<Script::Debug::HardwareType>(request->type());
	response->set_boolean(Script::Debug::SetHardwareBreakpoint(address, type));
	return Status::OK;
}

Status Debug::DeleteHardwareBreakpoint(::grpc::ServerContext* context, const ::base::Address* request, ::base::Boolean* response) 
{
	(void)context;
	response->set_boolean(Script::Debug::DeleteHardwareBreakpoint(static_cast<duint>(request->address())));
	return Status::OK;
}
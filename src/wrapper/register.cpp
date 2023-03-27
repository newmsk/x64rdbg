#include "register.h"

#include "pluginmain.h"


Status Register::Get(::grpc::ServerContext* context, const ::reg::RegisterId* request, ::reg::RegisterValue* response)
{
	(void)context;
	response->set_value(static_cast<uint64_t>(Script::Register::Get(static_cast<Script::Register::RegisterEnum>(request->id()))));
	return Status::OK;
}

Status Register::Set(::grpc::ServerContext* context, const ::reg::RegisterIdValuePair* request, ::base::Boolean* response)
{
	(void)context;
	const ::reg::RegisterId id = request->id();
	const ::reg::RegisterValue value = request->value();
	response->set_boolean(Script::Register::Set(static_cast<Script::Register::RegisterEnum>(id.id()), static_cast<duint>(value.value())));
	return Status::OK;
}

Status Register::Size(::grpc::ServerContext* context, const ::base::Empty* request, ::base::UnsignedNumberValue* response)
{
	(void)context; (void)request;
	response->set_value(static_cast<int64_t>(Script::Register::Size()));
	return Status::OK;
}

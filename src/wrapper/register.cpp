#include <map>

#include "register.h"
#include "pluginmain.h"


Script::Register::RegisterEnum get_real_reg_id(::reg::RegisterEnum wrap_id)
{
	std::map<::reg::RegisterEnum, Script::Register::RegisterEnum> cxx_reg_id_map = {
		{::reg::CIP, Script::Register::CIP},
		{::reg::CSP, Script::Register::CSP},
		{::reg::CAX, Script::Register::CAX},
		{::reg::CBX, Script::Register::CBX},
		{::reg::CCX, Script::Register::CCX},
		{::reg::CDX, Script::Register::CDX},
		{::reg::CDI, Script::Register::CDI},
		{::reg::CSI, Script::Register::CSI},
		{::reg::CBP, Script::Register::CBP},
		{::reg::CFLAGS, Script::Register::CFLAGS},
	};

	if (wrap_id < 10000)
		return static_cast<Script::Register::RegisterEnum>(wrap_id);

	return cxx_reg_id_map[wrap_id];
}


Status Register::Get(::grpc::ServerContext* context, const ::reg::RegisterId* request, ::reg::RegisterValue* response)
{
	(void)context;
	auto real_reg_id = get_real_reg_id(request->id());
	response->set_value(static_cast<uint64_t>(Script::Register::Get(real_reg_id)));
	return Status::OK;
}

Status Register::Set(::grpc::ServerContext* context, const ::reg::RegisterIdValuePair* request, ::base::Boolean* response)
{
	(void)context;
	const ::reg::RegisterId id = request->id();
	const ::reg::RegisterValue value = request->value();
	auto real_reg_id = get_real_reg_id(id.id());
	response->set_boolean(Script::Register::Set(real_reg_id, static_cast<duint>(value.value())));
	return Status::OK;
}

Status Register::Size(::grpc::ServerContext* context, const ::base::Empty* request, ::base::UnsignedNumberValue* response)
{
	(void)context; (void)request;
	response->set_value(static_cast<int64_t>(Script::Register::Size()));
	return Status::OK;
}

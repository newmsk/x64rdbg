#include "stack.h"

#include "pluginmain.h"


Status Stack::Pop(::grpc::ServerContext* context, const ::base::Empty* request, ::base::UnsignedNumberValue* response)
{
	(void)context; (void)request;
	response->set_value(Script::Stack::Pop());
	return Status::OK;
}

Status Stack::Push(::grpc::ServerContext* context, const ::base::UnsignedNumberValue* request, ::base::UnsignedNumberValue* response)
{
	(void)context;
	duint value = static_cast<duint>(request->value());
	duint prev_top = Script::Stack::Push(value);
	response->set_value(prev_top);
	return Status::OK;
}

Status Stack::Peek(::grpc::ServerContext* context, const ::base::UnsignedNumberValue* request, ::base::UnsignedNumberValue* response)
{
	(void)context;
	int offset = static_cast<int>(request->value());
	duint value = Script::Stack::Peek(offset);
	response->set_value(value);
	return Status::OK;
}
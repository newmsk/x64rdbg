#include "memory.h"

#include "pluginmain.h"

Status Memory::Read(::grpc::ServerContext* context, const::memory::AddressAndSizePair* request, ::base::BinaryData* response)
{
	(void)context;
	::base::Address address_obj = request->address();
	duint size = static_cast<duint>(request->size());
	duint sizeRead = 0;
	char* const data_buf = new char[size];
	
	if (Script::Memory::Read(static_cast<duint>(address_obj.address()), data_buf, size, &sizeRead)) {
		response->set_data(data_buf, sizeRead);
	}

	delete[] data_buf;
	return Status::OK;
}

Status Memory::Write(::grpc::ServerContext* context, const::memory::MemoryWriteParam* request, ::base::UnsignedNumberValue* response)
{
	(void)context;
	::base::Address address_obj = request->address();
	::base::BinaryData bin_data = request->data();
	std::string data = bin_data.data();
	duint sizeWrite = 0;

	if (Script::Memory::Write(static_cast<duint>(address_obj.address()), data.c_str(), data.size(), &sizeWrite))
		response->set_value(sizeWrite);
	return Status::OK;
}

Status Memory::IsValidPtr(::grpc::ServerContext* context, const::base::Address* request, ::base::Boolean* response)
{
	(void)context;
	response->set_boolean(Script::Memory::IsValidPtr(static_cast<duint>(request->address())));
	return Status::OK;
}

Status Memory::RemoteAlloc(::grpc::ServerContext* context, const::memory::AddressAndSizePair* request, ::base::Address* response)
{
	(void)context;
	::base::Address address_obj = request->address();
	duint size = static_cast<duint>(request->size());
	response->set_address(Script::Memory::RemoteAlloc(static_cast<duint>(address_obj.address()), size));
	return Status::OK;
}

Status Memory::RemoteFree(::grpc::ServerContext* context, const::base::Address* request, ::base::Boolean* response)
{
	(void)context;
	response->set_boolean(Script::Memory::RemoteFree(static_cast<duint>(request->address())));
	return Status::OK;
}

Status Memory::GetProtect(::grpc::ServerContext* context, const::base::Address* request, ::base::UnsignedNumberValue* response)
{
	(void)context;
	response->set_value(Script::Memory::GetProtect(static_cast<duint>(request->address())));
	return Status::OK;
}

Status Memory::GetBase(::grpc::ServerContext* context, const::base::Address* request, ::base::Address* response)
{
	(void)context;
	response->set_address(Script::Memory::GetBase(static_cast<duint>(request->address())));
	return Status::OK;
}

Status Memory::GetSize(::grpc::ServerContext* context, const::base::Address* request, ::base::UnsignedNumberValue* response)
{
	(void)context;
	response->set_value(Script::Memory::GetSize(static_cast<duint>(request->address())));
	return Status::OK;
}

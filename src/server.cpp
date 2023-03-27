#include <string>

#include <grpcpp/grpcpp.h>



#include "proto/base.grpc.pb.h"
#include "proto/debug.grpc.pb.h"

#include "pluginmain.h"

#include "wrapper/debug.h"
#include "wrapper/register.h"
#include "wrapper/memory.h"
#include "wrapper/bridgemain.h"
#include "wrapper/module.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;


bool GetEnvVar(const std::string& name, std::string& value)
{
	DWORD size_needed = GetEnvironmentVariableA(name.c_str(), NULL, 0);
	if (!size_needed && GetLastError() == ERROR_ENVVAR_NOT_FOUND)
		return false;
	std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size_needed);
	GetEnvironmentVariableA(name.c_str(), buffer.get(), size_needed);
	value = buffer.get();
	return true;
}


void Run()
{
	
	std::string rdbg_port;
	if (!GetEnvVar("rdbg_port", rdbg_port))
	{
		rdbg_port = "8064";
		dprintf("Use default port 8064\n");
	}

	std::string address = "0.0.0.0:";
	address += rdbg_port;
	Debug debug_service;
	Register register_service;
	Memory memory_service;
	BridgeMain bridgemain_service;
	Module module_service;
	
	ServerBuilder builder;
	builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	builder.RegisterService(&debug_service);
	builder.RegisterService(&register_service);
	builder.RegisterService(&memory_service);
	builder.RegisterService(&bridgemain_service);
	builder.RegisterService(&module_service);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	dprintf("Server listening on port: %s\n", rdbg_port.c_str());
	server->Wait();
}
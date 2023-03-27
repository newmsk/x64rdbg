#include "module.h"

#include "pluginmain.h"


Status Module::GetMainModuleBase(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Address* response)
{
	(void)context; (void)request;
	duint base = Script::Module::GetMainModuleBase();
	response->set_address(base);
	return Status::OK;
}

Status Module::GetMainModuleSize(::grpc::ServerContext* context, const ::base::Empty* request, ::base::UnsignedNumberValue* response)
{
	(void)context; (void)request;
	duint size = Script::Module::GetMainModuleSize();
	response->set_value(size);
	return Status::OK;
}

Status Module::GetMainModuleEntry(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Address* response)
{
	(void)context; (void)request;
	duint entry = Script::Module::GetMainModuleEntry();
	response->set_address(entry);
	return Status::OK;
}

Status Module::GetList(::grpc::ServerContext* context, const ::base::Empty* request, ::module::ModulesList* response)
{

	BridgeList<Script::Module::ModuleInfo> modules;
	if (!Script::Module::GetList(&modules)) {
		_plugin_logprintf("Module::GetList failed");
		return Status::OK;
	}

	for (int i = 0; i < modules.Count(); i++)
	{
		auto& mod = modules[i];

		::module::ModuleInfo *new_module = response->add_modules();
		new_module->mutable_base()->set_address(mod.base);
		new_module->mutable_size()->set_value(mod.size);
		new_module->mutable_entry()->set_address(mod.entry);
		new_module->mutable_section_count()->set_value(mod.sectionCount);
		new_module->mutable_name()->set_value(mod.name);
		new_module->mutable_path()->set_value(mod.path);
	}

	return Status::OK;

}
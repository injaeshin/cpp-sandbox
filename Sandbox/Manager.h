#pragma once

#include <iostream>

#include "Register.h"

namespace sb {
	namespace mgr {

		class ObjectManager : public util::IRegister
		{
		public:
			ObjectManager(const Manager &name)
			{
				_name = std::move(name);
			}

			virtual ~ObjectManager() = default;

			// Inherited via IManager
			virtual Manager &GetName() override
			{
				return _name;
			}

		private:
			Manager _name;
		};
	}	// namespace mgr
}	// namespace ca


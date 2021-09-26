#pragma once

#include <memory>
#include <unordered_map>
#include <mutex>

namespace sb {

	enum class Manager
	{
		LOG = 10,
	};

	namespace util {

		__interface IRegister
		{		
			Manager &GetName();
		};

		class Register
		{
		public:
			Register(const Register &) = delete;
			Register &operator=(const Register &) = delete;

			void Set(std::shared_ptr<IRegister> new_manager)
			{
				std::lock_guard<std::mutex> lock(_register_map_mutex);

				Add(std::move(new_manager));
			};

			template<class T>
			std::shared_ptr<T> Get(const Manager &mgr)
			{
				std::lock_guard<std::mutex> lock(_register_map_mutex);

				auto found = _managers.find(mgr);
				return found == _managers.end() ? nullptr : std::dynamic_pointer_cast<T>(found->second);
			};

			void Drop(const Manager &mgr)
			{
				std::lock_guard<std::mutex> lock(_register_map_mutex);

				_managers.erase(mgr);
			}

			void DropAll()
			{
				std::lock_guard<std::mutex> lock(_register_map_mutex);

				_managers.clear();
			}

			static Register &Instance()
			{
				static Register s_instance;
				return s_instance;
			}

		private:
			Register() = default;
			~Register() = default;

			void Add(std::shared_ptr<IRegister> new_manager)
			{
				// TODO - throw_if_exists

				auto mgr = new_manager->GetName();
				_managers[mgr] = std::move(new_manager);
			}

			std::unordered_map<Manager, std::shared_ptr<IRegister>> _managers;
			std::mutex _register_map_mutex;
		};

	}	// namespace util
}	// namespace ca
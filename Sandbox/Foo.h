#pragma once

#include <iostream>
#include <list>

namespace sb
{
	namespace log
	{
		enum class Reason : uint8_t
		{
			None   = 0,
			Battle = 1,
			Quest  = 2,
			Use    = 3,
		};

		struct ReasonValue
		{
			uint64_t id;
			uint64_t idx;
		};

		enum class Action : uint8_t
		{
			Create = 1,
			Delete = 2
		};

		class LogReason
		{
		private:
			Reason m_reason;
			std::list<ReasonValue> m_values;

		public:
			LogReason() : m_reason(Reason::None) { }

		public:
			inline void Set(const Reason &rsn, uint64_t &id, uint64_t &idx)
			{
				m_reason = std::move(rsn);

				ReasonValue rv = { id, idx };
				m_values.emplace_back(rv);
			}

			inline uint8_t GetReason() const { return static_cast<uint8_t>(m_reason); }
			inline const std::list<ReasonValue> &GetValues() const { return m_values; }
			inline bool IsEmpty() const { return m_values.empty(); }
		};

		class LogFoo
		{
		private:
			Action      m_action;
			uint32_t    m_account_idx;
			std::wstring m_account_id;
			LogReason   m_reason;

		public:
			LogFoo(const Action &act)
			{
				m_action = std::move(act);
			}

		public:
			inline void Set(uint32_t idx, const std::wstring &id)
			{
				m_account_idx = idx;
				m_account_id = std::move(id);
			}

			inline uint32_t GetAction() const { return static_cast<uint32_t>(m_action); }
			inline uint32_t GetAccountIdx() const { return m_account_idx; }
			inline const std::wstring &GetAccountId() const { return m_account_id; }

			inline bool IsReasonEmpty() const { return m_reason.IsEmpty(); }
			inline uint32_t GetReason() const { return m_reason.GetReason(); }
			inline const std::list<ReasonValue> &GetReasonValues() const { return m_reason.GetValues(); }
			inline void SetReason(const Reason &rsn, uint64_t id, uint64_t idx = 0) { m_reason.Set(rsn, id, idx); }			
		};
	}
}
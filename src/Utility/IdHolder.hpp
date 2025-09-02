#pragma once

#include "Utility/Registry.hpp"

template <typename TBase, typename TItem>
class IdHolder
{
public:
	using registry_t = Registry<TBase>;
	using id_t = typename TBase::id_t;

private:
	id_t m_id = id_t{};

public:
	id_t getId() const noexcept { return m_id; }

	static IdHolder& getInstance()
	{
		static IdHolder instance;
		return instance;
	}

private:
	IdHolder() : m_id(registry_t::template registerItem<TItem>()) {}
};
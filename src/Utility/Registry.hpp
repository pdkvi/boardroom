#pragma once

#include <unordered_map>
#include <concepts>
#include <memory>

template <typename TBase>
concept Registered = requires(TBase * ptr)
{
	typename TBase::id_t;
	{ ptr->clone().operator->() } -> std::convertible_to<TBase*>;
	{ ptr->getId() } -> std::convertible_to<typename TBase::id_t>;
};

template <typename TBase> requires Registered<TBase>
class Registry
{
public:
	using id_t = typename TBase::id_t;

private:
	using registry_t = std::unordered_map<id_t, std::shared_ptr<TBase>>;
	static inline registry_t s_tools;

public:
	template <typename TDerived> requires std::derived_from<TDerived, TBase>
	static id_t registerItem()
	{
		id_t const newId = s_tools.size() + 1;
		s_tools[newId] = std::make_shared<TDerived>();
		return newId;
	}

	static std::shared_ptr<TBase const> getItem(id_t id)
	{
		if (s_tools.contains(id) == false)
			return nullptr;

		return s_tools[id];
	}

	template <typename TDerived> requires std::derived_from<TDerived, TBase>
	static id_t getItemId() { return TDerived{}.getId(); }
};
#pragma once

/// @brief A class that allows the creation of an object only within the current inheritance hierarchy.
/// @note Also, using friendship, it is possible to allow selected third-party classes to construct objects.
class SelectedConstruction
{
public:
	virtual ~SelectedConstruction() = default;

protected:
	struct SecretTag {};
	virtual void secret(SecretTag) = 0;

	template <typename TDerived> requires std::derived_from<TDerived, SelectedConstruction>
	class SelectedConstructionImpl : public TDerived
	{
		void secret(typename TDerived::SecretTag) override {}
	};
};
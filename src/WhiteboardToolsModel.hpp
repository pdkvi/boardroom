#pragma once

#include <QAbstractListModel>

#include "Tools/Core/ToolBase.hpp"

class WhiteboardToolsModel : public QAbstractListModel
{
public:
	enum ItemRole
	{
		Data = Qt::UserRole
	};

private:
	std::vector<std::shared_ptr<ToolBase const>> m_toolsId;

public:
	template <typename TTool>
	void addTool()
	{
		ToolBase::id_t const toolId = ToolRegistry::getItemId<TTool>();
		m_toolsId.push_back(ToolRegistry::getItem(toolId));
	}

	int rowCount(QModelIndex const& parent) const override;

	QVariant data(QModelIndex const& index, int role) const override;
};
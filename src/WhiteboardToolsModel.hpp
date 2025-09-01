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
	std::vector<std::shared_ptr<ITool const>> m_toolsId;

public:
	void addTool(ITool::id_t id);

	int rowCount(QModelIndex const& parent) const override;

	QVariant data(QModelIndex const& index, int role) const override;
};
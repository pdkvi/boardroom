#include "WhiteboardToolsModel.hpp"

void WhiteboardToolsModel::addTool(ITool::id_t id)
{
	m_toolsId.push_back(ToolRegistry::getItem(id));
}

int WhiteboardToolsModel::rowCount(QModelIndex const& parent) const
{
	return m_toolsId.size();
}

QVariant WhiteboardToolsModel::data(QModelIndex const& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		return m_toolsId[index.row()]->getName();
	}
	if (role == ItemRole::Data)
	{
		return QVariant::fromValue(m_toolsId[index.row()]);
	}

	return { };
}

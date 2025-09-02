add_executable(boardroom
	"main.cpp"

	"MainWindow.hpp"
	"MainWindow.cpp"
	"MainWindow.ui"

	"WhiteboardScene.hpp"
	"WhiteboardScene.cpp"

	"WhiteboardView.hpp"
	"WhiteboardView.cpp"

	"WhiteboardToolsModel.hpp"
	"WhiteboardToolsModel.cpp"

	"Commands/DrawCommand.hpp"
	"Commands/DrawCommand.cpp"

	"Tools/Core/ITool.hpp"
	"Tools/Core/ToolBase.hpp"

	"Tools/ShapeTool.hpp"
	"Tools/ShapeTool.cpp"
	"Tools/PenTool.hpp"
	"Tools/PenTool.cpp"

	"Items/Core/IToolItem.hpp"
	"Items/Core/ToolItemBase.hpp"

	"Items/Shapes/LineItem.hpp"
	"Items/Shapes/LineItem.cpp"
	"Items/Shapes/RectangleItem.hpp"
	"Items/Shapes/RectangleItem.cpp"
	"Items/Shapes/EllipseItem.hpp"
	"Items/Shapes/EllipseItem.cpp"
	"Items/Shapes/TriangleItem.hpp"
	"Items/Shapes/TriangleItem.cpp"

	"Items/FreeDrawingItem.hpp"
	"Items/FreeDrawingItem.cpp"

	"Utility/IdHolder.hpp"
	"Utility/Registry.hpp"
	"Utility/SingleCall.hpp"
)

set_target_properties(boardroom PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO

	WIN32_EXECUTABLE YES
	MACOSX_BUNDLE YES
)

target_include_directories(boardroom PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(boardroom PRIVATE Qt::Core Qt::Gui Qt::Widgets)